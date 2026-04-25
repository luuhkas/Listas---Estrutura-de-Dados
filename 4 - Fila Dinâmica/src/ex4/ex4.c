#include <stdio.h>
#include <stdlib.h>
#include "fila_headers.h"

void max_min_media(Fila *fila)
{
    if (fila == NULL || fila->inicio == NULL)
    {
        printf("Fila vazia ou invalida\n");
        return;
    }

    int maior, menor, media, soma = 0, count = 0;
    Node *node = fila->inicio;

    maior = menor = node->data;

    while (node != NULL)
    {
        if (node->data > maior)
            maior = node->data;
        if (node->data < menor)
            menor = node->data;

        soma += node->data;
        count++;
        node = node->next;
    }

    media = soma / count;

    printf("\nO maior elemento da fila eh: %d\n", maior);
    printf("\nO menor elemento da fila eh: %d\n", menor);
    printf("\nA media dos elementos da fila eh: %d\n", media);
}

int main(void)
{
    Fila *fila = criarFila();
    for (int i = 2; i < 4; i++)
        enqueue(fila, i);

    printf("Fila depois do enqueue:\n");
    imprimirFila(fila);

    max_min_media(fila);

    return 0;
}
