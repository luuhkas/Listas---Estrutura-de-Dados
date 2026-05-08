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

    while ((*lista)->prox != NULL)
        *lista = (*lista)->prox;

    (*lista)->prox = node;
    node->ant = *lista;

    while ((*lista)->ant != NULL)
        *lista = (*lista)->ant;
}

int conta_lista_nota(ListaAluno *lista, int n1)
{
    if (lista == NULL || *lista == NULL)
        return 0;

    int contador = 0;

    while ((*lista)->prox != NULL)
    {
        if ((*lista)->data.n1 == n1)
            contador++;

        *lista = (*lista)->prox;
    }

    if ((*lista)->data.n1 == n1)
        contador++;

    while ((*lista)->ant != NULL)
        *lista = (*lista)->ant;

    return contador;
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

    inserirAluno(&lista, 10, "Ana", 9);
    inserirAluno(&lista, 20, "Bruno", 7);
    inserirAluno(&lista, 30, "Carlos", 9);
    inserirAluno(&lista, 40, "Julia", 10);

    printf("Lista:\n");
    imprimirListaAluno(&lista);

    printf("\nQuantidade de alunos com nota 9: %d\n", conta_lista_nota(&lista, 9));

    printf("\nLista depois da funcao:\n");
    imprimirListaAluno(&lista);

    return 0;
}

/*
Nesse exercicio eu fiz como o enunciado pediu e usei so o ponteiro da lista para
percorrer. Fui andando ate o final contando as notas iguais e depois voltei pelo ant
ate deixar a lista apontando para o primeiro aluno de novo.
*/
