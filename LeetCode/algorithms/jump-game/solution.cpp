#include <algorithm>

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int max_reach = 0;

        for (int i = 0; max_reach < nums.size() - 1; i++)
            if (i > max_reach)
                return false;
            else if (i + nums[i] > max_reach)
                max_reach = i + nums[i];

        return true;
    }
};
