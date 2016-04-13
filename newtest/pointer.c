#include "stdio.h"
#include "stdlib.h"

int main()
{
    long long a = 1;
    long long b;
    long long *p = &a;
    long long *q = &b;
    b = 2;

    long long g = a;

    long long c = a + *p;
    long long d = *q + b;
    long long e = (*q)+(*p);
    return 0;
}
