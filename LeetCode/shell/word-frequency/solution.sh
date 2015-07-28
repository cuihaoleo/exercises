echo $(cat words.txt) | tr ' ' '\n' | sort | uniq -c | awk '{ print $2,$1 }' | sort -rnk2
