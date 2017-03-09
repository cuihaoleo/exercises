typedef struct {
    int *p;
    int v;
} str1;

typedef struct {
    int prod;
    int sum;
} str2;

str2 word_sum(str1 s1) {
    str2 result;
    result.prod = *s1.p * s1.v;
    result.sum = *s1.p + s1.v;
    return result;
}

int diff(int x, int y) {
    str1 s1;
    str2 s2;
    s1.p = &x;
    s1.v = y;
    s2 = word_sum(s1);
    return s2.prod - s2.sum;
}
