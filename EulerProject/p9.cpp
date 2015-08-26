#include <iostream>

using namespace std;

int main ()
{
    int a, b, c;
    for (a=1; a<999; a++)
        for (b=a; b<1000-a; b++)
        {
            c = 1000-b-a;
            if (a*a + b*b == c*c)
                goto out;
        }

out:
    cout << a*b*c << endl;

    return 0;
}
