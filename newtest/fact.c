#include "stdio.h"
#include "stdlib.h"
int fact(int a){
    if( a == 0 ) return 1;
    else if( a == 1 ) return 1;
    return fact(a-1) + fact(a-2);
}
int main()
{
    int a = 4;
    int b = fact(a);
}
