#include <stdio.h>
#include <stdlib.h>
#include "fila_headers.h"

int dequeueN(Fila *fila, int n)
{
    if (fila == NULL || n <= 0)
        return 1;

    Node *node = fila->inicio;
    for (int i = 0; i < n; i++)
    {
        if (node == NULL)
            return 1;

        node = node->next;
    }

    for (int i = 0; i < n; i++)
        dequeue(fila);

    return 0;
}

int main(void)
{
    Fila *fila = criarFila();
    for (int i = 0; i < 4; i++)
        enqueue(fila, i);

    imprimirFila(fila);
    printf("Depois do enqueue\n");

    dequeueN(fila, 3);
    imprimirFila(fila);
    printf("Depois do dequeueN\n");

    return 0;
}

/*
A ideia eh conferir primeiro se existem N nos para depois remover todos.
Assim a funcao nao remove uma parte da fila e para no meio por falta de nos.
*/
