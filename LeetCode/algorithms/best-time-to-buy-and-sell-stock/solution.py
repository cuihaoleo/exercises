class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        running_min = prices[0]
        best = 0

        for p in prices[1:]:
            if p < running_min:
                running_min = p

            if p - running_min > best:
                best = p - running_min

        return best
