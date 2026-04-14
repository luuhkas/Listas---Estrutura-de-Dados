#include <stdio.h>

int recursiveExpKN(int k, int n)
{
    if (n == 1) // caso base
        return k;
    return k * recursiveExpKN(k, n - 1); // chamada recursiva
}

int main(void)
{
    printf("%d\n", recursiveExpKN(2,5));
    return 0;
}