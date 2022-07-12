class Solution:
    def balancedStringSplit(self, s: str) -> int:
        pos = count = 0

        for char in s:
            if char == 'R':
                pos += 1
            else:
                pos -= 1

            if pos == 0:
                count += 1

        return count
