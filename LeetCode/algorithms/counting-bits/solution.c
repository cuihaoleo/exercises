/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */

int* countBits(int num, int* returnSize) {
    int i, j = 0;
    int *ret = (int*)malloc((*returnSize = num + 1) * sizeof(int));

    for (i=1, ret[0]=0; i<=num; i++) {
        if ((i & (i-1)) == 0)
            j = 0;
        ret[i] = 1 + ret[j++];
    }

    return ret;
}
