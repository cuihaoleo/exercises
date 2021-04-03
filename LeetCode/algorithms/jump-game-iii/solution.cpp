#include <queue>
#include <algorithm>

class Solution {
public:
    bool canReach(vector<int>& arr, int start) {
        std::queue<int> q;
        std::vector<bool> visited(arr.size(), false);

        for (q.push(start); !q.empty(); q.pop()) {
            int pos = q.front();
            int left = pos - arr[pos];
            int right = pos + arr[pos];

            if (left >= 0 && !visited[left]) {
                q.push(left);
                visited[left] = true;
                if (arr[left] == 0) return true;
            }

            if (right < arr.size() && !visited[right]) {
                q.push(right);
                visited[right] = true;
                if (arr[right] == 0) return true;
            }
        }

        return false;
    }
};
