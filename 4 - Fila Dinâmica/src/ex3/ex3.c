#include <stdio.h>
#include <stdlib.h>
#include "fila_headers.h"

typedef struct pilhaAux
{
    Node *topo;
} PilhaAux;

PilhaAux *criarPilhaAux()
{
    PilhaAux *pilha = malloc(sizeof(PilhaAux));
    if (pilha == NULL)
        return NULL;

    pilha->topo = NULL;
    return pilha;
}

void pushAux(PilhaAux *pilha, int data)
{
    Node *node = malloc(sizeof(Node));
    if (node == NULL)
        return;

    node->data = data;
    node->next = pilha->topo;
    pilha->topo = node;
}

int topoAux(PilhaAux *pilha)
{
    return pilha->topo->data;
}

void popAux(PilhaAux *pilha)
{
    Node *node = pilha->topo;
    pilha->topo = node->next;
    free(node);
}

void inverterFila(Fila *fila)
{
    if (fila == NULL)
        return;

    PilhaAux *pilha = criarPilhaAux();
    if (pilha == NULL)
        return;

    while (fila->inicio != NULL)
    {
        int aux = frente(fila);
        dequeue(fila);
        pushAux(pilha, aux);
    }

    while (pilha->topo != NULL)
    {
        int aux = topoAux(pilha);
        popAux(pilha);
        enqueue(fila, aux);
    }

    free(pilha);
}

int main(void)
{
    Fila *fila = criarFila();

    for (int i = 1; i <= 5; i++)
        enqueue(fila, i);

    printf("Fila antes de inverter:\n");
    imprimirFila(fila);

    inverterFila(fila);

    printf("\nFila depois de inverter:\n");
    imprimirFila(fila);

    return 0;
}

/*
Aqui eu usei a pilha como auxiliar para inverter a fila.
Primeiro tirei todos os elementos da fila e empilhei. Depois desempilhei e enfileirei
de novo. Como a pilha inverte a ordem, a fila volta ao contrario.
*/
