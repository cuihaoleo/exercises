class Solution:
    def numTrees(self, n: int) -> int:
        f = [1]

        for i in range(1, n + 1):
            count = 0

            for j in range(i):
                count += f[j] * f[i - j - 1]

            f.append(count)

        return f[n]
