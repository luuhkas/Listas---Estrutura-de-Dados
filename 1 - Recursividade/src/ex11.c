#include <stdio.h>

void evenN(int n)
{
    if (n % 2 != 0)
    {
        printf("Digite um numero par\n");
        return;
    }
    if (n < 0) // caso base
        return;

    printf("%d ", n);
    evenN(n - 2); // chamada recursiva
}

int main (void)
{
    evenN(33);
    return 0;
}