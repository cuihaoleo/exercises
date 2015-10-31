import java.util.HashSet;

public class Solution {
    public boolean isHappy(int n) {
        HashSet<Integer> set = new HashSet<Integer>();
        while (n != 1 && !set.contains(n)) {
            int next = 0;
            set.add(n);
            while (n != 0) {
                int b = n % 10;
                n /= 10;
                next += b*b;
            }
            n = next;
        }
        return n == 1;
    }
}
