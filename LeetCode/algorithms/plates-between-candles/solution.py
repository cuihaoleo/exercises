class Solution:
    def platesBetweenCandles(self, s: str, queries: List[List[int]]) -> List[int]:
        pipe_idx = dict()
        left_pipe = []
        last_pipe_idx = None

        for i, c in enumerate(s):
            if c == "|":
                pipe_idx[i] = len(pipe_idx)
                last_pipe_idx = i
            left_pipe.append(last_pipe_idx)

        right_pipe = [0] * len(s)
        last_pipe_idx = None

        for i in range(len(s) - 1, -1, -1):
            c = s[i]
            if c == "|":
                last_pipe_idx = i
            right_pipe[i] = last_pipe_idx

        ans = []

        for i1, i2 in queries:
            p1 = right_pipe[i1]
            p2 = left_pipe[i2]

            if p1 is None or p2 is None:
                ans.append(0)
                continue

            star_count = max((p2 - p1) - (pipe_idx[p2] - pipe_idx[p1]), 0)
            ans.append(star_count)

        return ans
