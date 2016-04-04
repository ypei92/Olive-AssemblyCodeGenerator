#include "stdio.h"
#include "stdlib.h"

int main()
{
    int a = 1;
    int b;
    b = 2;
    int c = 0;
    int d = 0;

    for( int i = 0; i < a+b ; i ++) {
        c++;
    }

    while( c > 0 ) {
        a++;
        b--;
        c--;
        for (int i = 0 ; i < c; i++){
            d++;
        }
    }

    printf("%d %d %d %d\n", a, b, c, d);
}
