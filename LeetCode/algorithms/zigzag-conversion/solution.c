#include <stdlib.h>
#include <string.h>

char * convert(char * s, int numRows){
    int len = strlen(s);
    int period = 2 * (numRows - 1);
    char *result = malloc(len + 1);
    char *p_out = result;
    
    if (period == 0) {
        strcpy(result, s);
        return result;
    }
    
    for (int i=0; i<len; i+=period)
        *(p_out++) = s[i];

    for (int k=1; k<period/2; k++) {
        int step = k * 2;

        for (int i=k; i<len; i+=step) {
            *(p_out++) = s[i];
            step = period - step;
        }
    }
    
    for (int i=period/2; i<len; i+=period)
        *(p_out++) = s[i];

    *p_out = 0;
    return result;
}
