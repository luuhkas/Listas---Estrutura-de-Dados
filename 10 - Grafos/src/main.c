#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h"

// Testes dos exercicios 5 e 6, feitos sobre a estrutura original do
// ProjGrafo (base/Grafo.c). Pra deixar verificavel, monto AQUI o mesmo
// grafo dos aeroportos do exercicio 2 e confiro se o PRIM bate com a AGM
// que calculei a mao (peso total 831).

int main(){
    // indices: 0=BOS 1=DFW 2=JFK 3=LAX 4=MIA 5=ORD 6=SFO
    // grafo NAO direcionado e ponderado (eh_digrafo=0, eh_ponderado=1)
    Grafo* gr = cria_Grafo(7, 10, 1);
    int nd = 0; // nao digrafo: insere os dois sentidos

    insereAresta(gr, 0, 2, nd, 35);    // BOS-JFK
    insereAresta(gr, 0, 4, nd, 247);   // BOS-MIA
    insereAresta(gr, 2, 5, nd, 335);   // JFK-ORD
    insereAresta(gr, 2, 1, nd, 1387);  // JFK-DFW
    insereAresta(gr, 2, 4, nd, 903);   // JFK-MIA
    insereAresta(gr, 5, 1, nd, 877);   // ORD-DFW
    insereAresta(gr, 5, 6, nd, 45);    // ORD-SFO
    insereAresta(gr, 6, 3, nd, 120);   // SFO-LAX
    insereAresta(gr, 4, 1, nd, 523);   // MIA-DFW
    insereAresta(gr, 4, 3, nd, 611);   // MIA-LAX
    insereAresta(gr, 1, 3, nd, 49);    // DFW-LAX

    printf("=== Grafo dos aeroportos (lista de adjacencia) ===\n");
    printf("(0=BOS 1=DFW 2=JFK 3=LAX 4=MIA 5=ORD 6=SFO)\n");
    imprime_Grafo(gr);

    // ---- Exercicio 5: PRIM a partir de BOS (indice 0) ----
    printf("\n=== Exercicio 5: AGM por PRIM (comecando em BOS) ===\n");
    prim_Grafo(gr, 0);
    printf("(esperado: peso total 831)\n");

    // ---- Exercicio 6a: encontrar um no especifico ----
    printf("\n=== Exercicio 6a: encontrar um no ===\n");
    printf("Procurando o no 4 (MIA): %s\n", buscaNo_Grafo(gr, 4) ? "achei" : "nao existe");
    printf("Procurando o no 99: %s\n", buscaNo_Grafo(gr, 99) ? "achei" : "nao existe");

    // ---- Exercicio 6b: aresta de menor peso ----
    printf("\n=== Exercicio 6b: aresta de menor peso ===\n");
    int o, d;
    float m = arestaMenorPeso_Grafo(gr, &o, &d);
    printf("Menor aresta: %d - %d (peso %.0f)\n", o, d, m);
    printf("(esperado: aresta de peso 35, entre BOS(0) e JFK(2))\n");

    libera_Grafo(gr);
    printf("\nFim!\n");
    return 0;
}
