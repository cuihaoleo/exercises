# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def isBalanced(self, root: TreeNode) -> bool:
        def dfs(node):
            if node is None:
                return 0, True

            left_d, left_isbalance = dfs(node.left)
            right_d, right_isbalance = dfs(node.right)

            if left_isbalance and right_isbalance and abs(left_d - right_d) <= 1:
                return max(left_d, right_d) + 1, True
            else:
                return 0, False

        return dfs(root)[1]
