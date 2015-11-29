#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

double exnum (char *s)
{
    char *p;
    double fa;

    for (p=s; isdigit(*p) || *p=='.'; p++)
        ;

    switch (*p)
    {
        case 'M': fa = 1000000; break;
        case 'k': fa = 1000; break;
        case 'm': fa = 0.001; break;
        default:  fa = 1;
    }

    *p = '\0';
    return atof(s) * fa;
}

void solve ()
{
    char s[1000], *p;
    int i;
    struct {
        char name;
        double value;
    } pu[2], tp;

    fgets(s, 1000, stdin);

    for (i=0, p=s; i<2; i++)
    {
        for (; *p!='='; p++)
            ;
             
        pu[i].name = p[-1];
        pu[i].value = exnum(++p);
    }

    if (pu[0].name > pu[1].name)
    {
        tp = pu[0];
        pu[0] = pu[1];
        pu[1] = tp;
    }

    if (pu[0].name == 'I' &&
        pu[1].name == 'P')
        printf("U=%.2lfV\n", pu[1].value / pu[0].value);
    if (pu[0].name == 'I' &&
        pu[1].name == 'U')
        printf("P=%.2lfW\n", pu[0].value * pu[1].value);
    if (pu[0].name == 'P' &&
        pu[1].name == 'U')
        printf("I=%.2lfA\n", pu[0].value / pu[1].value);
}

int main ()
{
    int n, i;

    scanf("%d", &n);
    getchar();
    for (i=1; i<=n; i++)
    {
        printf("Problem #%d\n", i);
        solve();
        putchar('\n');
    }

    return 0;
}
    
