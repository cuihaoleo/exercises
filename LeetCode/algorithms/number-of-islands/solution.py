class Solution:
    def numIslands(self, grid: List[List[str]]) -> int:
        n_row = len(grid)
        n_col = len(grid[0])

        def dfs(y, x):
            for ny, nx in (y + 1, x), (y - 1, x), (y, x + 1), (y, x - 1):
                if 0 <= ny < n_row and 0 <= nx < n_col and grid[ny][nx] == '1':
                    grid[ny][nx] = '0'
                    dfs(ny, nx)

        count = 0

        for y in range(0, n_row):
            for x in range(0, n_col):
                if grid[y][x] == '1':
                    count += 1
                    dfs(y, x)

        return count
