#include <stdio.h>
#include <stdlib.h>
#include "lista_headers.h"

Lista *criarLista()
{
    Lista *lista;
    if ((lista = malloc(sizeof(Lista))) == NULL)
    {
        printf("Erro de alocacao de memoria\n");
        return NULL;
    }

    *lista = NULL;
    return lista;
}

void liberarLista(Lista *lista)
{
    if (lista == NULL)
        return;

    Node *node;
    while (*lista != NULL)
    {
        node = *lista;
        *lista = node->next;
        free(node);
    }

    free(lista);
}

int inserirFim(Lista *lista, int data)
{
    if (lista == NULL)
        return 1;

    Node *node;
    if ((node = malloc(sizeof(Node))) == NULL)
    {
        printf("Erro de alocacao de memoria\n");
        return 1;
    }

    node->data = data;
    node->next = NULL;

    if (*lista == NULL)
    {
        *lista = node;
        return 0;
    }

    Node *aux = *lista;
    while (aux->next != NULL)
        aux = aux->next;

    aux->next = node;
    return 0;
}

int inserirInicio(Lista *lista, int data)
{
    if (lista == NULL)
        return 1;

    Node *node;
    if ((node = malloc(sizeof(Node))) == NULL)
    {
        printf("Erro de alocacao de memoria\n");
        return 1;
    }

    node->data = data;
    node->next = *lista;
    *lista = node;

    return 0;
}

int inserirOrdenado(Lista *lista, int data)
{
    if (lista == NULL)
        return 1;

    Node *node;
    if ((node = malloc(sizeof(Node))) == NULL)
    {
        printf("Erro de alocacao de memoria\n");
        return 1;
    }

    node->data = data;

    if (*lista == NULL || (*lista)->data >= data)
    {
        node->next = *lista;
        *lista = node;
        return 0;
    }

    Node *anterior = *lista;
    Node *atual = (*lista)->next;

    while (atual != NULL && atual->data < data)
    {
        anterior = atual;
        atual = atual->next;
    }

    node->next = atual;
    anterior->next = node;
    return 0;
}

void imprimirLista(Lista *lista)
{
    if (lista == NULL)
        return;

    Node *node = *lista;
    while (node != NULL)
    {
        printf("Dado: %d\n", node->data);
        node = node->next;
    }
}

int removerValor(Lista *lista, int data)
{
    if (lista == NULL || *lista == NULL)
        return 1;

    Node *anterior = NULL;
    Node *node = *lista;

    while (node != NULL && node->data != data)
    {
        anterior = node;
        node = node->next;
    }

    if (node == NULL)
        return 1;

    if (anterior == NULL)
        *lista = node->next;
    else
        anterior->next = node->next;

    free(node);
    return 0;
}

int removerInicio(Lista *lista)
{
    if (lista == NULL || *lista == NULL)
        return 1;

    Node *node = *lista;
    *lista = node->next;

    free(node);
    return 0;
}

int removerFim(Lista *lista)
{
    if (lista == NULL || *lista == NULL)
        return 1;

    Node *anterior = NULL;
    Node *node = *lista;

    while (node->next != NULL)
    {
        anterior = node;
        node = node->next;
    }

    if (anterior == NULL)
        *lista = NULL;
    else
        anterior->next = NULL;

    free(node);
    return 0;
}

int tamanhoLista(Lista *lista)
{
    if (lista == NULL)
        return 0;

    int count = 0;
    Node *node = *lista;

    while (node != NULL)
    {
        count++;
        node = node->next;
    }

    return count;
}

int listaVazia(Lista *lista)
{
    return lista == NULL || *lista == NULL;
}

int listaCheia(Lista *lista)
{
    (void)lista;
    return 0;
}
