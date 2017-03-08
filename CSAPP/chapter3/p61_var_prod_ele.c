int var_prod_ele(int n, int A[n][n], int B[n][n], int i, int k) {
    register int j;
    register int result = 0;

    for (j = 0; j < n; j++)
        result += A[i][j] * B[j][k];

    return result;
}

int var_prod_ele2(int n, int A[n][n], int B[n][n], int i, int k) {
    int result = 0;

    for (--n; n >= 0; n--)
        result += A[i][n] * B[n][k];

    return result;
}
