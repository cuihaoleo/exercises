#include <ctype.h>

int lengthOfLastWord(char * s){
    int result = 0;

    while (*s) {
        while (*s == ' ')
            s++;
        
        if (isalpha(*s)) {
            result = 0;
            for (; isalpha(*s); s++)
                result++;
        }
    }
    
    return result;
}
