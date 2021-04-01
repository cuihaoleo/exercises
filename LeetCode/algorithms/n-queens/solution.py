class Solution:
    def solveNQueens(self, n: int) -> List[List[str]]:
        def dfs(row):
            if row == n:
                yield [row.decode() for row in chessboard]
                return

            for col in range(n):
                if col not in col_blacklist and \
                   row - col not in major_blacklist and \
                   row + col not in minor_blacklist:
                    col_blacklist.add(col)
                    major_blacklist.add(row - col)
                    minor_blacklist.add(row + col)
                    chessboard[row][col] = ord('Q')

                    yield from dfs(row + 1)

                    col_blacklist.remove(col)
                    major_blacklist.remove(row - col)
                    minor_blacklist.remove(row + col)
                    chessboard[row][col] = ord('.')

        chessboard = [bytearray(b"." * n) for _ in range(n)]
        col_blacklist = set()
        major_blacklist = set()
        minor_blacklist = set()

        return list(dfs(0))
