from functools import reduce

class Solution:
    def rob(self, nums: List[int]) -> int:
        return max(reduce(lambda dp, n: (dp[1] + n, max(dp)), nums, (0, 0)))
