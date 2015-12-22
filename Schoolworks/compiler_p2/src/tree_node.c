#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "tree_node.h"

TreeNode* mkNode(const char* name, int n_children, ...) {
    TreeNode *node = (TreeNode*)malloc(sizeof(TreeNode));
    node->name = strdup(name);
    node->n_children = n_children;
    node->children = (TreeNode**)malloc(n_children * sizeof(TreeNode*));

    va_list arguments;
    va_start(arguments, n_children);

    int i;
    for (i=0; i<n_children; i++)
        (node->children)[i] = va_arg(arguments, TreeNode*);

    va_end(arguments);   

    return node;
}

TreeNode *mkLeaf(const char* name) {
    return mkNode(name, 0);
}

void destroyTree(TreeNode *node) {
    int i;
    for (i=0; i<node->n_children; i++)
        destroyTree((node->children)[i]);

    free(node->name);
    free(node->children);
    free(node);
}

void _printTree(const TreeNode *node, int deep, const char *indent) {
    int i;
    char next_indent[deep+1];

    for (i=0; i<deep-1; i++)
        printf("%c ", next_indent[i] = indent[i]);

    printf("|-%s\n", node->name);
    next_indent[deep-1] = indent[deep-1];
    next_indent[deep] = '|';

    for (i=0; i<node->n_children; i++) {
        if (i+1 == node->n_children)
            next_indent[deep] = ' ';
        _printTree(*(node->children+i), deep+1, next_indent);
    }
}

void printTree(const TreeNode root) {
    _printTree(&root, 1, " ");
}
