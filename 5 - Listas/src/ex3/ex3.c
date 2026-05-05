#include <stdio.h>
#include <stdlib.h>
#include "lista_headers.h"

int inserirPosicao(Lista *lista, int data, int posicao)
{
    if (lista == NULL || posicao < 0)
        return 1;

    if (posicao == 0)
        return inserirInicio(lista, data);

    Node *anterior = *lista;

    for (int i = 0; anterior != NULL && i < posicao - 1; i++)
        anterior = anterior->next;

    if (anterior == NULL)
        return 1;

    Node *node = malloc(sizeof(Node));
    if (node == NULL)
        return 1;

    node->data = data;
    node->next = anterior->next;
    anterior->next = node;

    return 0;
}

int main(void)
{
    Lista *lista = criarLista();

    inserirFim(lista, 1);
    inserirFim(lista, 2);
    inserirFim(lista, 4);

    printf("Antes da insercao:\n");
    imprimirLista(lista);

    inserirPosicao(lista, 3, 2);

    printf("\nDepois da insercao:\n");
    imprimirLista(lista);

    return 0;
}

/*
Nesse exercicio eu precisei andar ate o no anterior da posicao desejada.
Depois disso foi so criar o novo no, apontar ele para o proximo, e fazer o anterior
apontar para ele. O caso da posicao zero ficou separado porque muda o inicio da lista.
*/
