class Solution:
    # @param {integer[][]} obstacleGrid
    # @return {integer}
    def uniquePathsWithObstacles(self, obstacleGrid):
        m, n = len(obstacleGrid), len(obstacleGrid[0])
        dym = [0] * n

        for j in range(n):
            if obstacleGrid[0][j] == 0:
                dym[j] = 1
            else:
                break

        for i in range(1, m):
            for j in range(n):
                if obstacleGrid[i][j] == 0:
                    dym[j] += dym[j-1] if j else 0
                else:
                    dym[j] = 0

        return dym[-1]
