# 并非最优解
class Solution:
    def maxArea(self, height):
        """
        :type height: List[int]
        :rtype: int
        """
        out = sorted(range(len(height)), key=lambda k: height[k], reverse=True)
        maxidx = minidx = out[0]
        most_water = 0

        for idx in out[1:]:
            if idx < minidx:
                minidx = idx
            elif idx > maxidx:
                maxidx = idx

            water = max(maxidx-idx, idx-minidx) * height[idx]
            if water > most_water:
                most_water = water

        return most_water
