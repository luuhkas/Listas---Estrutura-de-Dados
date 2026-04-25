#include <stdio.h>
#include "fila_headers.h"

int main(void)
{
    Fila *fila = criarFila();

    enqueue(fila, 1);
    enqueue(fila, 2);
    enqueue(fila, 3);

    printf("Fila base do exercicio 5:\n");
    imprimirFila(fila);

    return 0;
}
