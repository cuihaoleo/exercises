# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None


class FreeObject(object):
    pass


class Solution:
    # @param {ListNode} l1
    # @param {ListNode} l2
    # @return {ListNode}
    def addTwoNumbers(self, l1, l2):
        bk = l3 = FreeObject()
        rest = 0
        while l1 or l2 or rest:
            su = (l1.val if l1 else 0) + (l2.val if l2 else 0) + rest
            l3.next = ListNode(su % 10)
            rest = (0, 1)[su >= 10]
            l3 = l3.next
            l1 = l1.next if l1 else None
            l2 = l2.next if l2 else None
        return bk.next
