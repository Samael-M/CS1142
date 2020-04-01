#include <stdio.h>

int main(void)
{
    int a[10];

    for(int i = 0; i < 10; i++) {
        a[i] = i * i;
    }
    
    int* p = &a[9];
    int* q = p - 2;

    printf("%d", *q);

    p = q + 2;
    printf("%d", *p);
    return 0;

}