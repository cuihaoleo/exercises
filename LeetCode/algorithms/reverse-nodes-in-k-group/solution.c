#include <stdio.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* reverseKGroup(struct ListNode* head, int k) {
    struct ListNode *p = head;
    struct ListNode *newhead = NULL;
    struct ListNode *prev_last = NULL;

    if (!head || k == 1)
        return head;

    while (p) {
        int left = k;
        struct ListNode *first = p;

        while (left > 1 && p->next != NULL) {
            p = p->next;
            left--;
        }

        if (left != 1) break;

        struct ListNode *last = p;
        struct ListNode *next_first = p->next;
        struct ListNode *prev = p->next;
        struct ListNode *q = first;

        if (newhead == NULL) newhead = last;
        p = prev;

        while (q != next_first) {
            struct ListNode *next = q->next;
            q->next = prev;
            prev = q;
            q = next;
        }

        if (prev_last) prev_last -> next = last;
        prev_last = first;
    }

    return newhead == NULL ? head : newhead;
}

int main() {
    struct ListNode nodes[4];
    struct ListNode *head;
    for (int i=0; i<4; i++) {
        nodes[i].val = i+1;
        nodes[i].next = nodes + i + 1;
    }

    nodes[3].next = NULL;
    head = reverseKGroup(nodes, 2);

    for (struct ListNode *p = head; p != NULL; p = p->next)
        printf("%d->", p->val);
    printf("NULL\n");

    return 0;
}
