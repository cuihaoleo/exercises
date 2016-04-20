/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

bool isPalindrome(struct ListNode* head) {
    struct ListNode *prev = NULL, *cur = head;
    bool retval = true;

    while (cur != NULL) {
        struct ListNode *next = cur->next;
        cur->next = (uintptr_t)prev ^ (uintptr_t)next;
        prev = cur;
        cur = next;
    }

    struct ListNode *left_cur = head, *left_prev = NULL;
    struct ListNode *right_cur = prev, *right_prev = NULL;

    while (left_cur && right_cur) {
        if (left_cur->val != right_cur->val) {
            retval = false;
            break;
        }

        struct ListNode *left_next = (uintptr_t)left_prev ^ (uintptr_t)left_cur->next;
        struct ListNode *right_next = (uintptr_t)right_prev ^ (uintptr_t)right_cur->next;

        left_prev = left_cur;
        left_cur = left_next;
        right_prev = right_cur;
        right_cur = right_next;
    }

    prev = NULL;
    cur = head;
    while (cur) {
        cur->next = (uintptr_t)prev ^ (uintptr_t)cur->next;
        prev = cur;
        cur = cur->next;
    }

    return retval;
}
