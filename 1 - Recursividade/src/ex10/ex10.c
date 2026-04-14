#include <stdio.h>

void recursive0ToN(int n)
{
    if (n < 0) // caso base
        return;

    printf("%d ", n);
    recursive0ToN(n - 1); // chamda recursiva
}

int main (void)
{
    recursive0ToN(33);
    printf("\n");
    return 0;
}