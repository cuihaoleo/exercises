from functools import cache

class Solution:
    @cache
    def numTrees(self, n: int) -> int:
        if n == 0:
            return 1

        count = 0

        for i in range(n):
            count += self.numTrees(i) * self.numTrees(n - i - 1)

        return count
