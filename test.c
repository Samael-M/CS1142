#include <stdio.h>

int main(void)
{
    int a[] = {2, 4, 6, 8, 10};

    for(int* p = &a[3]; p >= a; p = p - 2) {
        printf("%d", *p);
    }
    
    printf("\n");
    return 0;

}