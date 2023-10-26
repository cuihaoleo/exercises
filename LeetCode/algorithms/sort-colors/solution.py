class Solution:
    def sortColors(self, nums: List[int]) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        k = 0
        i1, i2 = 0, len(nums) - 1

        while k <= i2:
            if nums[k] == 0 and k >= i1:
                nums[k], nums[i1] = nums[i1], nums[k]
                i1 += 1
            elif nums[k] == 2:
                nums[k], nums[i2] = nums[i2], nums[k]
                i2 -= 1
            else:
                k += 1
