class Solution:
    # @param {string} s
    # @return {string[]}
    def restoreIpAddresses(self, s):

        def dfs(prev, left, dp):
            if dp == 3:
                this = left
                if int(this) < 256 and (this[0] != '0' or this == '0'):
                    ans.append(prev + left)
                return

            for i in range(1, min(len(left), 4)):
                this = left[:i]
                if int(this) < 256 and (this[0] != '0' or this == '0'):
                    dfs(prev+left[:i]+".", left[i:], dp+1)

        ans = []
        dfs("", s, 0)
        return ans
