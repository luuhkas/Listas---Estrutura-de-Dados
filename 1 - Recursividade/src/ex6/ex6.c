#include <stdio.h>

int recursiveMDCxy(int x, int y)
{
    if (y == 0) // caso base
        return x;

    return recursiveMDCxy(y, x % y); // chamada recursiva
}

int main (void)
{
    printf("%d\n", recursiveMDCxy(36, 45));
    return 0;
}