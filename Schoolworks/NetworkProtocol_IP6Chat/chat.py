#!/usr/bin/env python3

import curses
import sys
import shlex
import textwrap

from chat_worker import ChatWorker


# from: https://stackoverflow.com/questions/1094841
def sizeof_fmt(num, suffix='B'):
    for unit in ['', 'Ki', 'Mi', 'Gi', 'Ti', 'Pi', 'Ei', 'Zi']:
        if abs(num) < 1024.0:
            return "%3.1f%s%s" % (num, unit, suffix)
        num /= 1024.0
    return "%.1f%s%s" % (num, 'Yi', suffix)


def main(stdscr):

    def do_command(cmd, arg_str):
        nonlocal file_client

        n_arg = {
            "/msg": 2,
            "/file": 3,
            "/recv": 2,
            "/users": 0,
            "/quit": 0,
        }
        args = shlex.split(arg_str)

        if cmd not in n_arg:
            msg_buf_append("[INFO]", "Unknown command %s" % cmd, "info")
            return False

        if len(args) != n_arg[cmd]:
            msg_buf_append("[INFO]", "Invalid command format", "info")
            return False

        if cmd == "/msg":
            nick, msg = args
            msg_buf_append("[ME]", "TO %s: %s" % (nick, msg), "pmsg")
            if not chat_worker.send_msg(nick, msg):
                msg_buf_append("[INFO]", "TO %s: FAILED" % nick, "info")
        elif cmd == "/file":
            nick, path, rate = args
            try:
                rate = int(rate)
            except ValueError:
                return False

            if not chat_worker.send_file(nick, path, rate):
                msg_buf_append("[INFO]", "Failed to send file", "info")
        elif cmd == "/recv":
            nick, path = args
            file_client = chat_worker.recv_file(nick, path)

            if file_client is None:
                msg_buf_append("[INFO]", "Failed to retrieve file from %s"
                               % nick, "info")
            else:
                msg_buf_append("[INFO]", "Receive file '%s' from %s"
                               % (path, nick), "info")
                msg_buf_append("[INFO]", "File transfer started", "info")
        elif cmd == "/users":
            for nick, host in chat_worker.online_users:
                msg_buf_append("[USERS]", "%s: [%s]" % (nick, host), "info")
        elif cmd == "/quit":
            chat_worker.bcast_bye()
            sys.exit(0)

        return True

    def msg_buf_append(nick, msg, mtype):
        nonlocal msg_linecount
        nonlocal msg_buf_changed

        msg = textwrap.fill(msg, msg_col-1) + "\n"
        msg_linecount += msg.count("\n")
        nick = nick[:nick_maxlen]
        msg_buf.append((nick, msg, mtype))

        while msg_linecount >= msg_row:
            _, msg, _ = msg_buf.pop(0)
            msg_linecount -= msg.count("\n")

        msg_buf_changed = True

    nick = sys.argv[1]
    channel = sys.argv[2]
    if_name = sys.argv[3]

    height, width = stdscr.getmaxyx()

    nick_win = curses.newwin(height-2, 10, 0, 0)
    nick_maxlen = 9
    msg_win = curses.newwin(height-2, width-10, 0, 10)
    msg_row, msg_col = msg_win.getmaxyx()
    input_win = curses.newwin(2, width, height-2, 0)

    file_win = curses.newwin(3, width, 0, 0)

    input_win.addstr(0, 0, "Input message here:")
    input_win.refresh()
    input_win.timeout(200)

    input_buf = []
    msg_buf = []
    msg_linecount = 0
    msg_buf_changed = False
    file_client = None

    chat_worker = ChatWorker(nick, channel, if_name)
    chat_worker.daemon = True
    chat_worker.start()

    msg_buf_append("[INFO]", "CHAT BEGIN (nick: %s, channel: %s@%s)"
                   % (nick, channel, if_name), "info")

    curses.init_pair(1, curses.COLOR_YELLOW, curses.COLOR_BLACK)
    curses.init_pair(2, curses.COLOR_CYAN, curses.COLOR_BLACK)
    colorset = {
            "gmsg": 0,
            "pmsg": curses.color_pair(1) | curses.A_BOLD,
            "info": curses.color_pair(2) | curses.A_LOW}

    while True:
        ch = input_win.getch(1, min(len(input_buf), width-1))

        if ch == -1:
            pass
        elif ch in [curses.KEY_BACKSPACE, curses.KEY_DC, 127]:
            if input_buf:
                input_buf.pop()
        elif ch in [curses.KEY_ENTER, 10, 13]:
            raw = "".join(input_buf)
            if raw.startswith("/"):
                cmd, _, arg_str = raw.partition(" ")
                do_command(cmd, arg_str)
            else:
                chat_worker.bcast_wall("".join(input_buf))
            input_buf.clear()
        elif chr(ch).isprintable():
            input_buf.append(chr(ch))

        recv_buf = chat_worker.recv_gmsg()
        for nick, msg in recv_buf:
            msg_buf_append(nick, msg, "gmsg")

        recv_buf = chat_worker.recv_pmsg()
        for nick, msg in recv_buf:
            msg_buf_append(nick, msg, "pmsg")

        if msg_buf_changed:
            msg_win.clear()
            nick_win.clear()

            start_line = msg_linecount
            for nick, msg, mtype in reversed(msg_buf):
                start_line -= msg.count("\n")
                if start_line >= 0:
                    nick_win.addstr(start_line, 0, nick, colorset[mtype])
                    msg_win.addstr(start_line, 0, msg, colorset[mtype])
                else:
                    break

            nick_win.refresh()
            msg_win.refresh()
            msg_buf_changed = False

        if chat_worker.has_newfile():
            for nick, filename, size in chat_worker.pending_files():
                msg_buf_append(nick, "SEND FILE: %s" % filename, "pmsg")

        if file_client is not None and file_client.is_alive():
            percent = file_client.progress * 100
            speed = file_client.avg_speed
            speed_str = sizeof_fmt(speed)
            disp = "[Transfer] %.2f%% (%s/s)" % (percent, speed_str)
            file_win.clear()
            file_win.box()
            file_win.addstr(1, 1, disp)
            file_win.refresh()
        elif file_client is not None:
            if file_client.success:
                msg_buf_append("[INFO]", "Successfully transferred", "info")
            else:
                msg_buf_append("[INFO]", "Failed to transfer, "
                               "bad hash or interrupted", "info")
            file_client = None

        display = "".join(input_buf)[-width+1:].ljust(width-1)
        input_win.addstr(1, 0, display)
        input_win.refresh()


if __name__ == "__main__":
    curses.wrapper(main)
