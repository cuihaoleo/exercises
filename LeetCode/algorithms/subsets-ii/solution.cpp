#include <vector>
#include <algorithm>

using std::vector;

class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>> result;
        int previousNum = 0xFFFF;
        int previousResultPos;

        std::sort(nums.begin(), nums.end());
        result.emplace_back();

        for (const auto &n: nums) {
            int oldSize = result.size();

            if (n != previousNum) {
                previousNum = n;
                previousResultPos = 0;
            }

            for (int i = previousResultPos; i < oldSize; i++) {
                result.push_back(result[i]);
                result.back().push_back(n);
            }

            previousResultPos = oldSize;
        }

        return result;
    }
};
