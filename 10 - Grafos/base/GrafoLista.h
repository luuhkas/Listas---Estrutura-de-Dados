//Arquivo GrafoLista.h
// Estrutura nova pedida no exercicio 4: o prototipo base eh
//   typedef struct{ Lista **vet; int nos; } Grafo;
// ou seja, cada vertice tem UMA lista encadeada de adjacencia, em vez da
// matriz arestas[][] + pesos[][] + grau[] do ProjGrafo original.

typedef struct lista Lista; // no da lista de adjacencia (um vizinho)
typedef struct grafo Grafo; // o grafo em si

Grafo* cria_Grafo(int nos);
void libera_Grafo(Grafo* gr);
int insereAresta(Grafo* gr, int orig, int dest, int eh_digrafo, float peso);
int removeAresta(Grafo* gr, int orig, int dest, int eh_digrafo);
void imprime_Grafo(Grafo* gr);
