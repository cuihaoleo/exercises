/**
 * Definition for singly-linked list.
 * class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode(int x) {
 *         val = x;
 *         next = null;
 *     }
 * }
 */
public class Solution {
    public boolean hasCycle(ListNode head) {
        ListNode pa, pb;
        pa = pb = head;
        for (int i=0; pb!=null; i++) {
            pb = pb.next;
            if (pa == pb) {
                return true;
            }
            if (i%2 == 0) {
                pa = pa.next;
            }
        }
        return false;
    }
}
