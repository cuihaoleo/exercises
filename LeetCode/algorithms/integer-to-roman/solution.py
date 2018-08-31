class Solution:
    WORDS = 'IVXLCDM'

    def _iter(self, num, depth):
        if num == 0:
            return ""

        digit = num % 10

        if digit <= 3:
            s = Solution.WORDS[depth*2] * digit
        elif digit == 4:
            s = Solution.WORDS[depth*2:depth*2+2]
        elif digit <= 8:
            s = Solution.WORDS[depth*2+1] + Solution.WORDS[depth*2] * (digit-5)
        else:
            s = Solution.WORDS[depth*2:depth*2+3:2]

        return self._iter(num//10, depth+1) + s

    def intToRoman(self, num):
        """
        :type num: int
        :rtype: str
        """
        return self._iter(num, 0)

if __name__ == "__main__":
    num = int(input())
    assert 1 <= num <= 3999

    solver = Solution()
    print(solver.intToRoman(num))
