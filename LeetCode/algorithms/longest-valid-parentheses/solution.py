class Solution:
    def longestValidParentheses(self, s: str) -> int:
        longest = [0] * len(s)
        best = 0

        for i, ch in enumerate(s):
            if ch == '(':
                continue

            mirror_pos = i - longest[i-1] - 1
            if mirror_pos >= 0 and s[mirror_pos] == '(':
                longest[i] = longest[i-1] + 2

                if mirror_pos >= 2 and longest[mirror_pos - 1]:
                    longest[i] += longest[mirror_pos - 1]

                if longest[i] > best:
                    best = longest[i]

        return best
