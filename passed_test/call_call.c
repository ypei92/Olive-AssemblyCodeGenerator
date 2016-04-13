#include "stdio.h"
#include "stdlib.h"

long long foo(long long a,long long b,long long c,long long d,
              long long e,long long f,long long g,long long h, long long i){
    return a + b + c + d + e + f + g + h + i;
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
    long long i = 9;

    long long res = foo(a,b,c,d,e,f,g,h,i);
    long long res1= foo(i,h,g,f,e,d,c,b,a);

    printf("%lld\n",res);
    printf("%lld\n",res1);

    return 0;
}
