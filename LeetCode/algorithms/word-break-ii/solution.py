class Solution:
    # @param s, a string
    # @param wordDict, a set<string>
    # @return a boolean
    def wordBreak(self, s, wordDict):
        dym = [[-1]]
        wordList = list(wordDict)

        for i in range(1, len(s)+1):
            dym.append([])
            for j, word in enumerate(wordDict):
                l = len(word)
                if l <= i and dym[i-l] and s.find(word, i-l, i) >= 0:
                    dym[-1].append(j)

        ans = []
        stack = []

        def dfs(wh):
            if wh == 0:
                ans.append(' '.join(reversed(stack)))
                return

            for word_index in dym[wh]:
                word = wordList[word_index]
                stack.append(word)
                dfs(wh - len(word))
                stack.pop()

        dfs(len(s))
        return ans
