class Solution {
public:
    bool isPowerOfTwo(int n) {
        int s = 0;
        while (n > 0) {
            s += n & 1;
            n >>= 1;
        }
        return s == 1;
    }
};
