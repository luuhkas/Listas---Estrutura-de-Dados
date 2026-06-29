#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h" //inclui os prototipos

#define INFINITO 1000000000.0f //usado como "sem ligacao" no PRIM

//Definicao do tipo Grafo (lista de adjacencia em forma de matriz de vizinhos)
struct grafo{
    int eh_ponderado;
    int nro_vertices;
    int grau_max;
    int** arestas;
    float** pesos;
    int* grau;
};

Grafo* cria_Grafo(int nro_vertices, int grau_max, int eh_ponderado){
    Grafo *gr;
    gr = (Grafo*) malloc(sizeof(struct grafo));
    if(gr != NULL){
        int i;
        gr->nro_vertices = nro_vertices;
        gr->grau_max = grau_max;
        gr->eh_ponderado = (eh_ponderado != 0)?1:0;
        gr->grau = (int*) calloc(nro_vertices,sizeof(int));

        gr->arestas = (int**) malloc(nro_vertices * sizeof(int*));
        for(i=0; i<nro_vertices; i++)
            gr->arestas[i] = (int*) malloc(grau_max * sizeof(int));

        if(gr->eh_ponderado){
            gr->pesos = (float**) malloc(nro_vertices * sizeof(float*));
            for(i=0; i<nro_vertices; i++)
                gr->pesos[i] = (float*) malloc(grau_max * sizeof(float));
        }

    }
    return gr;
}

void libera_Grafo(Grafo* gr){
    if(gr != NULL){
        int i;
        for(i=0; i<gr->nro_vertices; i++)
            free(gr->arestas[i]);
        free(gr->arestas);

        if(gr->eh_ponderado){
            for(i=0; i<gr->nro_vertices; i++)
                free(gr->pesos[i]);
            free(gr->pesos);
        }
        free(gr->grau);
        free(gr);
    }
}

int insereAresta(Grafo* gr, int orig, int dest, int eh_digrafo, float peso){
    if(gr == NULL)
        return 0;
    if(orig < 0 || orig >= gr->nro_vertices)
        return 0;
    if(dest < 0 || dest >= gr->nro_vertices)
        return 0;

    gr->arestas[orig][gr->grau[orig]] = dest;
    if(gr->eh_ponderado)
        gr->pesos[orig][gr->grau[orig]] = peso;
    gr->grau[orig]++;

    if(eh_digrafo == 0)
        insereAresta(gr,dest,orig,1,peso);
    return 1;
}

int removeAresta(Grafo* gr, int orig, int dest, int eh_digrafo){
    if(gr == NULL)
        return 0;
    if(orig < 0 || orig >= gr->nro_vertices)
        return 0;
    if(dest < 0 || dest >= gr->nro_vertices)
        return 0;

    int i = 0;
    while(i<gr->grau[orig] && gr->arestas[orig][i] != dest)
        i++;
    if(i == gr->grau[orig])//elemento nao encontrado
        return 0;
    gr->grau[orig]--;
    gr->arestas[orig][i] = gr->arestas[orig][gr->grau[orig]];
    if(gr->eh_ponderado)
        gr->pesos[orig][i] = gr->pesos[orig][gr->grau[orig]];
    if(eh_digrafo == 0)
        removeAresta(gr,dest,orig,1);
    return 1;
}

void imprime_Grafo(Grafo *gr){
    if(gr == NULL)
        return;

    int i, j;
    for(i=0; i < gr->nro_vertices; i++){
        printf("%d: ", i);
        for(j=0; j < gr->grau[i]; j++){
            if(gr->eh_ponderado)
                printf("%d(%.2f), ", gr->arestas[i][j], gr->pesos[i][j]);
            else
                printf("%d, ", gr->arestas[i][j]);
        }
        printf("\n");
    }
}

// =====================================================================
// Exercicio 5 - Algoritmo de PRIM (Arvore Geradora Minima).
// PRIM cresce a arvore a partir de UM vertice: a cada passo pega a
// aresta de menor peso que liga um vertice ja dentro da arvore a um
// que ainda esta fora. Uso a versao O(V^2) com tres vetores:
//   key[v] = menor peso conhecido para ligar v na arvore
//   pai[v] = de quem v vai pendurar na arvore
//   naAGM[v] = 1 se v ja entrou na arvore
// O grafo precisa ser tratado como NAO direcionado e conexo (foi assim
// que inseri as arestas no main, com eh_digrafo = 0).
// =====================================================================
void prim_Grafo(Grafo* gr, int inicio){
    if(gr == NULL)
        return;
    int n = gr->nro_vertices;
    int i, j;

    float *key   = (float*) malloc(n * sizeof(float));
    int   *pai   = (int*)   malloc(n * sizeof(int));
    int   *naAGM = (int*)   calloc(n, sizeof(int));

    for(i=0; i<n; i++){
        key[i] = INFINITO;   // ninguem alcancado ainda
        pai[i] = -1;
    }
    key[inicio] = 0;         // comeco pelo vertice "inicio"

    float total = 0;
    for(i=0; i<n; i++){
        // 1) escolhe o vertice de fora da arvore com a menor key
        int u = -1;
        float menor = INFINITO;
        for(j=0; j<n; j++)
            if(!naAGM[j] && key[j] < menor){
                menor = key[j];
                u = j;
            }
        if(u == -1)          // sobrou vertice inalcancavel: grafo desconexo
            break;

        naAGM[u] = 1;
        if(pai[u] != -1){    // o vertice inicial nao tem aresta de entrada
            printf("  %d - %d (peso %.0f)\n", pai[u], u, menor);
            total += menor;
        }

        // 2) relaxa os vizinhos de u: se chego mais barato neles por u, atualizo
        for(j=0; j<gr->grau[u]; j++){
            int v = gr->arestas[u][j];
            float peso = gr->eh_ponderado ? gr->pesos[u][j] : 1;
            if(!naAGM[v] && peso < key[v]){
                key[v] = peso;
                pai[v] = u;
            }
        }
    }

    printf("  Peso total da AGM: %.0f\n", total);
    free(key);
    free(pai);
    free(naAGM);
}

// =====================================================================
// Exercicio 6a - encontrar um no especifico no grafo.
// No ProjGrafo o "no" eh identificado pelo seu indice (0 .. n-1), ele
// nao guarda um valor proprio. Entao "encontrar um no" eh confirmar que
// ele pertence ao grafo (indice valido). Quando acho, ainda imprimo as
// arestas que saem dele, pra mostrar que realmente localizei o no.
// Retorna 1 se o no existe, 0 caso contrario.
// =====================================================================
int buscaNo_Grafo(Grafo* gr, int no){
    if(gr == NULL)
        return 0;
    if(no < 0 || no >= gr->nro_vertices)
        return 0;

    printf("  No %d encontrado. Grau de saida = %d. Vizinhos: ", no, gr->grau[no]);
    int j;
    for(j=0; j<gr->grau[no]; j++)
        printf("%d ", gr->arestas[no][j]);
    printf("\n");
    return 1;
}

// =====================================================================
// Exercicio 6b - encontrar a aresta de menor peso do grafo.
// Percorro todas as arestas (vertice i, posicao j) e guardo a de menor
// peso. Devolvo o peso pela funcao e a origem/destino pelos ponteiros.
// Se o grafo nao tiver arestas, devolvo -1.
// =====================================================================
float arestaMenorPeso_Grafo(Grafo* gr, int* orig, int* dest){
    if(gr == NULL)
        return -1;

    float menor = INFINITO;
    int i, j, achou = 0;
    for(i=0; i<gr->nro_vertices; i++){
        for(j=0; j<gr->grau[i]; j++){
            float peso = gr->eh_ponderado ? gr->pesos[i][j] : 1;
            if(peso < menor){
                menor = peso;
                *orig = i;
                *dest = gr->arestas[i][j];
                achou = 1;
            }
        }
    }
    if(!achou)
        return -1;
    return menor;
}
