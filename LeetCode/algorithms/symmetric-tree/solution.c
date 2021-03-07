/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

bool compare(const struct TreeNode *t1, const struct TreeNode *t2) {
    if (t1 == NULL || t2 == NULL)
        return t1 == NULL && t2 == NULL;
    
    return t1->val == t2->val && \
           compare(t1->left, t2->right) && \
           compare(t1->right, t2->left);
}

bool isSymmetric(struct TreeNode* root) {
    return compare(root->left, root->right);
}
