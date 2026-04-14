#include <stdio.h>

int recursiveSumInt(int n)
{
    if (n == 1) // caso base
        return 1;
    return n + recursiveSumInt(n - 1); // chamada recursiva
}

int main(void)
{
    int n = 7;

    printf("%d", recursiveSumInt(n));
    return 0;
}