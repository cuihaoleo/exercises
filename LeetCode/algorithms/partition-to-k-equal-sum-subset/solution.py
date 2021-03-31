from typing import List
import array


class Solution:
    def canPartitionKSubsets(self, nums: List[int], k: int) -> bool:

        def collectGoodSubsets(idx, mask, residue):
            if residue == 0:
                yield mask
            elif idx >= 0:
                yield from collectGoodSubsets(idx - 1, mask, residue)
                yield from collectGoodSubsets(idx - 1, mask | (1 << idx), residue - nums[idx])

        def findKSubsets(n_subset_left, prev_pos, prev_mask):
            if n_subset_left == 0:
                return True

            for i in range(prev_pos + 1, len(good_subsets) - n_subset_left + 1):
                mask = good_subsets[i]

                if prev_mask & mask == 0:
                    if findKSubsets(n_subset_left - 1, i, prev_mask | mask):
                        return True

            return False

        if k == 1:
            return True

        target, mod = divmod(sum(nums), k)

        if mod > 0:
            return False

        good_subsets = array.array('H', collectGoodSubsets(len(nums) - 1, 0, target))
        return findKSubsets(k, -1, 0)


if __name__ == "__main__":
    obj = Solution()
    assert obj.canPartitionKSubsets([4, 3, 2, 3, 5, 2, 1], 4) == True
    assert obj.canPartitionKSubsets([1, 1, 2, 4], 4) == False
