class Solution {
public:
    int removeDuplicates(int A[], int n) {
        int i = 0, j = 0;
        if (n == 0)
            return 0;
        while (j < n) {
            while (j < n && A[i] == A[j])
                j++;
            if (j < n)
                A[++i] = A[j];
        }
        return i + 1;
    }
};
