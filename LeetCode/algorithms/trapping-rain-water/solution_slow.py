import array
from typing import List


class Solution:
    def trap(self, height: List[int]) -> int:
        height_map = array.array('h')
        h_prev = 0
        water = 0

        for x, y in enumerate(height):
            if y > h_prev:
                for level in range(h_prev + 1, min(y + 1, len(height_map))):
                    water += x - height_map[level] - 1

            for i in range(min(len(height_map), y + 1)):
                height_map[i] = x

            height_map.extend(x for _ in range(len(height_map), y + 1))
            h_prev = y

        return water


if __name__ == "__main__":
    solution = Solution()
    assert solution.trap([4,2,0,3,2,5]) == 9
    assert solution.trap([0,1,0,2,1,0,1,3,2,1,2,1]) == 6
