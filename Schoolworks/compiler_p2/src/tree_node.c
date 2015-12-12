#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "tree_node.h"

TreeNode* mkNode(const char* name, int n_children, ...) {
    TreeNode *node = malloc(sizeof(TreeNode));
    node->name = strdup(name);
    node->n_children = n_children;
    node->children = malloc(n_children * sizeof(TreeNode*));

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

void _indent(int deep) {
    int i;
    for (i=0; i<deep; i++) {
        putchar(' ');
        putchar(' ');
    }
}

void _printTree(const TreeNode *node, int deep) {
    _indent(deep);
    printf("%s\n", node->name);
    int i;
    for (i=0; i<node->n_children; i++)
        _printTree(*(node->children+i), deep+1);
}

void printTree(const TreeNode root) {
    _printTree(&root, 0);
}
