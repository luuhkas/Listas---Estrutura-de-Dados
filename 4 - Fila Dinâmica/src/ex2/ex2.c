#include <stdio.h>
#include <stdlib.h>
#include "fila_headers.h"

typedef struct nodeFila
{
    Fila *data;
    struct nodeFila *next;
} NodeFila;

typedef struct filaDeFilas
{
    NodeFila *inicio;
    NodeFila *fim;
} FilaDeFilas;

typedef struct nodePilha
{
    struct pilhaInt *data;
    struct nodePilha *next;
} NodePilha;

typedef struct filaDePilhas
{
    NodePilha *inicio;
    NodePilha *fim;
} FilaDePilhas;

typedef struct pilhaInt
{
    Node *topo;
} PilhaInt;

typedef struct nodePilhaFila
{
    Fila *data;
    struct nodePilhaFila *next;
} NodePilhaFila;

typedef struct pilhaDeFilas
{
    NodePilhaFila *topo;
} PilhaDeFilas;

void enqueueFila(FilaDeFilas *fila, Fila *data)
{
    NodeFila *node = malloc(sizeof(NodeFila));
    if (node == NULL)
        return;

    node->data = data;
    node->next = NULL;

    if (fila->inicio == NULL)
        fila->inicio = node;
    else
        fila->fim->next = node;

    fila->fim = node;
}

PilhaInt *criarPilhaInt()
{
    PilhaInt *pilha = malloc(sizeof(PilhaInt));
    if (pilha == NULL)
        return NULL;

    pilha->topo = NULL;
    return pilha;
}

void pushInt(PilhaInt *pilha, int data)
{
    Node *node = malloc(sizeof(Node));
    if (node == NULL)
        return;

    node->data = data;
    node->next = pilha->topo;
    pilha->topo = node;
}

void enqueuePilha(FilaDePilhas *fila, PilhaInt *data)
{
    NodePilha *node = malloc(sizeof(NodePilha));
    if (node == NULL)
        return;

    node->data = data;
    node->next = NULL;

    if (fila->inicio == NULL)
        fila->inicio = node;
    else
        fila->fim->next = node;

    fila->fim = node;
}

void pushFila(PilhaDeFilas *pilha, Fila *data)
{
    NodePilhaFila *node = malloc(sizeof(NodePilhaFila));
    if (node == NULL)
        return;

    node->data = data;
    node->next = pilha->topo;
    pilha->topo = node;
}

int main(void)
{
    Fila *fila1 = criarFila();
    Fila *fila2 = criarFila();
    PilhaInt *pilha1 = criarPilhaInt();
    PilhaInt *pilha2 = criarPilhaInt();

    enqueue(fila1, 1);
    enqueue(fila1, 2);
    enqueue(fila2, 3);
    enqueue(fila2, 4);

    pushInt(pilha1, 10);
    pushInt(pilha1, 20);
    pushInt(pilha2, 30);
    pushInt(pilha2, 40);

    FilaDeFilas filaDeFilas = {NULL, NULL};
    FilaDePilhas filaDePilhas = {NULL, NULL};
    PilhaDeFilas pilhaDeFilas = {NULL};

    enqueueFila(&filaDeFilas, fila1);
    enqueueFila(&filaDeFilas, fila2);

    enqueuePilha(&filaDePilhas, pilha1);
    enqueuePilha(&filaDePilhas, pilha2);

    pushFila(&pilhaDeFilas, fila1);
    pushFila(&pilhaDeFilas, fila2);

    printf("Fila de filas criada\n");
    printf("Fila de pilhas criada\n");
    printf("Pilha de filas criada\n");

    return 0;
}

/*
Esse exercicio foi mais para montar as combinacoes de estruturas.
Como a fila original guarda int, eu criei nos separados para guardar ponteiros para
fila ou pilha. Assim da para ter fila de filas, fila de pilhas e pilha de filas.
*/
