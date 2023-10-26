# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def generateTrees(self, n: int) -> List[Optional[TreeNode]]:
        def go(avail_nums):
            if avail_nums:
                for i, val in enumerate(avail_nums):
                    for l in go(avail_nums[:i]):
                        for r in go(avail_nums[i + 1:]):
                            yield TreeNode(val, l, r)
            else:
                yield None

        return list(go(list(range(1, n + 1))))
