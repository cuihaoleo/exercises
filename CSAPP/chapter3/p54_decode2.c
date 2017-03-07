int decode2(int x, int y, int z) {
    int t = z - y;
    int eax = t << 15 >> 15;
    int edx = t | x;
    return eax * edx;
}
