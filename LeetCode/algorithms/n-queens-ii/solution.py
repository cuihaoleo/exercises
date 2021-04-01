class Solution:
    def totalNQueens(self, n: int) -> int:
        def dfs(row):
            if row == 0:
                return 1

            count = 0
            for col in range(n):
                if col not in col_blacklist and \
                   row - col not in major_blacklist and \
                   row + col not in minor_blacklist:
                    col_blacklist.add(col)
                    major_blacklist.add(row - col)
                    minor_blacklist.add(row + col)

                    count += dfs(row - 1)

                    col_blacklist.remove(col)
                    major_blacklist.remove(row - col)
                    minor_blacklist.remove(row + col)

            return count

        col_blacklist = set()
        major_blacklist = set()
        minor_blacklist = set()

        return dfs(n)
