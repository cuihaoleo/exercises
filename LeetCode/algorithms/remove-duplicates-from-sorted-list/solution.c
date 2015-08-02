/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* deleteDuplicates(struct ListNode* head) {
    struct ListNode* p;
    for (p=head; p; p=p->next)
        while (p->next && p->next->val==p->val) {
            struct ListNode* n = p->next;
            p->next = n->next;
            free(n);
        }
    return head;
}
