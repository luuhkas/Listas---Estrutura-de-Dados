#include <stdio.h>

int Multip_Rec(int n1, int n2)
{
    if (n2 == 0) // caso base
        return 0;

    return n1 + Multip_Rec(n1, n2 - 1); // chamada recursiva
}

int main(void)
{
    printf("%d\n", Multip_Rec(4, 5));
    return 0;
}