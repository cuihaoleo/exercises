/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2){
    struct ListNode head, *p_out, *p1, *p2;

    p_out = &head;
    p_out->next = NULL;

    p1 = l1;
    p2 = l2;

    while (p1 && p2) {
        if (p1->val <= p2->val) {
            p_out->next = p1;
            p1 = p1->next;
        } else {
            p_out->next = p2;
            p2 = p2->next;
        }
        
        p_out = p_out->next;
    }

    p_out->next = p1 ? p1 : p2;
    
    return head.next;
}
