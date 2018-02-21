import select
import logging
import ipaddress
import threading
import struct
import re
import hashlib
import socket
import sys
import queue
import time
import base64
import os
import itertools

from socket import AF_INET6, IPPROTO_IPV6, SOCK_DGRAM
from socket import IPV6_PKTINFO, IPV6_RECVPKTINFO
from socket import IPV6_JOIN_GROUP, IPV6_MULTICAST_IF

from file_transfer import FileTransferClient, FileTransferServer


class ChatWorker(threading.Thread):
    """Protocol (Group)
        WALL <NICK> <MSG>
        WHERE <NICK>
        IAM <NICK>

       Protocol (Private)
        WHO
        MSG <MSG>
        FILE <PORT> <FILENAME> <SIZE>

       Protocol (TCP file transfer)
        <DATADATADATADATADATA>
    """

    CMD_ARGS = {
            "WALL": (0, 1),
            "IAM": (0, 1),
            "WHERE": (0, 1),
            "BYE": (0, 0),
            "WHO": (1, 0),
            "MSG": (1, 1),
            "FILE": (1, 3),
    }

    gen_id = itertools.count().__next__

    def __init__(self, nick, channel, if_name, port=50000, msg_ttl=2):
        super().__init__()

        self.id = ChatWorker.gen_id()
        logger = self.logger = logging.getLogger("ChatWorker #%d" % self.id)

        # setup socket for sending and receiving
        self.sock = sock = socket.socket(AF_INET6, SOCK_DGRAM)
        self.sock2 = sock2 = socket.socket(AF_INET6, SOCK_DGRAM)

        if_idx = socket.if_nametoindex(if_name)
        sock.setsockopt(IPPROTO_IPV6, IPV6_MULTICAST_IF, if_idx)
        sock2.setsockopt(IPPROTO_IPV6, IPV6_MULTICAST_IF, if_idx)
        logger.info("Bind to interface %s (#%d)", if_name, if_idx)

        # calculate multicast group from channel name
        ch_hash = hashlib.md5(channel.encode()).hexdigest()[:28]
        maddr = "ff12:" + ":".join(re.findall('....', ch_hash))

        group_addr_raw = socket.inet_pton(AF_INET6, maddr)
        group_if = struct.pack('@I', if_idx)
        sock.setsockopt(IPPROTO_IPV6, IPV6_JOIN_GROUP,
                        group_addr_raw + group_if)
        logger.info("Joined in multicast group [%s]", maddr)

        sock.bind(("::", port))
        logger.info("Listening on UDP port %d", port)

        self.nick = nick
        self.channel = channel
        logger.info("Nick: '%s'; Channel: '%s'", nick, channel)

        self.port = port
        self.maddr = maddr

        self.nick2host = dict()
        self.host2nick = dict()

        self.msg_ttl = msg_ttl
        self.pmsg = queue.Queue()
        self.gmsg = queue.Queue()
        self.newfile = False
        self.fsrv = dict()

        self.fileserver = None
        self.fileclient = None

    def __bcast(self, msg):
        self.logger.info("Multicast %s", msg)
        info = socket.getaddrinfo(self.maddr, self.port, AF_INET6, SOCK_DGRAM)
        self.sock2.sendto(msg.encode(), info[0][-1])

    def __send(self, msg, host, port=None):
        port = self.port if port is None else port
        self.logger.info("Send %s to [%s]:%d", msg, host, port)
        info = socket.getaddrinfo(host, port, AF_INET6, SOCK_DGRAM)
        self.sock2.sendto(msg.encode(), info[0][-1])

    def bcast_iam(self):
        self.__bcast("IAM %s" % self.nick)

    def bcast_where(self, nick):
        self.__bcast("WHERE %s" % nick)

    def bcast_wall(self, message):
        self.__bcast("WALL %s" % message)

    def bcast_bye(self):
        self.__bcast("BYE")

    def send_who(self, host):
        self.__send("WHO", host)

    def send_msg(self, nick, message):
        if nick in self.nick2host:
            host = self.nick2host[nick]
            self.__send("MSG %s" % message, host)
            return True
        else:
            self.bcast_where(nick)
            return False

    def send_file(self, nick, filepath, rate):
        if nick not in self.nick2host:
            self.bcast_where(nick)
            return False

        if self.fileserver != None and self.fileserver.is_alive():
            self.logger.warn("File server has already started")
            return False

        client_ip = self.nick2host[nick]
        fileserver = FileTransferServer(filepath, client_ip, rate=rate)
        fileserver.daemon = True
        fileserver.start()
        self.fileserver = fileserver

        host = self.nick2host[nick]
        filesize = fileserver.filesize
        filename = os.path.basename(filepath)
        filename_b64 = base64.b64encode(filename.encode())

        msg = "FILE %d %s %d" % (self.port, filename_b64.decode(), filesize)
        self.__send(msg, host)

        return True

    def update_addrbook(self, nick, host):

        if nick in self.nick2host:
            oldhost = self.nick2host.pop(nick)
            self.host2nick.pop(oldhost)

        if host in self.host2nick:
            oldnick = self.host2nick.pop(host)
            self.nick2host.pop(oldnick)

        self.host2nick[host] = nick
        self.nick2host[nick] = host
        self.logger.info("Update addrbook: %s -> %s", nick, host)

    def parse_msg(self, src, dest, message):
        cmd, _, arg_str = message.strip().partition(" ")

        if cmd in self.CMD_ARGS:
            cmd_type, cmd_reqarg = self.CMD_ARGS[cmd]
        else:
            self.logger.warning("Illegal command: %s", message)
            return False

        # verify command type
        dest_ip6 = ipaddress.IPv6Address(dest)
        if dest_ip6.is_multicast ^ (cmd_type == 0):
            self.logger.warning("Illegal command type: %s", message)
            return False

        # split command arguments
        if cmd_reqarg > 0:
            args = arg_str.split(" ", maxsplit=cmd_reqarg-1)
        else:
            args = list(arg_str)

        # verify number of arguments
        if len(args) != cmd_reqarg:
            self.logger.warning("Wrong number of arguments: %s", message)
            return False

        cur_time = time.time()
        if cmd == "WALL":
            self.gmsg.put((cur_time, src, args[0]))
        elif cmd == "WHERE":
            if args[0] == self.nick:
                self.bcast_iam()
        elif cmd == "BYE":
            try:
                nick = self.host2nick.pop(src)
                self.nick2host.pop(nick)
            except KeyError:
                pass
        elif cmd == "IAM":
            nick = args[0]
            self.update_addrbook(nick, src)
        elif cmd == "MSG":
            self.pmsg.put((cur_time, src, args[0]))
        elif cmd == "WHO":
            self.bcast_iam()
        elif cmd == "FILE":
            self.newfile = True
            port, filename_b64, size = args

            try:
                port = int(port)
                size = int(size)
                filename = base64.b64decode(filename_b64).decode()
            except (ValueError, TypeError):
                return False

            self.fsrv[src] = (port, filename, size)

        return True

    def run(self):
        # self.sock.setblocking(False)
        self.sock.setsockopt(IPPROTO_IPV6, IPV6_RECVPKTINFO, 1)
        self.bcast_iam()

        while True:
            # Max size of UDP datagram is about 64K
            # 1024 bytes buffer for destination addr is fair enough
            recvmsg = self.sock.recvmsg(65535, socket.CMSG_LEN(1024))
            raw, ancdata, flags, (host, port, *_) = recvmsg

            # Get destination addr
            for cmsg_level, cmsg_type, data in ancdata:
                if cmsg_level == IPPROTO_IPV6 and cmsg_type == IPV6_PKTINFO:
                    dip = socket.inet_ntop(AF_INET6, data[:16])
                    break
            else:
                continue

            # If host unknown, ask for its nick
            if host not in self.host2nick:
                self.logger.info("Unknown host: %s", host)
                self.send_who(host)

            buf = raw.decode()
            self.logger.info("Received '%s' ([%s]:%d -> [%s]:%d)",
                             buf, host, port, dip, self.port)

            success = self.parse_msg(host, dip, buf)
            if not success:
                self.logger.warning("Invalid message: %s", buf)

    def recv(self, q):
        items = []
        reque = []
        cur_time = time.time()

        while True:
            try:
                timestamp, host, msg = q.get_nowait()
            except queue.Empty:
                break

            if host in self.host2nick:
                items.append((self.host2nick[host], msg))
            else:
                self.send_who(host)
                if cur_time - timestamp <= self.msg_ttl:
                    reque.append((timestamp, host, msg))

        for item in reque:
            q.put(item)

        return items

    def recv_gmsg(self):
        return self.recv(self.gmsg)

    def recv_pmsg(self):
        return self.recv(self.pmsg)

    @property
    def online_users(self):
        return self.nick2host.items()

    def has_newfile(self):
        if self.newfile:
            self.newfile = False
            return True
        else:
            return False

    def pending_files(self):
        for host in self.fsrv:
            if host in self.host2nick:
                nick = self.host2nick[host]
                _, filename, size = self.fsrv[host]
                yield nick, filename, size

    def recv_file(self, nick, save_path):
        try:
            host = self.nick2host[nick]
        except KeyError:
            self.bcast_where(nick)
            return None

        try:
            port, filename, size = self.fsrv.pop(host)
        except KeyError:
            return None

        client = FileTransferClient(save_path, size, host, port)
        client.daemon = True
        client.start()

        return client
