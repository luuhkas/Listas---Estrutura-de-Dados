#include <stdio.h>

int K_in_N(int k, int n)
{
    if (n == 0) // caso base
        return 0;

    if (k == n % 10)
        return 1 + K_in_N(k, n / 10); // chamada recursiva quando for =

    return K_in_N(k, n / 10); // chamada recursiva quando for !=
}

int main(void)
{
    printf("%d\n", K_in_N(2, 262021192));
    return 0;
}