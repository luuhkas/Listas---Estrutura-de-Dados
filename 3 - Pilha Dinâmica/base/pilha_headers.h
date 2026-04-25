#pragma once

typedef struct node
{
    int data;
    struct node *next;
} Node;

typedef struct pilha
{
    Node *topo;
} Pilha;

Pilha *criarPilha();
void imprimirPilha(Pilha *pilha);
int push(Pilha *pilha, int data);
int pop(Pilha *pilha);
int topo(Pilha *pilha);
int topo(Pilha *pilha);
int pop2(Pilha *pilha);
int push2(Pilha *pilha, int data);