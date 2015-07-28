class Solution:
    # @return a boolean
    def isValid(self, s):
        stack = [None]
        for c in s:
            if c in ['(', '{', '[']:
                stack.append(c)
            elif c == ')':
                if stack.pop() != '(':
                    return False
            elif c == ']':
                if stack.pop() != '[':
                    return False
            elif c == '}':
                if stack.pop() != '{':
                    return False
        return stack[-1] == None
