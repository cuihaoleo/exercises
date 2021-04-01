# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def removeNthFromEnd(self, head: ListNode, n: int) -> ListNode:
        def goDeep(head):
            if head == None:
                return 1, None

            pos, head.next = goDeep(head.next)
            return pos + 1, head.next if pos == n else head

        return goDeep(head)[1]
