#include <stdio.h>

#define SIZE 20

int main ()
{
    int arr[SIZE][SIZE], max = 0, i, j;

    for (i=0; i<SIZE; i++)
        for (j=0; j<SIZE; j++)
        {
            int s;
            scanf("%d", &arr[i][j]);
            
            // left
            if (j >= 3)
            {
                s = arr[i][j-3] * arr[i][j-2] * arr[i][j-1] * arr[i][j];
                if (s > max) max = s;
            }

            // up
            if (i >= 3)
            {
                s = arr[i-3][j] * arr[i-2][j] * arr[i-1][j] * arr[i][j];
                if (s > max) max = s;
            }

            // north-west
            if (i >= 3 && j >= 3)
            {
                s = arr[i-3][j-3] * arr[i-2][j-2] * arr[i-1][j-1] * arr[i][j];
                if (s > max) max = s;
            }

            // north-east
            if (i >= 3 && j <= SIZE-4)
            {
                s = arr[i-3][j+3] * arr[i-2][j+2] * arr[i-1][j+1] * arr[i][j];
                if (s > max) max = s;
            }
        }

    printf("%d\n", max);
    
    return 0;
}
