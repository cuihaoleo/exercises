import os
import sys
import colorsys

row = int(sys.argv[1])
out = sys.argv[2]
files = sys.argv[3:]

fout = open(out, "wb")
fout.write("P6\x0a{0} {0}\x0a255\x0a".format(row).encode())

fin = open(os.devnull, 'rb')

for i in range(row * row):
    three = []

    for j in range(3):
        byte = fin.read(1)

        while len(byte) != 1:
            fin = open(files.pop(0), "rb")
            byte = fin.read(1)

        three.append(byte[0])

    fout.write(bytes(three))

fin.close()
fout.close()
