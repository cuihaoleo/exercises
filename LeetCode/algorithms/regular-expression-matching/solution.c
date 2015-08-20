#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct part {
    char c;
    bool any;
};

int parse_pattern(const char* p, struct part **save) {
    int ct = 0;
    const char *pp = p;

    while (*pp) {
        if (*pp != '*') {
            ct++;
        }
        pp++;
    }

    *save = (struct part*) malloc(ct * sizeof(struct part));
    struct part* psave = *save - 1;
    for (pp=p; *pp; pp++) {
        if (*pp != '*') {
            psave++;
            psave->c = *pp;
            psave->any = false;
        }
        else {
            psave->any = true;
        }
    }

    return ct;
}

bool cmatch(char c, char p) {
    return p == '.' || c == p;
}

bool isMatch(char* s, char* p) {
    struct part* bp;
    int i, lp = parse_pattern(p, &bp);
    bool dym[2][lp+1];
    int row = 0;

    dym[0][0] = true;
    for (i=1; i<=lp && bp[i-1].any; i++) {
        dym[0][i] = true;
    }
    for (; i<=lp; i++) {
        dym[0][i] = false;
    }

    while (*s) {
        int lrow = row, j;
        bool ate = false;
        row = 1 - row;
        dym[row][0] = false;
        for (j=1; j<=lp; j++) {
            if (cmatch(*s, bp[j-1].c)) {
                if (bp[j-1].any) {
                    dym[row][j] = dym[lrow][j-1] || dym[lrow][j] || dym[row][j-1];
                }
                else {
                    if ((dym[row][j] = dym[lrow][j-1] || (!ate && dym[row][j-1]))) {
                        ate = true;
                    }
                }
            }
            else if (bp[j-1].any)
                dym[row][j] = dym[row][j-1];
            else
                dym[row][j] = false; 
        }
        s++;
    }

    return dym[row][lp];
}

int main() {
    printf("%d\n", isMatch("a", "aa"));
    printf("%d\n", isMatch("aa", "aa"));
    printf("%d\n", isMatch("aaa", "aa"));
    printf("%d\n", isMatch("aa", "a*"));
    printf("%d\n", isMatch("aa", ".*"));
    printf("%d\n", isMatch("ab", ".*"));
    printf("%d\n", isMatch("aab", "c*a*b"));
    printf("%d\n", isMatch("aaa", "ab*a"));
    printf("%d\n", isMatch("aaba", "ab*a*c*a"));
    printf("%d\n", isMatch("ab", ".*.."));
    return 0;
}
