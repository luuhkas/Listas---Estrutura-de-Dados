#include <stdio.h>

void recursive_invert(int n)
{
    if (n == 0) return; // caso base
    printf("%d", n % 10);
    recursive_invert(n / 10); // chamada recursiva
}

int main(void)
{
    int n = 123;

    recursive_invert(n);
    printf("/n");
    return 0;
}