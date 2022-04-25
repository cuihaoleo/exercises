class Solution:
    def decodeString(self, s: str) -> str:
        stack = []
        result = bytearray()
        num = 0

        for c in s:
            if c.isalpha():
                result.append(ord(c))
            elif c.isdigit():
                num = num * 10 + int(c)
            elif c == '[':
                stack.append((len(result), num))
                num = 0
            elif c == ']':
                start_pos, n_repeat = stack.pop()
                end_pos = len(result)

                for _ in range(n_repeat - 1):
                    result.extend(result[start_pos:end_pos])

        return result.decode()
