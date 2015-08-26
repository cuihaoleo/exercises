#!/usr/bin/env python3
s = 0
for i in range(1,101):
    for j in range(1,101):
        if i != j:
            s += i*j
print(s)
