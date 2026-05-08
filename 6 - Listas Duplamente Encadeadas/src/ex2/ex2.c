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

Aluno criarAluno(int matricula, char nome[], int n1)
{
    Aluno aluno;
    aluno.matricula = matricula;
    strcpy(aluno.nome, nome);
    aluno.n1 = n1;
    return aluno;
}

int inserirOrdenadoAluno(ListaAluno *lista, Aluno aluno)
{
    if (lista == NULL)
        return 1;

    NodeAluno *node = malloc(sizeof(NodeAluno));
    if (node == NULL)
        return 1;

    node->data = aluno;
    node->ant = NULL;
    node->prox = NULL;

    if (*lista == NULL || (*lista)->data.matricula >= aluno.matricula)
    {
        node->prox = *lista;

        if (*lista != NULL)
            (*lista)->ant = node;

        *lista = node;
        return 0;
    }

    NodeAluno *atual = *lista;
    while (atual->prox != NULL && atual->prox->data.matricula < aluno.matricula)
        atual = atual->prox;

    node->ant = atual;
    node->prox = atual->prox;

    if (atual->prox != NULL)
        atual->prox->ant = node;

    atual->prox = node;
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

    inserirOrdenadoAluno(&lista, criarAluno(30, "Carlos", 9));
    inserirOrdenadoAluno(&lista, criarAluno(10, "Ana", 8));
    inserirOrdenadoAluno(&lista, criarAluno(20, "Bruno", 7));
    inserirOrdenadoAluno(&lista, criarAluno(5, "Julia", 10));

    printf("Lista ordenada por matricula:\n");
    imprimirListaAluno(&lista);

    return 0;
}

/*
Aqui eu adaptei a insercao ordenada da base para uma lista de alunos.
A comparacao ficou pela matricula, e como a lista eh dupla eu tambem precisei
arrumar o ponteiro ant do no que fica depois do novo.
*/
