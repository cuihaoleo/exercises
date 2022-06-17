/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


bool hasPathSum(struct TreeNode* root, int targetSum) {
    if (root == NULL)
        return false;

    int residue = targetSum - root->val;

    if (root->left == NULL && root->right == NULL)
        return residue == 0;
    else
        return hasPathSum(root->left, residue) || hasPathSum(root->right, residue);
}
