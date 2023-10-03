#include <stdio.h>
#include <stdlib.h>

int fat(int n);

int main(int argc, char *argv[])
{
    printf("%d\n", fat(atoi(argv[1])));
    return 0;
}