class Solution:
    def combinationSum2(self, candidates, target):
        """
        :type candidates: List[int]
        :type target: int
        :rtype: List[List[int]]
        """

        def dfs(idx, csum):
            record.append(None)
            b = None

            for i in range(idx+1, len(candidates)):
                if b == candidates[i]:
                    continue
                else:
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
        return list(dfs(-1, 0))

if __name__ == "__main__":
    solver = Solution()
    print(solver.combinationSum2([10,1,2,7,6,1,5], 8))
    print(solver.combinationSum2([2,5,2,1,2], 5))
