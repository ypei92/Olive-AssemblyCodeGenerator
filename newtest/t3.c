#include "stdio.h"
#include "stdlib.h"
long long anotherfoo(long long a, long long b) {
    long long c = a + b;
    long long d = a + b + c;
    return c;
}

long long foo(long long a, long long b, long long c){
    long long e = a;
    long long f = b;
    long long g = anotherfoo(e,f);
    return e + f + g;
}

int main()
{
    long long a = 0;
    long long b;

    b = 2;

    long long c = a+b;
    long long d = c+a;
    long long e = c+b;
    long long f = foo(c, d, e);
}
