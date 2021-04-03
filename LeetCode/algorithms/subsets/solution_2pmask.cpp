#include <vector>

using std::vector;

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> result;

        for (int i = 0; i < (1 << nums.size()); i++) {
            result.emplace_back();

            for (int j = 0, mask = i; mask; j++, mask >>= 1)
                if (mask & 1)
                    result[i].push_back(nums[j]);
        }

        return result;
    }
};
