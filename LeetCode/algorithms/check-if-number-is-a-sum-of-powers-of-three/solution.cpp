class Solution {
public:
    bool checkPowersOfThree(int n) {
        for (; n >= 1; n /= 3)
            if (n % 3 == 2)
                return false;

        return true;
    }
};
