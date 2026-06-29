#include <stdio.h>
#include <stdlib.h>
#include "GrafoLista.h"

// Teste do exercicio 4 (estrutura nova: grafo por lista de adjacencia).
// Refaco um grafinho simples e mostro que criar, inserir, remover e
// liberar funcionam com a nova estrutura {Lista **vet; int nos;}.

int main(){
    Grafo* gr = cria_Grafo(5); // 5 vertices, listas comecam vazias
    int nd = 0;                // nao direcionado: insere os dois sentidos

    insereAresta(gr, 0, 1, nd, 4);
    insereAresta(gr, 0, 2, nd, 1);
    insereAresta(gr, 2, 1, nd, 2);
    insereAresta(gr, 1, 3, nd, 5);
    insereAresta(gr, 3, 4, nd, 3);

    printf("=== Exercicio 4: grafo por lista de adjacencia ===\n");
    printf("Depois das insercoes:\n");
    imprime_Grafo(gr);

    printf("\nRemovo a aresta 0-1:\n");
    removeAresta(gr, 0, 1, nd);
    imprime_Grafo(gr);

    libera_Grafo(gr);
    printf("\nFim!\n");
    return 0;
}
