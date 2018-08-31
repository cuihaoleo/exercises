#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* longestPalindrome(char* s) {
    char *cur, *lp1;
    int maxlen = 0;

    if (s[0]) {
        maxlen = 1;
        lp1 = s;
    }

    for (cur=s; *cur; cur++) {
        int offset;

        for (offset=1; offset<=2 && cur[offset]; offset++) {
            char *p1 = cur, *p2 = cur + offset;
            while (p1 >= s && *p1 == *p2) {
                if (p2 - p1 + 1 > maxlen) {
                    maxlen = p2 - p1 + 1;
                    lp1 = p1;
                }
                p1--, p2++;
            }
        }
    }

    cur = malloc(maxlen+1);
    strncpy(cur, lp1, maxlen);
    cur[maxlen] = 0;

    return cur;
}

int main() {
    char *s = "ccc";
    char *p = longestPalindrome(s);
    puts(p);
    return 0;
}
