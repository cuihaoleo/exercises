/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


struct ListNode* swapPairs(struct ListNode* head){
    if (head && head->next) {
        struct ListNode *p1, *p2;
        p1 = head;
        p2 = head->next;
        p1->next = swapPairs(p2->next);
        p2->next = p1;

        return p2;
    } else {
        return head;
    }
}
