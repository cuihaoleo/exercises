class Solution:
    def partitionLabels(self, s: str) -> List[int]:
        last_appearance = dict()

        for idx, char in enumerate(s):
            last_appearance[char] = idx

        part_start = -1
        part_end = 0
        result = []

        for idx, char in enumerate(s):
            part_end = max(part_end, last_appearance[char])

            if idx == part_end:
                result.append(part_end - part_start)
                part_start = part_end

        return result
