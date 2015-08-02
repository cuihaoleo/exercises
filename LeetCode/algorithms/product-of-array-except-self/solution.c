/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdlib.h>
int* productExceptSelf(int* nums, int numsSize, int* returnSize) {
    int *ans = malloc((*returnSize=numsSize)*sizeof(int));
    int left = 1, right = 1, i = 0;
    
    for (i=0; i<numsSize; i++)
        ans[i] = 1;

    for (i=0; i<numsSize;) {
        ans[i] *= left;
        left *= nums[i];
        i++;
        ans[numsSize-i] *= right;
        right *= nums[numsSize-i];
    }
    
    return ans;
}
