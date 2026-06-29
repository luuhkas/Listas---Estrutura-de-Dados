#include <stdio.h>
#include <stdlib.h>
#include "GrafoLista.h"

// Cada vizinho vira um no de lista com destino e peso.
struct lista{
    int dest;
    float peso;
    struct lista *prox;
};

// A struct do grafo fica com o MINIMO possivel: so o vetor de listas e o
// numero de nos, exatamente o prototipo do enunciado. Nao precisei de
// grau_max (a lista cresce sozinha) nem de grau[] (o tamanho da lista ja
// diz o grau) nem de eh_ponderado (o peso mora no proprio no da lista; se
// o grafo nao for ponderado, basta inserir peso 1).
struct grafo{
    Lista **vet;
    int nos;
};

Grafo* cria_Grafo(int nos){
    Grafo *gr = (Grafo*) malloc(sizeof(struct grafo));
    if(gr != NULL){
        int i;
        gr->nos = nos;
        gr->vet = (Lista**) malloc(nos * sizeof(Lista*));
        for(i=0; i<nos; i++)
            gr->vet[i] = NULL; // toda lista comeca vazia
    }
    return gr;
}

void libera_Grafo(Grafo* gr){
    if(gr != NULL){
        int i;
        for(i=0; i<gr->nos; i++){      // libera a lista de cada vertice
            Lista *p = gr->vet[i];
            while(p != NULL){
                Lista *aux = p;
                p = p->prox;
                free(aux);
            }
        }
        free(gr->vet);
        free(gr);
    }
}

int insereAresta(Grafo* gr, int orig, int dest, int eh_digrafo, float peso){
    if(gr == NULL)
        return 0;
    if(orig < 0 || orig >= gr->nos)
        return 0;
    if(dest < 0 || dest >= gr->nos)
        return 0;

    // insiro o novo vizinho na CABECA da lista de orig (custa O(1))
    Lista *novo = (Lista*) malloc(sizeof(Lista));
    novo->dest = dest;
    novo->peso = peso;
    novo->prox = gr->vet[orig];
    gr->vet[orig] = novo;

    if(eh_digrafo == 0)            // grafo nao direcionado: poe a volta tambem
        insereAresta(gr, dest, orig, 1, peso);
    return 1;
}

int removeAresta(Grafo* gr, int orig, int dest, int eh_digrafo){
    if(gr == NULL)
        return 0;
    if(orig < 0 || orig >= gr->nos)
        return 0;
    if(dest < 0 || dest >= gr->nos)
        return 0;

    Lista *p = gr->vet[orig];
    Lista *ant = NULL;
    while(p != NULL && p->dest != dest){ // procura o vizinho dest
        ant = p;
        p = p->prox;
    }
    if(p == NULL)                  // nao tem essa aresta
        return 0;

    if(ant == NULL)               // era o primeiro da lista
        gr->vet[orig] = p->prox;
    else
        ant->prox = p->prox;
    free(p);

    if(eh_digrafo == 0)
        removeAresta(gr, dest, orig, 1);
    return 1;
}

void imprime_Grafo(Grafo* gr){
    if(gr == NULL)
        return;
    int i;
    for(i=0; i<gr->nos; i++){
        printf("%d: ", i);
        Lista *p = gr->vet[i];
        while(p != NULL){
            printf("%d(%.0f) ", p->dest, p->peso);
            p = p->prox;
        }
        printf("\n");
    }
}
