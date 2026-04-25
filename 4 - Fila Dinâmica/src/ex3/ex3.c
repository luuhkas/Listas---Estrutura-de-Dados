#include <stdio.h>
#include <stdlib.h>
#include "fila_headers.h"

Node *nodeRecursivo(Node *node)
{
    if (node == NULL)
        return NULL;

    Node *auxNode;
    if ((auxNode = malloc(sizeof(Node))) == NULL)
        return NULL;

    auxNode->data = node->data;
    auxNode->next = nodeRecursivo(node->next);

    return auxNode;
}

Fila *fila_copia(Fila *fila)
{
    if (fila == NULL)
        return NULL;

    Fila *filaAux = criarFila();
    if (filaAux == NULL)
        return NULL;

    filaAux->inicio = nodeRecursivo(fila->inicio);

    Node *node = filaAux->inicio;
    while (node != NULL && node->next != NULL)
        node = node->next;

    filaAux->fim = node;
    return filaAux;
}

int main(void)
{
    Fila *fila = criarFila();
    for (int i = 0; i < 4; i++)
        enqueue(fila, i);

    printf("Depois do enqueue:\n");
    imprimirFila(fila);

    printf("Depois da copia:\n");
    Fila *copia = fila_copia(fila);
    imprimirFila(copia);

    return 0;
}

/*
A copia percorre os nos mantendo a mesma ordem da fila original.
Depois da copia dos nos, o ponteiro fim precisa apontar para o ultimo no copiado.
*/
