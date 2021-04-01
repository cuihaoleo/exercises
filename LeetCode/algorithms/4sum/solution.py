from collections import Counter, defaultdict

class Solution:
    def fourSum(self, nums: List[int], target: int) -> List[List[int]]:
        one_dict = Counter(nums)
        two_sum_dict = defaultdict(list)

        uniq_nums = sorted(one_dict.keys())
        for i, ni in enumerate(uniq_nums):
            if one_dict[ni] > 1:
                two_sum_dict[ni + ni].append((ni, ni))

            for nj in uniq_nums[i + 1:]:
                two_sum_dict[ni + nj].append((ni, nj))

        uniq_two_sums = sorted(two_sum_dict.keys())
        p1, p2 = 0, len(uniq_two_sums) - 1
        results = set()

        while p1 <= p2:
            n1 = uniq_two_sums[p1]
            n2 = uniq_two_sums[p2]

            if n1 + n2 > target:
                p2 -= 1
            elif n1 + n2 < target:
                p1 += 1
            else:
                for a, b in two_sum_dict[n1]:
                    for c, d in two_sum_dict[n2]:
                        sorted_4nums = tuple(sorted([a, b, c, d]))
                        ct = Counter(sorted_4nums)

                        if all(ct[k] <= one_dict[k] for k in ct):
                            results.add(sorted_4nums)

                p1 += 1
                p2 -= 1

        return [list(t) for t in results]
