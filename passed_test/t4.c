#include "stdio.h"
#include "stdlib.h"

int main()
{
    long long a = 5;
    long long b;

    b = 2;
    long long c =  ( a +  b ) * (a-b);
    printf("%lld\n",c);

    return 0;
//  int d = c+a;
//  int e = c+b;

}
