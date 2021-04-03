#include <algorithm>

class Solution {
public:
    int jump(vector<int>& nums) {
        int step = 0;
        int current_reach = 0;
        int next_reach = 0;

        for (int i = 0; i < nums.size(); i++) {
            if (i > current_reach) {
                step++;
                current_reach = next_reach;
            }

            next_reach = std::max(next_reach, i + nums[i]);
        }

        return step;
    }
};
