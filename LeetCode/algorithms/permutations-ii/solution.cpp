#include <iostream>
#include <algorithm>
#include <vector>

using std::vector;

class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> result;
        
        result.push_back(nums);
        std::sort(result[0].begin(), result[0].end());

        // generate by lexicological order
        for (;;) {
            vector<int> last(result.back());
            int j, pos1, pos2;
            
            for (pos1 = n - 2; pos1 >= 0; pos1--)
                if (last[pos1] < last[pos1 + 1])
                    break;

            if (pos1 < 0)
                break;

            for (j = (pos2 = pos1 + 1) + 1; j < n; j++)
                // beware of '<='
                if (last[pos1] < last[j] && last[j] <= last[pos2])
                    pos2 = j;
            
            std::swap(last[pos1], last[pos2]);
            std::reverse(last.begin() + pos1 + 1, last.end());
            result.push_back(last);
        }
        
        return result;
    }
};

int main() {
    std::vector<int> nums{1, 1, 4, 2, 4};
    Solution solution;
    auto result = solution.permuteUnique(nums);

    for (auto it = result.begin(); it != result.end(); it++) {
        for (auto jt = it->begin(); jt != it->end(); jt++)
            std::cout << ' ' << *jt;
        std::cout << std::endl;
    }

    return 0;
}
