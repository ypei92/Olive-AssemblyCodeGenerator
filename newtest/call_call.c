#include "stdio.h"
#include "stdlib.h"

long long foo(long long a,long long b,long long c,long long d,
              long long e,long long f,long long g,long long h){

    printf("%lld\n",a);
    printf("%lld\n",b);
    printf("%lld\n",c);
    printf("%lld\n",d);
    printf("%lld\n",e);
    printf("%lld\n",f);
    printf("%lld\n",g);
    printf("%lld\n",h);
    return a + b + c + d + e + f + g + h;
}
int main()
{
    long long a = 1;
    long long b;
    b = 2;
    long long c = 3;
    long long d = 4;
    long long e = 5;
    long long f = 6;
    long long g = 7;
    long long h = 8;

    long long res = foo(a,b,c,d,e,f,g,h);
    long long res1= foo(h,g,f,e,d,c,b,a);

    printf("%lld\n",res);
    printf("%lld\n",res1);

    return 0;
}
