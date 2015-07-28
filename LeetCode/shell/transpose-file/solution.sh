# zsh won't transform string into array by ($var)

declare -A matrix
rowcount=0
while read line; do
    colcount=0
    for word in $line; do
        matrix[$rowcount,$colcount]=$word
        let colcount++
    done
    let rowcount++
done < file.txt

for ((i=0; i<colcount; i++)); do
    echo -n ${matrix[0,$i]}
    for ((j=1; j<rowcount; j++)); do
        echo -n ' '${matrix[$j,$i]}
    done
    echo
done
