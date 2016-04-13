#include "stdio.h"
#include "stdlib.h"

long long fact(long long a){
    if( a == 0 ) return 1;
    else if( a == 1 ) return 1;
    return fact(a-1) + fact(a-2);
}
int main()
{
    long long  a = 4;
    long long  b = fact(a);
    printf("%lld\n", b);
}
