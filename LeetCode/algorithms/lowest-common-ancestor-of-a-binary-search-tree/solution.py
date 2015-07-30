# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    # @param {TreeNode} root
    # @param {TreeNode} p
    # @param {TreeNode} q
    # @return {TreeNode}
    def lowestCommonAncestor(self, root, p, q):
        if p == root or q == root:
            return root

        pnode = root.left if p.val < root.val else root.right
        qnode = root.left if q.val < root.val else root.right

        if pnode != qnode:
            return root
        else:
            return self.lowestCommonAncestor(pnode, p, q)
