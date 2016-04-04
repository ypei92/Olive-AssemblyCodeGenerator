#include "stdio.h"
#include "stdlib.h"

int main()
{
    int a = 0;
    int b;

    b = 2;

    int c = a+b;
    int d = c+a;
    int e = c+b;

    printf("%d %d %d\n", c, d, e);
}
