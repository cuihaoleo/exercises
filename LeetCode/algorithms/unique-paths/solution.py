class Solution:
    # @param {integer} m
    # @param {integer} n
    # @return {integer}
    def uniquePaths(self, m, n):
        dym = [1] * n
        for i in range(m-1):
            for j in range(n):
                dym[j] += dym[j-1] if j else 0
        return dym[-1]
