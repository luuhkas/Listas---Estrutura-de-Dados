# Grafos

Ultima lista da disciplina. Um grafo eh um conjunto de vertices ligados por
arestas; aqui ele eh guardado por lista de adjacencia (no projeto do professor,
em forma de matriz de vizinhos) e, quando ponderado, cada aresta tem um peso.

No projeto do professor (`ProjGrafo`) a estrutura eh:

```c
struct grafo{
    int eh_ponderado;
    int nro_vertices;
    int grau_max;
    int** arestas;   // destinos que saem de cada vertice
    float** pesos;   // peso de cada aresta
    int* grau;       // quantos vizinhos cada vertice tem
};
```

## Sobre esta lista

O enunciado pede para usar o projeto `ProjGrafo` disponibilizado pelo professor,
entao a base nao foi reescrita do zero - so implementei dentro dela (ou ao lado
dela) o que a lista pede.

- `base/Grafo.c` e `.h`: o projeto do professor com as funcoes novas dos
  exercicios 5 (`prim_Grafo`) e 6 (`buscaNo_Grafo`, `arestaMenorPeso_Grafo`).
- `base/GrafoLista.c` e `.h`: a estrutura nova do exercicio 4 (grafo por lista de
  adjacencia encadeada). Fica em arquivo separado porque o tipo tambem se chama
  `Grafo` e conflitaria com a base.
- `src/main.c`: testes dos exercicios 5 e 6 (monta o grafo dos aeroportos do
  exercicio 2 e confere o PRIM).
- `src/main_q4.c`: teste da estrutura nova do exercicio 4.
- `enunciado/`: PDF da lista.
- `RESPOSTAS.md`: respostas dos exercicios 1 e 2 (teoria) e as descricoes pedidas
  nos exercicios 3, 4, 5 e 6.
- `build/`: executaveis gerados localmente.

## Exercicios

1. Construcao de grafos: exemplo direcionado e nao direcionado; e dois grafos
   simples conexos a partir de sequencias de graus (Havel-Hakimi).
2. Analise do grafo dos aeroportos: arestas, vertices, alcance DFW->JFK, caminho
   mais curto MIA->LAX, matriz e lista de adjacencia, e AGM por PRIM (peso 831).
3. Descricao das funcoes `cria_Grafo`, `libera_Grafo`, `insereAresta` e
   `removeAresta` do ProjGrafo, com trechos do codigo.
4. Estrutura nova por lista de adjacencia, com criacao, insercao e remocao.
5. `prim_Grafo`: Arvore Geradora Minima por PRIM.
6. `buscaNo_Grafo` (achar um no) e `arestaMenorPeso_Grafo` (aresta de menor peso).

Os exercicios 1, 2 e as descricoes (3, 4, 5, 6) estao no `RESPOSTAS.md`. O codigo
dos exercicios 4, 5 e 6 esta na base e eh testado nos `main`.

## Como compilar

```sh
# exercicios 5 e 6 (estrutura original do ProjGrafo)
gcc -Wall -Wextra -I '10 - Grafos/base' \
  '10 - Grafos/src/main.c' \
  '10 - Grafos/base/Grafo.c' \
  -o /tmp/lista10
/tmp/lista10

# exercicio 4 (estrutura nova por lista de adjacencia)
gcc -Wall -Wextra -I '10 - Grafos/base' \
  '10 - Grafos/src/main_q4.c' \
  '10 - Grafos/base/GrafoLista.c' \
  -o /tmp/lista10_q4
/tmp/lista10_q4
```
