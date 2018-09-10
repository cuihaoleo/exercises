class Solution:
    def combinationSum(self, candidates, target):
        """
        :type candidates: List[int]
        :type target: int
        :rtype: List[List[int]]
        """

        def dfs(idx, csum):
            record.append(None)
            for i in range(idx, len(candidates)):
                record[-1] = b = candidates[i]
                nsum = csum + b
                if nsum == target:
                    yield record[:]
                elif nsum > target:
                    break
                elif target - nsum >= b:
                    yield from dfs(i, nsum)
            record.pop()
 
        record = []
        candidates.sort()
        return list(dfs(0, 0))

if __name__ == "__main__":
    solver = Solution()
    print(solver.combinationSum([2, 3, 6, 7], 7))
    print(solver.combinationSum([2, 3, 5], 8))
