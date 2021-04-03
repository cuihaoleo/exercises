#include <vector>
#include <numeric>
#include <algorithm>

using std::vector;

int factorial(int n) {
    int ret = 1;
    for (int i = 2; i <= n; i++) ret *= i;
    return ret;
}

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        int n = nums.size();
        int returnSize = factorial(n);
        vector<vector<int>> result(returnSize, vector<int>(n));

        // Johnson–Trotter algorithm
        vector<bool> dir(n, false);
        vector<int> pos(n);
        vector<int> val(n);

        std::iota(pos.begin(), pos.end(), 0);
        val = pos;
        result[0] = nums;

        for (int i = 1; i < returnSize; i++) {
            // find the greatest movable element
            int chosen, oldPos, newPos, swapped;

            for (chosen = n - 1; chosen >= 0; chosen--) {
                oldPos = pos[chosen];
                newPos = oldPos + (dir[chosen] ? 1:-1);

                if (newPos >= 0 && newPos < n && (swapped = val[newPos]) < chosen)
                    break;
            }

            // swap
            pos[swapped] = oldPos;
            pos[chosen] = newPos;
            val[oldPos] = swapped;
            val[newPos] = chosen;

            // assign the result
            for (int j = 0; j < n; j++)
                result[i][j] = nums[val[j]];

            // change directions
            for (int j = chosen + 1; j < n; j++)
                dir[j] = !dir[j];
        }

        return result;
    }
};
