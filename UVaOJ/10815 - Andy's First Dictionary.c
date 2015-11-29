#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *wordlist[100000];
int ji = 0;

int cmp (const void *pa, const void *pb)
{
    return strcmp(*(char**)pa, *(char**)pb);
}

int main()
{
    char c, inword = 0, nw[100];
    int ct;

    while ((c = getchar()) != EOF)
    {
        if (isalpha(c))
        {
            if (!inword)
                inword = 1, ct=0;
            nw[ct++] = tolower(c);
        }
        else if (!isalpha(c) && inword)
        {
            inword = nw[ct++] = 0;
            wordlist[ji] = (char*) malloc(ct*sizeof(char));
            strcpy(wordlist[ji], nw);
            ji++;
        }
    }

    qsort(wordlist, ji, sizeof(char*), cmp);
    wordlist[ji] = "";

    for (ct=0; ct<ji; ct++)
        if (strcmp(wordlist[ct], wordlist[ct+1]))
            puts(wordlist[ct]);

    return 0;
}

