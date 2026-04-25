#include <stdio.h>
#include <stdlib.h>
#include "fila_headers.h"

int dequeue2(Fila *fila)
{
    if (fila == NULL || fila->inicio == NULL || fila->inicio->next == NULL)
        return 1;

    for (int i = 0; i < 2; i++)
        dequeue(fila);

    return 0;
}

int enqueue2(Fila *fila, int data)
{
    if (fila == NULL)
        return 1;

    for (int i = 0; i < 2; i++)
    {
        if (enqueue(fila, data) != 0)
            return 1;
    }

    return 0;
}

int main(void)
{
    Fila *fila = criarFila();

    enqueue2(fila, 2);
    printf("Apos o enqueue2:\n");
    imprimirFila(fila);

    dequeue2(fila);
    printf("Apos o dequeue2:\n");
    imprimirFila(fila);

    return 0;
}

/*
Parecido com o exercicio de pilha, mas na fila a insercao acontece no fim
e a remocao acontece no inicio.
*/
