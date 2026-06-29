//Arquivo Grafo.h

typedef struct grafo Grafo;

Grafo* cria_Grafo(int nro_vertices, int grau_max, int eh_ponderado);
void libera_Grafo(Grafo* gr);
int insereAresta(Grafo* gr, int orig, int dest, int eh_digrafo, float peso);
int removeAresta(Grafo* gr, int orig, int dest, int eh_digrafo);
void imprime_Grafo(Grafo *gr);

// ---- funcoes que eu acrescentei nesta lista ----
void prim_Grafo(Grafo* gr, int inicio);                          // exercicio 5 (AGM por PRIM)
int  buscaNo_Grafo(Grafo* gr, int no);                           // exercicio 6a (achar um no)
float arestaMenorPeso_Grafo(Grafo* gr, int* orig, int* dest);    // exercicio 6b (aresta de menor peso)
