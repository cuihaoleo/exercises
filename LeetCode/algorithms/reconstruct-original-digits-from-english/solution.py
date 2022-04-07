from collections import Counter


class Solution:
    def originalDigits(self, s: str) -> str:
        words = ["zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"]
        char_counter = Counter(s)
        num_counter = [0] * 10

        for char, num in zip("zwuxorfsge", (0, 2, 4, 6, 1, 3, 5, 7, 8, 9)):
            num_counter[num] = num_count = char_counter[char]
            for c in words[num]:
                char_counter[c] -= num_count

        return "".join(str(i) * c for i, c in enumerate(num_counter))
