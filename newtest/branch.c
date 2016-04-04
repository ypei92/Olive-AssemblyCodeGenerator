#include "stdio.h"
#include "stdlib.h"

int main()
{
    int a = 1;
    int b;
    b = 2;
    int c = 0;

    if( a + b > 1)
        c = a*b;
    else
        c = b/a;

    printf("%d %d %d\n", a, b, c);
}
