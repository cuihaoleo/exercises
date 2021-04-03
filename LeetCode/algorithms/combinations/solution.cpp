#include <vector>

using std::vector;

class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> result;

        for (int i = 1; i <= n - k + 1; ++i) {
            result.emplace_back(k);
            result.back()[0] = i;
        }


        for (int i = 1; i < k; ++i)
            for (int j = result.size() - 1; j >= 0; --j) {
                int previous = result[j][i - 1];

                for (int l = previous + 2; l <= n - (k - i - 1); ++l) {
                    result[j][i] = l;
                    result.push_back(result[j]);
                }

                result[j][i] = previous + 1;
            }

        return result;
    }
};
