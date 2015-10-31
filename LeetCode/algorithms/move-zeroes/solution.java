class Solution {
    public void moveZeroes(int[] nums) {
        int j = 0;
        for (int i=0; i<nums.length; i++, j++) {
            if (nums[i] == 0) {
                while (j < nums.length && nums[j] == 0) {
                    j++;
                }
                if (j == nums.length) {
                    break;
                }
                else if (i != j) {
                    nums[i] = nums[j];
                    nums[j] = 0;
                }
            }
        }
    }
}
