#!/usr/bin/env python3

def fib (m):
    a, b, c = 0, 1, 1
    yield 1
    while c <= m:
        yield c 
        c = a + b
        a, b= b, c

s = 0
for i in fib(4000000):
    if i%2 == 0:
        s += i 

print(s)
