/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* searchRange(int* nums, int numsSize, int target, int* returnSize){
    int lo, hi, mid;
    int *result = malloc((*returnSize = 2) * sizeof(int));

    if (numsSize == 0 || target < nums[0] || target > nums[numsSize - 1]) {
        result[0] = result[1] = -1;
        return result;
    }

    // Binary search 1
    // nums[hi] >= target, nums[lo] < target
    lo = -1;
    hi = numsSize - 1;
    while (hi - lo > 1) {
        mid = (lo + hi) / 2;

        if (nums[mid] >= target)
            hi = mid;
        else
            lo = mid;
    }
    
    result[0] = lo + 1;
    
    // Binary search 2
    // nums[hi] > target, nums[lo] <= target
    // optimize: keep previous lo
    hi = numsSize;

    while (hi - lo > 1) {
        mid = (lo + hi) / 2;

        if (nums[mid] > target)
            hi = mid;
        else
            lo = mid;
    }

    result[1] = hi - 1;

    if (result[0] > result[1])
        result[0] = result[1] = -1;

    return result;
}
