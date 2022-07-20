class Solution:
    def maximalSquare(self, matrix: List[List[str]]) -> int:
        m, n = len(matrix), len(matrix[0])

        prev_dp = [int(i) for i in matrix[0]]
        max_width = max(prev_dp)

        for i in range(1, m):
            curr_dp = [int(matrix[i][0])]

            for j in range(1, n):
                if matrix[i][j] == '1':
                    curr_dp.append(min(curr_dp[j - 1], prev_dp[j], prev_dp[j - 1]) + 1)
                else:
                    curr_dp.append(0)

            max_width = max(max_width, max(curr_dp))
            prev_dp = curr_dp

        return max_width * max_width
