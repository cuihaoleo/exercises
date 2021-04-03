class Solution {
public:
    int fib(int n) {
        int a = 0, b = 1;

        if (n == 0) return 0;

        for (int i = 1; i < n; i++) {
            int t = a;
            a = b;
            b += t;
        }

        return b;
    }
};
