#include <stdio.h>

void foo(int a[], int n);

int main(void)
{
    int a[] = {1, 2, 3, 4, 0, 5, 0};
    int n = 7;
    foo(a, n);
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
    return 0;
}