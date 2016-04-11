#include "stdio.h"
#include "stdlib.h"
int foo(int a, int b, int c){


    return a + b - c;
}
int main()
{
    int a = 0;
    int b;

    b = 2;

    int c = a+b;
    int d = c+a;
    int e = d+b;
    int f = foo(c, d, e);
}
