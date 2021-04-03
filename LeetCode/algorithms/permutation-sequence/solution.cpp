#include <vector>
#include <string>

class Solution {
public:
    std::string getPermutation(int n, int k) {
        std::vector<bool> mask(n);
        std::string result(n, '0');
        int factorial = 1;

        for (int i = 2; i <= n; i++)
            factorial *= i;

        k--;

        for (int i = n; i >= 1; i--) {
            factorial /= i;

            int digit = 0;
            for (int j = k / factorial; digit < n; digit++)
                if (!mask[digit] && j-- == 0)
                    break;

            mask[digit] = true;
            result[n - i] = digit + '1';

            k %= factorial;
        }

        return result;
    }
};
