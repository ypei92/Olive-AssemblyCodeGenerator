#include "stdio.h"
#include "stdlib.h"

long long anotherfoo(long long a, long long b) {
    long long c = a + b;
    long long d = a + b + c;
    printf("%lld\n",a);
    printf("%lld\n",b);
    printf("%lld\n",c);
    printf("%lld\n",d);
    return c;
}

long long foo(long long a, long long b, long long c){
    long long e = a;
    long long f = b;
    long long g = anotherfoo(e,f);
    printf("%lld\n",e);
    printf("%lld\n",f);
    printf("%lld\n",g);
    return e + f + g;
}

int main()
{
    long long a = 1;
    long long b;

    b = 2;

    long long c = a+b;
    long long d = c+a;
    long long e = c+b;
    long long f = foo(c, d, e);


    printf("%lld\n",c);
    printf("%lld\n",d);
    printf("%lld\n",e);
    printf("%lld\n",f);

    return 0;
}
