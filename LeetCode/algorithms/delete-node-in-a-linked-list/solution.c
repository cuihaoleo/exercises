/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
void deleteNode(struct ListNode* node) {
    struct ListNode* succ = node->next;
    node->val = succ->val;
    node->next = succ->next;
    free(succ);
}