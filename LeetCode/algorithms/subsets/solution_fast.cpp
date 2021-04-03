#include <vector>
#include <algorithm>

using std::vector;

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> result;

        result.reserve(1 << nums.size());
        result.emplace_back();

        for (const auto &n: nums)
            std::transform(result.crbegin(), result.crend(), back_inserter(result), [n](auto v) {
                v.push_back(n);
                return std::move(v);
            });

        return result;
    }
};
