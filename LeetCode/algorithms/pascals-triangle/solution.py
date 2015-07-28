class Solution:
    # @return a list of lists of integers
    def generate(self, numRows):
        ans = []
        for i in range(numRows):
            row = [1]
            for j in range(i):
                try:
                    le = ans[i-1][j]
                except IndexError:
                    le = 0

                try:
                    ri = ans[i-1][j+1]
                except IndexError:
                    ri = 0

                row.append(le+ri)
            ans.append(row)
        return ans
