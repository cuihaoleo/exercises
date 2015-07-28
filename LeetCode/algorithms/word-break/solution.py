class Solution:
    # @param s, a string
    # @param wordDict, a set<string>
    # @return a boolean
    def wordBreak(self, s, wordDict):
        dym = [True]
        for i in range(1, len(s)+1):
            dym.append(False)
            for word in wordDict:
                l = len(word)
                if l <= i and dym[i-l] and s.find(word, i-l, i) >= 0:
                    dym[-1] = True
                    break
        return dym[-1]
