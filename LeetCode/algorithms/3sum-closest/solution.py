class Solution:
    def threeSumClosest(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: int
        """
        nums.sort()
        k0 = len(nums)
        mindist = 0x7fffffff
        result = 0

        for i in range(len(nums)):
            while k0 > i + 2 and nums[i]*2 + nums[k0-1] > target:
                k0 -= 1

            if k0 <= i:
                break

            k = k0
            for j in range(i+1, len(nums)):
                part = nums[i] + nums[j]

                while k > j + 1 and part + nums[k-1] > target:
                    k -= 1

                if k <= j:
                    break

                if k < len(nums):
                    sum3 = part + nums[k]
                    if sum3 - target < mindist:
                        mindist = sum3 - target
                        result = sum3

                if k - 1 > j:
                    sum3 = part + nums[k-1]
                    if target - sum3 < mindist:
                        mindist = target - sum3
                        result = sum3

        return result

if __name__ == "__main__":
    solver = Solution()
    print(solver.threeSumClosest([0, 1, 2], 0))
