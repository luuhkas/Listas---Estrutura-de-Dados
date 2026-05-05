#include <stdio.h>
#include <stdlib.h>
#include "fila_headers.h"

void reverso(Fila *fila)
{
    if (fila == NULL || fila->inicio == NULL)
        return;

    Node *anterior = NULL;
    Node *atual = fila->inicio;
    Node *proximo = NULL;

    fila->fim = fila->inicio;

    while (atual != NULL)
    {
        proximo = atual->next;
        atual->next = anterior;
        anterior = atual;
        atual = proximo;
    }

    fila->inicio = anterior;
}

int main(void)
{
    Fila *fila = criarFila();

    for (int i = 1; i <= 5; i++)
        enqueue(fila, i);

    printf("Fila antes do reverso:\n");
    imprimirFila(fila);

    reverso(fila);

    printf("\nFila depois do reverso:\n");
    imprimirFila(fila);

    return 0;
}

/*
Nesse exercicio eu inverti os ponteiros dos nos da fila.
O inicio antigo vira o fim, e conforme eu vou andando pela fila, cada no passa a
apontar para o anterior. No final, o ultimo no vira o novo inicio.
*/
