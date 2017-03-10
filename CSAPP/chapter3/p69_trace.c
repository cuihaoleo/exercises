typedef struct ELE *tree_ptr;

struct ELE {
    tree_ptr left;
    tree_ptr right;
    long val;
};

long trace(tree_ptr tp) {
    long retval = 0;

    while (tp) {
        retval = tp->val;
        tp = tp->left;
    }

    return retval;
}
