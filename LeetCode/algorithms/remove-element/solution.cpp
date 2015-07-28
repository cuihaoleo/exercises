class Solution {
public:
    int removeElement(int A[], int n, int elem) {
        int i = 0, j = 0;
        if (n == 0)
            return 0;
        while (j < n) {
            while (j < n && elem == A[j])
                j++;
            if (j < n && elem != A[j])
                A[i++] = A[j++];
        }
        return i;
    }
};
