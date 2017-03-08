int loop(int x, int n) {
    int result = 0x55555555;
    int mask;
    for (mask = 0x80000000; mask; mask = (unsigned)mask >> (char)n)
        result ^= mask & x;
    return result;
}
