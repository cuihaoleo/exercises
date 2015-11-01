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
    public ListNode detectCycle(ListNode head) {
        ListNode pa, pb;

        for (pa = pb = head; pb!=null && pb.next!=null; ) {
            pa = pa.next;
            pb = pb.next.next;
            
            if (pa == pb) {
                pb = head;
                while (pa != pb) {
                    pa = pa.next;
                    pb = pb.next;
                }
                return pa;
            }
        }
        
        return null;
    }
}
