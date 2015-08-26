#!/bin/bash

sum=0
for (( i=1901; i<=2000; i++ )); do
    for (( j=1; j<=12; j++ )); do
        s=$(cal $j $i | awk 'NR == 3 {print $0}' | cut -c2)
        if [[ "$s" == '1' ]]; then
            sum=$(($sum+1))
        fi
    done
done
echo $sum

