#include <stdio.h>

int recursiveSumInt(int *vet, int size)
{
    if (size <= 0) // caso base
        return 0;
    return vet[size - 1] + recursiveSumInt(vet, size - 1); // chamada recursiva
}

int main(void)
{
    int vet[5] = {1, 2, 3, 4, 5};
    printf("%d\n", recursiveSumInt(vet, 5));
    return 0;
}