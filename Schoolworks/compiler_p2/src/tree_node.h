#ifndef TREE_NODE_H_INCLUDE
#define TREE_NODE_H_INCLUDE

typedef struct st_tree_node {
    char *name;
    int n_children;
    struct st_tree_node **children;
} TreeNode;

TreeNode *mkNode(const char* name, int n_children, ...);
TreeNode *mkLeaf(const char* name);
void destroyTree(TreeNode *node);
void printTree(const TreeNode root);
#endif
