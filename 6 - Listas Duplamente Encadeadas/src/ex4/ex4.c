#include <stdio.h>
#include <stdlib.h>
#include "lista_dupla_headers.h"

int inserirInicioCircular(Lista *lista, int data)
{
    if (lista == NULL)
        return 1;

    Node *node = malloc(sizeof(Node));
    if (node == NULL)
        return 1;

    node->data = data;

    if (*lista == NULL)
    {
        node->prox = node;
        node->ant = node;
        *lista = node;
    }
    else
    {
        Node *ultimo = (*lista)->ant;
        node->prox = *lista;
        node->ant = ultimo;
        ultimo->prox = node;
        (*lista)->ant = node;
        *lista = node;
    }

    return 0;
}

int inserirFimCircular(Lista *lista, int data)
{
    if (lista == NULL)
        return 1;

    Node *node = malloc(sizeof(Node));
    if (node == NULL)
        return 1;

    node->data = data;

    if (*lista == NULL)
    {
        node->prox = node;
        node->ant = node;
        *lista = node;
    }
    else
    {
        Node *ultimo = (*lista)->ant;
        node->prox = *lista;
        node->ant = ultimo;
        ultimo->prox = node;
        (*lista)->ant = node;
    }

    return 0;
}

int removerInicioCircular(Lista *lista)
{
    if (lista == NULL || *lista == NULL)
        return 1;

    Node *node = *lista;

    if (node->prox == node)
    {
        *lista = NULL;
    }
    else
    {
        Node *ultimo = node->ant;
        *lista = node->prox;
        ultimo->prox = *lista;
        (*lista)->ant = ultimo;
    }

    free(node);
    return 0;
}

int removerFimCircular(Lista *lista)
{
    if (lista == NULL || *lista == NULL)
        return 1;

    Node *node = (*lista)->ant;

    if (node->prox == node)
    {
        *lista = NULL;
    }
    else
    {
        Node *penultimo = node->ant;
        penultimo->prox = *lista;
        (*lista)->ant = penultimo;
    }

    free(node);
    return 0;
}

void percorrerListaCircular(Lista *lista)
{
    if (lista == NULL || *lista == NULL)
        return;

    Node *node = *lista;

    do
    {
        printf("Dado: %d\n", node->data);
        node = node->prox;
    } while (node != *lista);
}

void liberarListaCircular(Lista *lista)
{
    if (lista == NULL)
        return;

    while (*lista != NULL)
        removerInicioCircular(lista);

    free(lista);
}

int main(void)
{
    Lista *lista = criarLista();

    inserirFimCircular(lista, 10);
    inserirFimCircular(lista, 20);
    inserirInicioCircular(lista, 5);
    inserirFimCircular(lista, 30);

    printf("Lista circular:\n");
    percorrerListaCircular(lista);

    removerInicioCircular(lista);
    removerFimCircular(lista);

    printf("\nLista depois das remocoes:\n");
    percorrerListaCircular(lista);

    liberarListaCircular(lista);
    return 0;
}

/*
Aqui eu usei a estrutura da base, mas refiz as funcoes para a lista ficar circular.
O ultimo aponta para o primeiro e o primeiro aponta para o ultimo, entao inserir e
remover precisa manter essa ligacao funcionando.
*/
