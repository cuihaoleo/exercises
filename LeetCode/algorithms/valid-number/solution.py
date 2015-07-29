import re
class Solution:
    # @param {string} s
    # @return {boolean}
    def isNumber(self, s):
        return bool(re.match(
            r"^\s*[+-]?(\d+[.]?\d*|[.]\d+)([eE][+-]?\d+)?\s*$", s))
