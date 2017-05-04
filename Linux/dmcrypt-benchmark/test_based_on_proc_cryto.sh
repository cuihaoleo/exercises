#!/bin/bash

cat /proc/crypto \
    | grep -P '^name\s+: [[:alnum:]]+\([[:alnum:]]+\)' \
    | awk '{ print $3 }' \
    | sed 's_\(\w\+\)(\(\w\+\))_\2-\1_' \
| while read cipher; do

    for ((i=8; i<=2048; i+=8)); do
        cryptsetup benchmark -c $cipher -s $i 2>/dev/null | grep -v '^#'
    done
done
