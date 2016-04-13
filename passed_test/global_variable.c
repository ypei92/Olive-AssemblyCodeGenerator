#include "stdio.h"
#include "stdlib.h"
long long d = 20;
long long e = 30;
long long f = 40;

int main()
{
    long long a = 2;
    long long b;
    b = 3;
    long long c = 4;

    d = a+d;
    e = b+e;
    f = c+f;

    printf("%lld\n", d);
    printf("%lld\n", e);
    printf("%lld\n", f);
}
