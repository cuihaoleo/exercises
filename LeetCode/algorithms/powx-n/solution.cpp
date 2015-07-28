class Solution {
public:
    double pow(double x, int n) {
        if (n == 1)
            return x;
        if (n == 0)
            return 1;
        if (n < 0)
            return 1/(x*pow(x, (-1)-n));

        double p = pow(x, n/2);
        return n&1 ? p*p*x : p*p;
    }
};
