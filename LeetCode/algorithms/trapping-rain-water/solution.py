class Solution:
    def trap(self, height: List[int]) -> int:
        highest = [0]
        water = 0

        for h in height:
            highest.append(max(h, highest[-1]))

        highest_right = 0
        for x in range(len(height) - 1, 0, -1):
            highest_left = highest.pop()

            if height[x] > highest_right:
                highest_right = height[x]

            water += max(0, min(highest_right, highest_left) - height[x])

        return water
