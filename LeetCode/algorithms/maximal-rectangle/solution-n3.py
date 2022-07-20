class Solution:
    def maximalRectangle(self, matrix: List[List[str]]) -> int:
        # O(m n^2), not the optimal solution
        m, n = len(matrix), len(matrix[0])

        vertical_one_counts = [[int(i) for i in matrix[0]]]

        for i in range(1, m):
            one_counts = []
            vertical_one_counts.append(one_counts)

            for j in range(n):
                if matrix[i][j] == '1':
                    one_counts.append(vertical_one_counts[i - 1][j] + 1)
                else:
                    one_counts.append(0)

        max_area = 0

        for i in range(m):
            for j in range(n):
                height = m

                for offset in range(j + 1):
                    if matrix[i][j - offset] == '1':
                        height = min(vertical_one_counts[i][j - offset], height)
                        max_area = max(max_area, height * (offset + 1))
                    else:
                        break

        return max_area
