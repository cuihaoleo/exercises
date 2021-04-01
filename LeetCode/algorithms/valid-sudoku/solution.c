bool isValidSudoku(char** board, int boardSize, int* boardColSize) {
    bool bucket[10];

    for (int k=0; k<9; k++) {
        // check 3x3
        int top = (k / 3) * 3;
        int left = (k % 3) * 3;
        memset(bucket, 0, sizeof(bucket));
        for (int i=top; i<top+3; i++)
            for (int j=left; j<left+3; j++) {
                char chr = board[i][j];
                if (chr != '.') {
                    if (bucket[chr - '0'])
                        return false;
                    else
                        bucket[chr - '0'] = true;
                }
            }

        // check row
        memset(bucket, 0, sizeof(bucket));
        for (int i=0; i<9; i++) {
            char chr = board[k][i];
            if (chr != '.') {
                if (bucket[chr - '0'])
                    return false;
                else
                    bucket[chr - '0'] = true;
            }
        }
        
        // check column
        memset(bucket, 0, sizeof(bucket));
        for (int i=0; i<9; i++) {
            char chr = board[i][k];
            if (chr != '.') {
                if (bucket[chr - '0'])
                    return false;
                else
                    bucket[chr - '0'] = true;
            }
        }
    }
    
    return true;
}
