import socket
import time
import threading
import math
import sys
import hashlib
import os
import itertools
import logging

from socket import AF_INET6, SOCK_STREAM


class FileTransferServer(threading.Thread):

    gen_id = itertools.count().__next__

    def __init__(self, filepath, remote,
                 host="::", port=50000, rate=math.inf,
                 bufsize=1024, wait_time=60):
        super().__init__()

        self.id = FileTransferServer.gen_id()
        self.logger = logging.getLogger("FileTransferServer #%d" % self.id)

        if os.path.isfile(filepath):
            self._filepath = filepath
            self._filesize = os.path.getsize(filepath)
        else:
            self.logger.error("File '%s' not found", filepath)
            raise FileNotFoundError(filepath)

        self.sock = socket.socket(AF_INET6, SOCK_STREAM)
        self.sock.bind((host, port))

        self.logger.info("Local: [%s]:%d", host, port)
        self.logger.info("Remote: [%s]", remote)

        self.remote = remote
        self.rate = rate
        self.wait_time = wait_time
        self.bufsize = bufsize

    def sendfile(self, conn):
        t0 = time.time()
        total = 0
        hasher = hashlib.sha256()
        self.logger.info("Start to send file...")

        with open(self.filepath, "rb") as fin:
            while total < self.filesize:
                # bandwidth control
                dt = time.time() - t0
                dt_std = total / self.rate
                wait_time = dt_std - dt
                self.logger.debug("Sent %d, elapsed %f", total, dt)

                if wait_time > 0:
                    self.logger.debug("Wait %f secs", wait_time)
                    time.sleep(wait_time)

                # read/send/hash
                buf = fin.read(min(self.bufsize, self.filesize - total))
                total += len(buf)
                hasher.update(buf)
                conn.send(buf)

        digest = hasher.digest()
        self.logger.info("Digest: %s", hasher.hexdigest())
        conn.send(digest)

    def run(self):
        self.sock.listen()
        time_begin = time.time()
        self.sock.settimeout(self.wait_time)

        while True:
            try:
                conn, addr = self.sock.accept()
            except socket.timeout:
                break

            with conn:
                if addr[0] == self.remote:
                    self.sendfile(conn)
                    break

                self.logger.warning("Illegal conn from %s", addr)

                elapsed = time.time() - time_begin
                if elapse >= self.wait_time:
                    break

                self.sock.settimeout(self.wait_time - elapse)

        self.sock.close()

    @property
    def filesize(self):
        return self._filesize

    @property
    def filepath(self):
        return self._filepath


class FileTransferClient(threading.Thread):

    gen_id = itertools.count().__next__

    def __init__(self, local_path, size,
                 remote, port=50000, bufsize=1024):
        super().__init__()

        self.id = FileTransferClient.gen_id()
        self.logger = logging.getLogger("FileTransferClient #%d" % self.id)

        self.local_path = local_path
        self.server = (remote, port)
        self.bufsize = bufsize
        self.filesize = size
        self.total = 0
        self.start_time = time.time()
        self.hash_ok = False

    def run(self):
        addrinfo = socket.getaddrinfo(*self.server, AF_INET6, SOCK_STREAM)
        sock = socket.socket(AF_INET6, SOCK_STREAM)
        sock.connect(addrinfo[0][-1])
        hasher = hashlib.sha256()
        self.logger.info("Remote: [%s]:%d", self.server[0], self.server[1])

        with open(self.local_path, "wb") as fout:
            while self.total < self.filesize:
                buf = sock.recv(min(self.bufsize, self.filesize - self.total))
                self.total += len(buf)
                hasher.update(buf)
                fout.write(buf)

        digest = hasher.digest()
        recv_digest = sock.recv(hasher.digest_size)
        sock.close()

        self.logger.info("File saved: %s", self.local_path)
        self.logger.info("Digest: %s", hasher.hexdigest())
        recv_digest_hex = "".join([hex(i)[2:].zfill(2) for i in recv_digest])
        self.logger.info("Remote digest: %s", recv_digest_hex)
        if recv_digest == digest:
            self.hash_ok = True
            self.logger.info("Checksum OK")
        else:
            self.logger.warning("Checksum bad")

    @property
    def progress(self):
        return self.total / self.filesize

    @property
    def avg_speed(self):
        elapse = time.time() - self.start_time
        return self.total / elapse

    @property
    def success(self):
        return None if self.is_alive() else self.hash_ok
