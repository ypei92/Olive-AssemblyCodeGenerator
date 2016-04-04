#include "stdio.h"
#include "stdlib.h"

int main()
{
    int a = 1;
    int b;
    int *p = &a;
    int *q = &b;
    b = 2;

    int c = a + *p;
    int d = *q + b;
    int e = (*q)*(*p);

    printf("%d %d %d\n", c, d, e);
}
