class Solution:
    # @return a float
    def findMedianSortedArrays(self, A, B):
        length = len(A) + len(B)
        mark = length / 2 + (-1 if length % 2 == 0 else 0)

        A.append(0xFFFFFFFF)
        B.append(0xFFFFFFFF)

        while mark >= 0:
            num = A.pop(0) if A[0] < B[0] else B.pop(0)
            # print("DEBUG: %d %d" % (mark, num))
            mark -= 1

        if length % 2 == 0:
            num2 = A.pop(0) if A[0] < B[0] else B.pop(0)
            # print("DEBUG: %d %d" % (mark, num2))
            return (num+num2)/2.0

        return num
