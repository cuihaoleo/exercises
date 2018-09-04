import heapq


class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None

    def __str__(self):
        cur = self
        elem = []
        while cur is not None:
            elem.append(cur.val)
            cur = cur.next
        return str(elem)


class Solution:
    def mergeKLists(self, lists):
        """
        :type lists: List[ListNode]
        :rtype: ListNode
        """
        h = []
        for idx, node in enumerate(lists):
            if node is not None:
                heapq.heappush(h, (node.val, idx))

        pilot = ListNode(None)
        tail = pilot
        while h:
            val, idx = h[0]
            tail.next = lists[idx]
            tail = tail.next
            lists[idx] = lists[idx].next
            if lists[idx] is not None:
                heapq.heapreplace(h, (lists[idx].val, idx))
            else:
                heapq.heappop(h)

        tail.next = None
        return pilot.next


def main():
    def toLinkList(li):
        tail = pilot = ListNode(None)
        for i in li:
            tail.next = ListNode(i)
            tail = tail.next
        return pilot.next

    inp = [toLinkList([1, 4, 5]),
           toLinkList([1, 3, 4]),
           toLinkList([2, 6])]
    solver = Solution()
    result = solver.mergeKLists(inp)
    print(result)


if __name__ == "__main__":
    main()
