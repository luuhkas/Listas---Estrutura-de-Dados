#include <stdio.h>
#include <stdlib.h>

typedef struct nodeFloat
{
    float data;
    struct nodeFloat *next;
} NodeFloat;

typedef NodeFloat *ListaFloat;

void iniciarLista(ListaFloat *lista)
{
    *lista = NULL;
}

void inserirFimFloat(ListaFloat *lista, float data)
{
    NodeFloat *node = malloc(sizeof(NodeFloat));
    if (node == NULL)
        return;

    node->data = data;
    node->next = NULL;

    if (*lista == NULL)
    {
        *lista = node;
        return;
    }

    NodeFloat *aux = *lista;
    while (aux->next != NULL)
        aux = aux->next;

    aux->next = node;
}

ListaFloat construirLista(float vetor[], int n)
{
    ListaFloat lista;
    iniciarLista(&lista);

    for (int i = 0; i < n; i++)
        inserirFimFloat(&lista, vetor[i]);

    return lista;
}

void imprimirListaFloat(ListaFloat *lista)
{
    NodeFloat *node = *lista;

    while (node != NULL)
    {
        printf("Dado: %.2f\n", node->data);
        node = node->next;
    }
}

int main(void)
{
    float vetor[] = {5.5, 8, 9.1, 25};
    ListaFloat lista = construirLista(vetor, 4);

    printf("Lista criada a partir do vetor:\n");
    imprimirListaFloat(&lista);

    return 0;
}

/*
Aqui eu criei uma lista de float porque o enunciado pede um vetor com valores reais.
Para manter a mesma ordem do vetor, fui inserindo sempre no fim da lista.
*/
