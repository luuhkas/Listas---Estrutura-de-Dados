#include <stdio.h>

void recursiveNEven(int n)
{
    if (n % 2 != 0)
    {
        printf("O input so aceita numeros pares");
        return;
    }
    if (n == 0)
        return;
    
    printf("%d ", n);
    recursiveNEven(n -2);
}

int main(void)
{
    recursiveNEven(20);
    return 0;
}