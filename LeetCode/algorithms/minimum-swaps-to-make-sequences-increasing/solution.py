class Solution:
    def minSwap(self, nums1: List[int], nums2: List[int]) -> int:
        n = len(nums1)
        dp_no_swap, dp_swap = 0, 1

        for i in range(1, n):
            best_swap = best_no_swap = n

            if nums1[i] > nums1[i - 1] and nums2[i] > nums2[i - 1]:
                best_no_swap = dp_no_swap  # cur: no swap, pre: no swap
                best_swap = dp_swap + 1    # cur: swap, pre: swap

            if nums2[i] > nums1[i - 1] and nums1[i] > nums2[i - 1]:
                best_swap = min(dp_no_swap + 1, best_swap)  # cur: swap, pre: no swap
                best_no_swap = min(dp_swap, best_no_swap)   # cur: no swap, pre: swap

            dp_swap, dp_no_swap = best_swap, best_no_swap

        return min(dp_swap, dp_no_swap)
