#include <stdio.h>
#include "fila_headers.h"

int main(void)
{
    Fila *fila = criarFila();

    enqueue(fila, 100);
    enqueue(fila, 200);

    printf("Fila base do exercicio 9:\n");
    imprimirFila(fila);

    return 0;
}
