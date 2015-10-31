import java.util.HashMap;

public class Solution {
    public boolean containsDuplicate(int[] nums) {
        HashMap<Integer, Boolean> d = new HashMap<Integer, Boolean>();
        for (int i: nums) {
            Boolean value = d.get(i);
            if (value != null && value) {
                return true;
            }
            else {
                d.put(i, true);
            }
        }
        return false;
    }
}
