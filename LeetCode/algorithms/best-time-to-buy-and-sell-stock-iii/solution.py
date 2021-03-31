class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        running_min = prices[0]
        best_trans1 = [0]

        for p in prices[1:]:
            if p < running_min:
                running_min = p

            best_trans1.append(max(p - running_min, best_trans1[-1]))

        running_max = prices[-1]
        best = best_trans1.pop()
        best_trans2 = 0

        for p in prices[:0:-1]:
            if p > running_max:
                running_max = p

            if running_max - p > best_trans2:
                best_trans2 = running_max - p

            trans1 = best_trans1.pop()
            if best_trans2 + trans1 > best:
                best = best_trans2 + trans1

        return best
