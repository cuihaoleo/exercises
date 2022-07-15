# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def reorderList(self, head: Optional[ListNode]) -> None:
        """
        Do not return anything, modify head in-place instead.
        """

        def dfs(node):
            nonlocal insert_loc

            if node is None:
                return

            dfs(node.next)

            node.next = insert_loc.next
            insert_loc.next = node
            insert_loc = node.next

        p1 = p2 = head

        while p2.next:
            p1 = p1.next

            p2 = p2.next

            if p2.next:
                p2 = p2.next

        insert_loc = head
        dfs(p1.next)
        p1.next = None
