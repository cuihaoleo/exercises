from itertools import chain, ifilter, izip
class Solution:
    # @param {integer[]} nums
    # @return {string[]}
    def summaryRanges(self, nums):
        it = ifilter(
                lambda x: x != 1 << 64,
                chain.from_iterable(
                    pair for pair in izip(
                        chain([1 << 64], nums),
                        chain(nums, [1 << 64])
                    ) if pair[1]-pair[0] != 1))
        return ['{}->{}'.format(*p)
                if p[0] != p[1] else str(p[0])
                for p in izip(it, it)]
