import array

class Solution:
    def maxProfit(self, k: int, prices: List[int]) -> int:
        if len(prices) == 0:
            return 0
        
        # optimization: consider only maximum and minimum
        p_compact = array.array('H')
        i = 1
        while True:
            p_compact.append(prices[i-1])
            direction = 0

            try:
                while (prices[i] - prices[i-1]) * direction >= 0:
                    if prices[i] < prices[i-1]:
                        direction = -1
                    elif prices[i] > prices[i-1]:
                        direction = 1

                    i += 1
            except IndexError:
                p_compact.append(prices[-1])
                break
        
        # dynamic programming
        # dp[k, i]: max profit you get at day i after at most k transactions
        n_days = len(p_compact)
        dp = array.array('L', (0 for _ in range(n_days)))

        for _ in range(1, k + 1):
            dp_new = dp[:]

            for i in range(1, n_days):
                if p_compact[i] <= p_compact[i-1]:
                    dp_new[i] = dp_new[i-1]
                    continue

                running_max = p_compact[i]
                best_trans = 0

                for j in range(i-1, -1, -1):
                    if p_compact[j] > running_max:
                        running_max = p_compact[j]
                    elif running_max - p_compact[j] > best_trans:
                        best_trans = running_max - p_compact[j]

                    if dp[j] + best_trans > dp_new[i]:
                        dp_new[i] = dp[j] + best_trans

            dp = dp_new

        return dp[-1]
