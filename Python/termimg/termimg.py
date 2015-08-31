#!/usr/bin/env python3
# 用终端颜色渲染图片，推荐256色终端
# colorfinder.py from lilydjwg/winterpy on github
# lolcat.py from https://gist.github.com/lilydjwg/9891346

from PIL import Image
from concurrent.futures import ProcessPoolExecutor
import argparse
import lzma
import itertools
import subprocess
import curses
from array import array as Array

try:
    from lolcat import get_terminal_size
except ImportError:
    def get_terminal_size():
        op = subprocess.check_output(["stty", "size"]).strip().decode()
        return tuple(int(i) for i in op.split())


# a dummy executor to replace concurrent executors
class DummyExecutor:
    def __enter__(self):
        return type("", (), {"map": map})()

    def __exit__(self, *args, **kwargs):
        pass


try:
    from colorfinder import hex2term_quick, hex2term_accurate
except ImportError:
    method_accurate = method_quick = None
else:
    def method_accurate(r):
        return Array("B", (hex2term_accurate("#%02x%02x%02x" % c) for c in r))

    def method_quick(r):
        return Array("B", (hex2term_quick("#%02x%02x%02x" % c) for c in r))


def load_colormap(path):
    global colormap
    colormap = Array("B")

    with lzma.open(path) as fin:
        tb = fin.read(2)
        while len(tb) == 2:
            times, color = tb
            colormap.extend(itertools.repeat(color, times))
            tb = fin.read(2)

    if len(colormap) != 256**3:
        raise OSError("Invalid color map!")


def method_map(row):
    return Array("B", (colormap[r*256*256+g*256+b] for r, g, b in row))


class TerminalImage:
    def __init__(self, path):
        self.img = Image.open(path).convert("RGB")
        self.map = []
        self.cols = self.rows = 0

    def map_color(self, cols, rows, method, parallel=False):
        Executor = ProcessPoolExecutor if parallel else DummyExecutor
        im = self.img.resize((cols, rows), Image.ANTIALIAS).convert("RGB")

        def yield_row():
            for row in range(rows):
                yield [im.getpixel((col, row)) for col in range(cols)]

        with Executor() as executor:
            self.map = list(executor.map(method, yield_row()))
            self.cols, self.rows = cols, rows

    def print(self):
        for row in self.map:
            print(''.join('\x1b[48;5;{}m \x1b[0m'.format(c) for c in row))

    def curses(self, stdscr):
        curses.curs_set(False)
        curses.start_color()
        curses.use_default_colors()
        stdscr.keypad(True)
        stdscr.refresh()

        if curses.COLORS < 256 or curses.COLOR_PAIRS < 256:
            raise NotImplementedError("curses output requires 256-color terms")

        for i in range(256):
            curses.init_pair(i, -1, i)

        pad = curses.newpad(self.rows+1, self.cols+1)
        for rn in range(self.rows):
            for cn in range(self.cols):
                pad.addch(rn, cn, ' ', curses.color_pair(self.map[rn][cn]))

        trow, tcol = get_terminal_size()
        cy = cx = 0

        while True:
            pad.refresh(cy, cx, 0, 0, trow-1, tcol-1)
            ch = stdscr.getch()

            if ch in [27, ord('q')]:
                break
            elif ch in [curses.KEY_UP, ord('k')]:
                cy = max(cy-1, 0)
            elif ch in [curses.KEY_DOWN, ord('j')]:
                cy = min(cy+1, self.rows)
            elif ch in [curses.KEY_LEFT, ord('h')]:
                cx = max(cx-1, 0)
            elif ch in [curses.KEY_RIGHT, ord('l')]:
                cx = min(cx+1, self.cols)


if __name__ == "__main__":
    termsize = get_terminal_size()

    parser = argparse.ArgumentParser()
    parser.add_argument("file", type=TerminalImage,
                        help="path to the image file")
    parser.add_argument("-c", "--col", type=int, default=termsize[1],
                        help="number of cols",)
    parser.add_argument("-r", "--row", type=int, default=termsize[0],
                        help="number of rows")
    parser.add_argument("-f", "--fast", action="store_true",
                        help="use a faster color-mapping algorithm")
    parser.add_argument("-m", "--map",
                        help="color map (quite fast for big image)")
    parser.add_argument("-p", "--parallel", action="store_true",
                        help="use multi-process")
    parser.add_argument("-u", "--curses", action="store_true",
                        help="use curses lib")
    args = parser.parse_args()

    if args.map:
        load_colormap(args.map)
        method = method_map
    elif args.fast:
        method = method_quick
    else:
        method = method_accurate

    if method is None:
        raise NotImplementedError("Selected method is not supported")

    termimg = args.file
    termimg.map_color(cols=args.col, rows=args.row,
                      method=method, parallel=args.parallel)

    if args.curses:
        curses.wrapper(termimg.curses)
    else:
        termimg.print()
