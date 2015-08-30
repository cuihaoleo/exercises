#!/usr/bin/env python3
# 用终端颜色渲染图片，推荐256色终端
# colorfinder.py from lilydjwg/winterpy on github
# lolcat.py from https://gist.github.com/lilydjwg/9891346

from PIL import Image
import concurrent.futures
import argparse
import lzma
import array
import itertools
import subprocess

try:
    from lolcat import get_terminal_size
except ImportError:
    def get_terminal_size():
        op = subprocess.check_output(["stty", "size"]).strip().decode()
        return tuple(int(i) for i in op.split())

colormap = array.array("B")


# 给 hex2term 事先打表
def read_colormap(path):
    with lzma.open(path) as fin:
        while True:
            try:
                times, color = fin.read(2)
            except ValueError:
                break
            else:
                colormap.extend(itertools.repeat(color, times))

    if len(colormap) != 256**3:
        raise argparse.ArgumentError("Invalid color map!")
    else:
        return colormap


if __name__ == "__main__":
    termsize = get_terminal_size()

    parser = argparse.ArgumentParser()
    parser.add_argument("file", type=Image.open,
                        help="path to the image file")
    parser.add_argument("-c", "--col", type=int, default=termsize[1],
                        help="number of cols",)
    parser.add_argument("-r", "--row", type=int, default=termsize[0],
                        help="number of rows")
    parser.add_argument("-f", "--fast", action="store_true",
                        help="use a faster color-mapping algorithm")
    parser.add_argument("-m", "--map", type=read_colormap,
                        help="color map (quite fast for big image)")

    args = parser.parse_args()
    coln, rown = args.col, args.row
    im = args.file.resize((coln, rown), Image.ANTIALIAS).convert("RGB")

    if args.map:
        hex2term = lambda h: colormap[int(h[1:], 16)]
    elif args.fast:
        from colorfinder import hex2term_quick as hex2term
    else:
        from colorfinder import hex2term_accurate as hex2term

    def generate_line(row):
        ret = ""
        for j in range(coln):
            r, g, b = im.getpixel((j, row))
            res = hex2term("#%02x%02x%02x" % (r, g, b))
            ret += '\x1b[48;5;{c}m \x1b[0m'.format(c=res)
        return ret

    with concurrent.futures.ProcessPoolExecutor() as executor:
        for i in executor.map(generate_line, range(rown)):
            print(i)
