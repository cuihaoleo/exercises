#define R 11
#define S  7
#define T  9

int A[R][S][T];

int store_ele(int i, int j, int k, int *dest) {
    *dest = A[i][j][k];
    return sizeof(A);
}
