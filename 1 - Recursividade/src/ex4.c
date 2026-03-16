#include <stdio.h>

int recursiveExpKN(int k, int n)
{
    if (n == 1) // chamada recursiva
        return k;
    return k * recursiveExpKN(k, n - 1);
}

int main(void)
{
    printf("%d\n", recursiveExpKN(2,5));
    return 0;
}