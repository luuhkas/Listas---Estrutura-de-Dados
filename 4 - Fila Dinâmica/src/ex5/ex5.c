#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct aviao
{
    int numero;
    char nome[30];
} Aviao;

typedef struct nodeAviao
{
    Aviao data;
    struct nodeAviao *next;
} NodeAviao;

typedef struct filaAviao
{
    NodeAviao *inicio;
    NodeAviao *fim;
} FilaAviao;

void iniciarFila(FilaAviao *fila)
{
    fila->inicio = NULL;
    fila->fim = NULL;
}

void adicionarAviao(FilaAviao *fila, int numero, char nome[])
{
    NodeAviao *node = malloc(sizeof(NodeAviao));
    if (node == NULL)
        return;

    node->data.numero = numero;
    strcpy(node->data.nome, nome);
    node->next = NULL;

    if (fila->inicio == NULL)
        fila->inicio = node;
    else
        fila->fim->next = node;

    fila->fim = node;
}

int contarAvioes(FilaAviao *fila)
{
    int count = 0;
    NodeAviao *node = fila->inicio;

    while (node != NULL)
    {
        count++;
        node = node->next;
    }

    return count;
}

void autorizarDecolagem(FilaAviao *fila)
{
    if (fila->inicio == NULL)
    {
        printf("Nao ha avioes aguardando\n");
        return;
    }

    NodeAviao *node = fila->inicio;
    printf("Decolagem autorizada para o aviao %s\n", node->data.nome);

    fila->inicio = node->next;
    if (fila->inicio == NULL)
        fila->fim = NULL;

    free(node);
}

void listarAvioes(FilaAviao *fila)
{
    NodeAviao *node = fila->inicio;

    while (node != NULL)
    {
        printf("Numero: %d - Nome: %s\n", node->data.numero, node->data.nome);
        node = node->next;
    }
}

void listarPrimeiro(FilaAviao *fila)
{
    if (fila->inicio == NULL)
    {
        printf("Fila vazia\n");
        return;
    }

    printf("Primeiro aviao: %d - %s\n", fila->inicio->data.numero, fila->inicio->data.nome);
}

int main(void)
{
    FilaAviao fila;
    iniciarFila(&fila);

    adicionarAviao(&fila, 101, "Azul");
    adicionarAviao(&fila, 202, "Gol");
    adicionarAviao(&fila, 303, "Latam");

    printf("Quantidade de avioes aguardando: %d\n", contarAvioes(&fila));

    printf("\nAvioes na fila:\n");
    listarAvioes(&fila);

    printf("\nCaracteristicas do primeiro:\n");
    listarPrimeiro(&fila);

    printf("\nAutorizando decolagem:\n");
    autorizarDecolagem(&fila);

    printf("\nFila depois da decolagem:\n");
    listarAvioes(&fila);

    return 0;
}

/*
Nesse exercicio eu criei uma fila propria para avioes, porque cada aviao precisa ter
mais de uma informacao. A fila funciona igual a fila normal: entra no fim e sai pelo
inicio.
As funcoes fazem as tarefas pedidas no enunciado, como contar, listar, autorizar a
decolagem e mostrar o primeiro aviao da fila.
*/
