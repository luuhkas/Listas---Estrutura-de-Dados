#pragma once

typedef struct node
{
    int data;
    struct node *next;
} Node;

typedef struct fila
{
    Node *inicio;
    Node *fim;
} Fila;

Fila *criarFila();
void imprimirFila(Fila *fila);
int enqueue(Fila *fila, int data);
int dequeue(Fila *fila);
int frente(Fila *fila);
