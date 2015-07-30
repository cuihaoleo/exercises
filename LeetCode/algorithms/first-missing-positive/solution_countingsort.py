class Solution:
    # @param {integer[]} nums
    # @return {integer}
    def firstMissingPositive(self, nums):
        positive = max(sum(1 for n in nums if n >= 0), 1)
        a = [False] * (positive + 1)
        for n in nums:
            if 0 < n <= positive:
                a[n] = True
        for i in range(1, positive + 1):
            if a[i] == False:
                return i
        return positive + 1
