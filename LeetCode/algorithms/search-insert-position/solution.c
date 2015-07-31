int searchInsert(int* nums, int numsSize, int target) {
    int *pl = nums, *pr = nums+numsSize;
    
    while (pl < pr) {
        int *pm = pl+(pr-pl)/2;
        if (target > *pm)
            pl = pm+1;
        else if (target < *pm)
            pr = pm;
        else
            return pm-nums;
    }
    
    return pl-nums;
}
