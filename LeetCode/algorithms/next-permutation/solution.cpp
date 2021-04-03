#include <algorithm>
#include <vector>

using std::vector;

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int pos1;
            
        for (pos1 = nums.size() - 2; pos1 >= 0; pos1--)
            if (nums[pos1] < nums[pos1 + 1])
                break;

        if (pos1 < 0)
            std::reverse(nums.begin(), nums.end());
        else {
            int pos2 = pos1 + 1;

            for (int j = pos2 + 1; j < nums.size(); j++)
                if (nums[pos1] < nums[j] && nums[j] <= nums[pos2])
                    pos2 = j;
            
            std::swap(nums[pos1], nums[pos2]);
            std::reverse(nums.begin() + pos1 + 1, nums.end());
        }
    }
};
