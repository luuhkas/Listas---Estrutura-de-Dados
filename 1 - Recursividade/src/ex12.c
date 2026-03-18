#include <stdio.h>
#include <stdlib.h>

int doubleFactorial(int n)
{
    if (n % 2 == 0)
    {
        printf("Digite um numero impar");
        exit(1);
    }
    if (n == 1) // caso base
        return n;

    return n * doubleFactorial(n -2); // chamada recursiva
}

int main (void)
{
    printf("%d\n", doubleFactorial(5));
    return 0;
}