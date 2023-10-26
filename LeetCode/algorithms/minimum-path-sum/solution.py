class Solution:
    def minPathSum(self, grid: List[List[int]]) -> int:
        m = len(grid)
        n = len(grid[0])

        f = [0xFFFFFFFF] * n
        f[0] = 0

        for i in range(m):
            f[0] = f[0] + grid[i][0]

            for j in range(1, n):
                f[j] = min(f[j], f[j - 1]) + grid[i][j]

        return f[-1]
