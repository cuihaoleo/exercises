bool isIsomorphic(char* s, char* t) {
    char s2t[256] = {0}, t2s[256] = {0};

    for (; *s; s++, t++) {
        if (s2t[*s] == 0)
            s2t[*s] = *t;
        else if (s2t[*s] != *t)
            return 0;
            
        if (t2s[*t] == 0)
            t2s[*t] = *s;
        else if (t2s[*t] != *s)
            return 0;
    }

    return 1;
}
