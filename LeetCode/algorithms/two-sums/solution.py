class Solution:
    # @return a tuple, (index1, index2)
    def twoSum(self, num, target):
        di = dict((b, a) for a, b in enumerate(num))
        for ind, i in enumerate(num):
            try:
                ind2 = di[target-i]
            except KeyError:
                continue
            else:
                if ind != ind2:
                    return (ind+1, ind2+1)
