// Example:
// m = aa...aa, n = bb...bb
// Does n = bb..b1b..bb, and bb...b01..11 < m ?
// If so, this bit cannot be 0, set it~

int rangeBitwiseAnd(int m, int n) {
    int ans = 0, mask;

    for (mask=1; mask>=0; mask=mask<<1)
        if (n & mask && ((n^mask) | (mask-1)) < m)
            ans |= mask;

    return ans;
}
