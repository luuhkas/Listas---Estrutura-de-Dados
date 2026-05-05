#pragma once

typedef struct node
{
    int data;
    struct node *next;
} Node;

typedef Node *Lista;

Lista *criarLista();
void liberarLista(Lista *lista);
int inserirFim(Lista *lista, int data);
int inserirInicio(Lista *lista, int data);
int inserirOrdenado(Lista *lista, int data);
void imprimirLista(Lista *lista);
int removerValor(Lista *lista, int data);
int removerInicio(Lista *lista);
int removerFim(Lista *lista);
int tamanhoLista(Lista *lista);
int listaVazia(Lista *lista);
int listaCheia(Lista *lista);