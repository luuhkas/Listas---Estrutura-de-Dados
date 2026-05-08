#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct aluno
{
    int matricula;
    char nome[30];
    int n1;
} Aluno;

typedef struct nodeAluno
{
    Aluno data;
    struct nodeAluno *ant;
    struct nodeAluno *prox;
} NodeAluno;

typedef NodeAluno *ListaAluno;

void iniciarLista(ListaAluno *lista)
{
    *lista = NULL;
}

void inserirAluno(ListaAluno *lista, int matricula, char nome[], int n1)
{
    NodeAluno *node = malloc(sizeof(NodeAluno));
    if (node == NULL)
        return;

    node->data.matricula = matricula;
    strcpy(node->data.nome, nome);
    node->data.n1 = n1;
    node->ant = NULL;
    node->prox = NULL;

    if (*lista == NULL)
    {
        *lista = node;
        return;
    }

    NodeAluno *aux = *lista;
    while (aux->prox != NULL)
        aux = aux->prox;

    aux->prox = node;
    node->ant = aux;
}

int removerPorMatricula(ListaAluno *lista, int matricula)
{
    if (lista == NULL || *lista == NULL)
        return 1;

    NodeAluno *node = *lista;

    while (node != NULL && node->data.matricula != matricula)
        node = node->prox;

    if (node == NULL)
        return 1;

    if (node->ant == NULL)
        *lista = node->prox;
    else
        node->ant->prox = node->prox;

    if (node->prox != NULL)
        node->prox->ant = node->ant;

    free(node);
    return 0;
}

void imprimirListaAluno(ListaAluno *lista)
{
    NodeAluno *node = *lista;

    while (node != NULL)
    {
        printf("Matricula: %d - Nome: %s - Nota: %d\n",
               node->data.matricula, node->data.nome, node->data.n1);
        node = node->prox;
    }
}

int main(void)
{
    ListaAluno lista;
    iniciarLista(&lista);

    inserirAluno(&lista, 10, "Ana", 8);
    inserirAluno(&lista, 20, "Bruno", 7);
    inserirAluno(&lista, 30, "Carlos", 9);

    printf("Lista antes da remocao:\n");
    imprimirListaAluno(&lista);

    removerPorMatricula(&lista, 20);

    printf("\nLista depois da remocao:\n");
    imprimirListaAluno(&lista);

    return 0;
}

/*
Nesse exercicio eu criei uma lista de alunos porque precisava guardar matricula,
nome e nota. Para remover, procurei a matricula e depois ajustei o ant e o prox.
O cuidado foi tratar quando o aluno removido esta no inicio, no meio ou no fim da lista.
*/
