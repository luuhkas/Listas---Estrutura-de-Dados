#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct aluno
{
    int matricula;
    char nome[30];
} Aluno;

typedef struct nodeAluno
{
    Aluno data;
    struct nodeAluno *next;
} NodeAluno;

typedef NodeAluno *ListaAluno;

void iniciarLista(ListaAluno *lista)
{
    *lista = NULL;
}

void inserirAluno(ListaAluno *lista, int matricula, char nome[])
{
    NodeAluno *node = malloc(sizeof(NodeAluno));
    if (node == NULL)
        return;

    node->data.matricula = matricula;
    strcpy(node->data.nome, nome);
    node->next = NULL;

    if (*lista == NULL)
    {
        *lista = node;
        return;
    }

    NodeAluno *aux = *lista;
    while (aux->next != NULL)
        aux = aux->next;

    aux->next = node;
}

Aluno *buscarPorMatricula(ListaAluno *lista, int matricula)
{
    NodeAluno *node = *lista;

    while (node != NULL)
    {
        if (node->data.matricula == matricula)
            return &node->data;

        node = node->next;
    }

    return NULL;
}

Aluno *buscarPorPosicao(ListaAluno *lista, int posicao)
{
    NodeAluno *node = *lista;
    int count = 0;

    while (node != NULL)
    {
        if (count == posicao)
            return &node->data;

        count++;
        node = node->next;
    }

    return NULL;
}

void imprimirAluno(Aluno *aluno)
{
    if (aluno == NULL)
        printf("Aluno nao encontrado\n");
    else
        printf("Matricula: %d - Nome: %s\n", aluno->matricula, aluno->nome);
}

int main(void)
{
    ListaAluno lista;
    iniciarLista(&lista);

    inserirAluno(&lista, 10, "Ana");
    inserirAluno(&lista, 20, "Bruno");
    inserirAluno(&lista, 30, "Carlos");

    printf("Busca por matricula:\n");
    imprimirAluno(buscarPorMatricula(&lista, 20));

    printf("\nBusca por posicao:\n");
    imprimirAluno(buscarPorPosicao(&lista, 2));

    return 0;
}

/*
Nesse exercicio eu criei uma lista de alunos porque precisava guardar matricula e nome.
A busca por matricula percorre a lista ate achar a matricula igual, e a busca por
posicao usa um contador para saber em qual no esta.
*/
