#include <stdio.h>
#include <stdlib.h>
#include "pilha_headers.h"

void max_min_media(Pilha *pilha)
{
    if (pilha == NULL)
    {
        printf("Erro de alocacao de memoria\n");
        return;
    }

    int maior, menor, media = 0, soma = 0, count = 0;
    Node *node;
    if ((node = malloc(sizeof(Node))) == NULL)
    {
        printf("Erro de alocacao de memoria");
        return;
    }

    node = pilha->topo;
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

    printf("\nO maior elemento da pilha eh: %d\n", maior);
    printf("\nO menor elemento da pilha eh: %d\n", menor);
    printf("\nA media dos elementos da pilha eh: %d\n", media);
}

int main(void)
{
    Pilha *pilha = criarPilha();
    for (int i = 2; i < 4; i++)
        push(pilha, i);

    printf("Pilha depois do push:\n");
    imprimirPilha(pilha);

    max_min_media(pilha);

    return 0;
}