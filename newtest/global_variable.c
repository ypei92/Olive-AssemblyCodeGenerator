#include "stdio.h"
#include "stdlib.h"
int d = 20;
long e = 30;
long long f = 40;

int main()
{
    int a = 0;
    int b;

    b = 2;
    int c = 3;

    d = a+d;
    e = b+e;
    f = c+f;

    printf("%d %ld %lld\n", d, e, f);
}
