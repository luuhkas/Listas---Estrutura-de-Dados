#include <stdio.h>
#include "fila_headers.h"

int main(void)
{
    Fila *fila = criarFila();

    enqueue(fila, 5);
    enqueue(fila, 6);

    printf("Fila base do exercicio 8:\n");
    imprimirFila(fila);

    return 0;
}
