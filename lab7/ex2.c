#include <stdio.h>
char S2[] = {65, 108, 111, 32, 123, 103, 97, 108, 101, 114, 97, 125, 33, 0};
int main(void)
{
    char *pc = S2;
    while (*pc)
    {
        if (*pc != '{' && *pc != '}')
            printf("%c", *pc);
        pc++;
    }
    printf("\n");
    return 0;
}