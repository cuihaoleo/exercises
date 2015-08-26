#!/usr/bin/env python3

import subprocess

subprocess.check_output('fpc p17_numbeng.pas -O3 -oa.out', shell=True)

ac = 0
for i in range(1, 1001):
    s = subprocess.check_output('echo %d | ./a.out' % i, shell=True)
    ac += len(s.strip().replace(b' ', b'').replace(b'-', b''))

print(ac)
