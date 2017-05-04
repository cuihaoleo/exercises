#!/bin/bash

bmode=(cbc ctr cts ecb lrw pcbc xts keywrap)
cipher=(aes anubis arc4 blowfish camellia cast cast5 cast6 chacha20 des des3 fcrypt khazad salsa20 seed serpent tea twofish)

for c in ${cipher[@]}; do
    for m in ${bmode[@]}; do
        for ((i=8; i<=2048; i+=8)); do
            cryptsetup benchmark -c $c-$m -s $i 2>/dev/null | grep -v '^#'
        done
    done
done
