#!/usr/bin/env python3

MAX = 2000000
shai = [True] * (MAX + 1)
acc = 0

for i in range(2, MAX+1):
    if shai[i]:
        acc += i
        mul = 2 * i
        while mul <= MAX:
            shai[mul] = False
            mul += i

print(acc)
