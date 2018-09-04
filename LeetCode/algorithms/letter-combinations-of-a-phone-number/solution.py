import itertools

class Solution:
    def letterCombinations(self, digits):
        """
        :type digits: str
        :rtype: List[str]
        """
        if digits == "":
            return []
 
        maps = ["", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"]
        result = []
        for ss in itertools.product(*(maps[int(i)] for i in digits)):
            result.append("".join(ss))
        return result
