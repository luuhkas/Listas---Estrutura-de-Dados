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

    if (pilha->topo == NULL)
    {
        printf("A pilha esta vazia\n");
        return;
    }

    int maior, menor, soma = 0, count = 0;
    float media = 0;

    Node *node = pilha->topo;
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
    media = (float)soma / count;

    printf("\nO maior elemento da pilha eh: %d\n", maior);
    printf("\nO menor elemento da pilha eh: %d\n", menor);
    printf("\nA media dos elementos da pilha eh: %.2f\n", media);
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

/*
Esse exercicio foi mais direto, eu so precisei percorrer a pilha com um no auxiliar
e ir comparando para achar o maior e o menor. Para a media, fui somando todos os
valores e contando quantos nos tinham na pilha.
O cuidado maior aqui foi lembrar de tratar a pilha vazia, porque se o topo for NULL
nao da para acessar o data.
*/
