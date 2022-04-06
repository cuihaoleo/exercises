class LinkListNode:
    def __init__(self, prev, next, data):
        self.prev = prev
        self.next = next
        self.data = data

    def detach(self):
        if self.prev:
            self.prev.next = self.next
        if self.next:
            self.next.prev = self.prev

    def insert(self, new_node):
        if self.next:
            self.next.prev = new_node

        new_node.next = self.next
        new_node.prev = self
        self.next = new_node


class LRUCache:
    def __init__(self, capacity: int):
        self.capacity = capacity
        self.map = dict()

        self.head = LinkListNode(None, None, None)
        self.tail = LinkListNode(None, None, None)
        self.head.insert(self.tail)

    def get(self, key: int) -> int:
        try:
            node = self.map[key]
        except KeyError:
            return -1
        else:
            node.detach()
            self.head.insert(node)
            return node.data[1]

    def put(self, key: int, value: int) -> None:
        if key in self.map:
            self.map[key].data = (key, value)
            self.get(key)
        else:
            if len(self.map) == self.capacity:
                evicted_node = self.tail.prev
                evicted_node.detach()
                self.map.pop(evicted_node.data[0])

            self.map[key] = new_node = LinkListNode(None, None, (key, value))
            self.head.insert(new_node)
