from collections import defaultdict

class Solution:
    def canCross(self, stones: List[int]) -> bool:
        # next jumps from stone[i]
        next_jumps = [set() for _ in stones]
        next_jumps[0].add(1)

        reachability = [False] * len(stones)
        reachability[0] = True

        for curr_stone in range(len(stones)):
            if reachability[curr_stone] is False:
                continue

            for next_stone in range(curr_stone + 1, len(stones)):
                dist = stones[next_stone] - stones[curr_stone]

                # if next stone is reachable
                if dist in next_jumps[curr_stone]:
                    if reachability[next_stone] is False:
                        if next_stone == len(stones) - 1:
                            return True

                        reachability[next_stone] = True

                    # next jump from this stones will be
                    next_jumps[next_stone].update(range(dist - 1, dist + 2))

        return False
