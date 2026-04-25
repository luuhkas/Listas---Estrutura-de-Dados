#include <stdio.h>
#include "fila_headers.h"

int main(void)
{
    Fila *fila = criarFila();

    enqueue(fila, 1);
    enqueue(fila, 2);

    printf("Fila base do exercicio 6:\n");
    imprimirFila(fila);

    return 0;
}
