from collections import Counter

class Solution:
    def commonChars(self, words: List[str]) -> List[str]:
        char_counter = Counter(words[0])

        for word in words[1:]:
            char_counter &= Counter(word)

        result = []

        for char, count in char_counter.items():
            result.extend(char * count)

        return result
