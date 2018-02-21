#include <stdio.h>

int lengthOfLongestSubstring(char* s) {
    int flags[128] = { 0 };
    char *p, *q;
    int len = 0;
    int maxlen = 0;

    p = q = s;
    while (*q) {
        while (flags[(int)*q]) {
            flags[(int)*(p++)] = 0;
            len--;
        }

        flags[(int)*(q++)] = 1;

        if (++len > maxlen)
            maxlen = len;
    }

    return maxlen;
}

int main() {
    printf("%d\n", lengthOfLongestSubstring("abcabcbb"));
    printf("%d\n", lengthOfLongestSubstring("bbbbb"));
    printf("%d\n", lengthOfLongestSubstring("pwwkew"));
    return 0;
}
