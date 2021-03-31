class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        return sum(max(p2 - p1, 0) for p1, p2 in zip(prices, prices[1:]))
