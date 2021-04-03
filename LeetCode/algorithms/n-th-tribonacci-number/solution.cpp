class Solution {
public:
    int tribonacci(int n) {
        int a = 0, b = 0, c = 1;
        
        if (n == 0) return 0;
        
        for (int i = 1; i < n; i++) {
            int t = a;
            a = b;
            b = c;
            c += t + a;
        }
        
        return c;
    }
};
