int cread(int *xp) {
    return (xp ? *xp : 0);
}

int cread_alt(int *xp) {
    int zero = 0;
    return *(xp ? xp : &zero);
}
