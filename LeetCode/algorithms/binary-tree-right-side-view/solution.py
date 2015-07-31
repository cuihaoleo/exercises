# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None
from math import log


class Solution:
    # @param {TreeNode} root
    # @return {integer[]}
    def rightSideView(self, root):

        def dfs(node, pos):
            if not node:
                return

            row = int(log(pos, 2))
            if row >= len(ans):
                ans.append((node, pos))
            elif pos > ans[row][1]:
                ans[row] = (node, pos)

            dfs(node.left, pos*2)
            dfs(node.right, pos*2+1)

        ans = []
        dfs(root, 1)
        return [p[0].val for p in ans]
