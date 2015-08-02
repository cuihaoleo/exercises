/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode* deleteDuplicates(struct ListNode* head) {
    struct ListNode *p = NULL, *cp = NULL;
    while (head) {
        if (!head->next || head->next->val != head->val) {
            if (cp)
                cp = cp->next = head;
            else
                p = cp = head;

            head = head->next;
        }
        else {
            int val = head->val;
            while (head && head->val == val) {
                struct ListNode* n = head->next;
                free(head);
                head = n;
            }
        }
    }

    cp && (cp->next = NULL);
    return p;
}
