class Solution:
    def canPartition(self, nums: List[int]) -> bool:
        target, mod = divmod(sum(nums), 2)
        
        if mod:
            return False

        dp = bytearray(target + 1)
        dp[0] = 1

        for n in nums:
            if dp[target-n]:
                return True

            for i in range(target-1, n-1, -1):
                dp[i] |= dp[i-n]

        return dp[target] == 1
