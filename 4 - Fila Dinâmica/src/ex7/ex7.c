#include <stdio.h>
#include "fila_headers.h"

int main(void)
{
    Fila *fila = criarFila();

    enqueue(fila, 10);
    enqueue(fila, 20);

    printf("Fila base do exercicio 7:\n");
    imprimirFila(fila);

    return 0;
}
