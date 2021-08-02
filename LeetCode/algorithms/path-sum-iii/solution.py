# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

from collections import Counter

class Solution:
    def pathSum(self, root: TreeNode, targetSum: int) -> int:
        prefix_sum_count = Counter([0])
        prefix_sum = 0
        count = 0

        def go(node: TreeNode):
            nonlocal prefix_sum, count

            if node is None:
                return

            prefix_sum += node.val
            count += prefix_sum_count[prefix_sum - targetSum]
            prefix_sum_count[prefix_sum] += 1

            go(node.left)
            go(node.right)

            prefix_sum_count[prefix_sum] -= 1
            prefix_sum -= node.val

        go(root)
        return count
