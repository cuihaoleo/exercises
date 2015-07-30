int firstMissingPositive(int* nums, int numsSize) {
    int i;
    for (i=0; i<numsSize; i++) {
        int n;
        while ((n = nums[i]) > 0 &&
                n <= numsSize &&
                n-1 != i &&
                nums[n-1] != n) {
            nums[i] = nums[n-1];
            nums[n-1] = n;
        }
    }

    for (i=0; i<numsSize; i++)
        if (nums[i] != i+1)
            return i+1;

    return numsSize+1;
}
