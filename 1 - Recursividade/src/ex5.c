#include <stdio.h>
#include <stdlib.h>

void recursiveArray100Real(int *array, int tam)
{
    if (tam == 0) // caso base
        return;

    recursiveArray100Real(array + 1, tam - 1); // chamada recursiva
    printf("%d ", *array);
}

int main(void)
{
    int array[100] =
        {42, 7, 89, 13, 65, 21, 90, 34, 56, 78,
         12, 99, 3, 47, 68, 25, 84, 16, 73, 51,
         60, 5, 92, 38, 27, 71, 44, 18, 63, 80,
         9, 55, 31, 74, 2, 97, 46, 67, 14, 88,
         29, 53, 76, 11, 40, 62, 8, 95, 24, 70,
         36, 81, 4, 59, 22, 93, 48, 66, 15, 79,
         32, 54, 87, 10, 41, 69, 26, 75, 6, 98,
         35, 57, 83, 19, 64, 28, 91, 43, 72, 50,
         1, 77, 33, 58, 86, 20, 61, 30, 94, 17,
         45, 82, 23, 49, 96, 37, 52, 85, 39, 100};

    recursiveArray100Real(array, 100);
    return 0;
}