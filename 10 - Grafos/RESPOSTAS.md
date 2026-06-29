# Lista 10 - Grafos

Os exercicios de codigo (3, 4, 5 e 6) foram feitos sobre o projeto `ProjGrafo`
do professor, como pede o enunciado. As funcoes novas (5 e 6) foram implementadas
em `base/Grafo.c` e a estrutura nova (4) em `base/GrafoLista.c`; os testes ficam
em `src/main.c` e `src/main_q4.c`. Os exercicios 1 e 2 (teoria) estao resolvidos
aqui no `RESPOSTAS.md`.

No ProjGrafo o grafo eh guardado numa lista de adjacencia em forma de matriz de
vizinhos: pra cada vertice ha uma linha `arestas[v]` com os destinos, uma linha
`pesos[v]` com os pesos e um `grau[v]` que diz quantos vizinhos aquele vertice ja
tem.

```c
struct grafo{
    int eh_ponderado;
    int nro_vertices;
    int grau_max;
    int** arestas;   // arestas[v] = vetor com os destinos saindo de v
    float** pesos;   // pesos[v]   = peso de cada uma dessas arestas
    int* grau;       // grau[v]    = quantos vizinhos v tem agora
};
```

---

## 1) Construcao de grafos

### a) Um grafo simples direcionado e um nao direcionado

Simples = sem laco (aresta de um vertice nele mesmo) e sem aresta repetida.

**Direcionado** (as setas tem sentido). Vertices {A, B, C, D}:

```txt
A ---> B
^      |
|      v
D <--- C
```

Arcos: A->B, B->C, C->D, D->A. Cada ligacao so vale no sentido da seta (de A da
pra ir a B, mas de B nao da pra voltar a A direto).

**Nao direcionado** (as arestas valem nos dois sentidos). Vertices {A, B, C, D}:

```txt
A ----- B
| \     |
|   \   |
|     \ |
D ----- C
```

Arestas: A-B, B-C, C-D, D-A e A-C. Aqui A-B eh a mesma coisa que B-A.

### b) Grafos simples conexos a partir da sequencia de graus

Montei cada grafo pelo metodo de Havel-Hakimi (pego o vertice de maior grau e
ligo ele aos proximos de maior grau, abaixando o grau de cada um; repito). No
fim confiro somando os graus: a soma tem que ser par e igual a 2x o numero de
arestas.

**(a) (1, 1, 2, 3, 3, 4, 4, 6)** -> 8 vertices, soma 24, logo 12 arestas.

Chamei os vertices de A a H com estes graus alvo: A=6, B=4, C=4, D=3, E=3, F=2,
G=1, H=1.

Arestas: A-B, A-C, A-D, A-E, A-F, A-G, B-C, B-D, B-E, C-D, C-E, F-H.

```txt
        G
        |
  D --- A --- F --- H
  |\   /|\
  | \ / | \
  |  X  |  E
  | / \ | /
  |/   \|/
  C --- B
```

Conferencia dos graus:

| Vertice | Vizinhos            | Grau | Alvo |
|---------|---------------------|------|------|
| A | B, C, D, E, F, G | 6 | 6 |
| B | A, C, D, E       | 4 | 4 |
| C | A, B, D, E       | 4 | 4 |
| D | A, B, C          | 3 | 3 |
| E | A, B, C          | 3 | 3 |
| F | A, H             | 2 | 2 |
| G | A                | 1 | 1 |
| H | F                | 1 | 1 |

Soma = 24 (12 arestas), bate. Eh simples (sem laco/repeticao) e conexo (todo
mundo chega em todo mundo: H chega via F-A, G via A).

**(b) (3, 3, 3, 3, 3, 5, 5, 5)** -> 8 vertices, soma 30, logo 15 arestas.

Vertices A a H com: A=5, B=5, C=5, D=3, E=3, F=3, G=3, H=3.

Arestas: A-B, A-C, A-D, A-E, A-F, B-C, B-D, B-G, B-H, C-E, C-F, C-G, D-H, E-H, F-G.

Conferencia dos graus:

| Vertice | Vizinhos         | Grau | Alvo |
|---------|------------------|------|------|
| A | B, C, D, E, F | 5 | 5 |
| B | A, C, D, G, H | 5 | 5 |
| C | A, B, E, F, G | 5 | 5 |
| D | A, B, H       | 3 | 3 |
| E | A, C, H       | 3 | 3 |
| F | A, C, G       | 3 | 3 |
| G | B, C, F       | 3 | 3 |
| H | B, D, E       | 3 | 3 |

Soma = 30 (15 arestas), bate. Simples e conexo.

---

## 2) Analise do grafo dado (aeroportos)

Li o grafo do enunciado e anotei as arestas como **direcionadas** (o desenho usa
setas), cada uma com seu peso:

| Origem -> Destino | Peso |
|-------------------|------|
| BOS -> JFK | 35   |
| BOS -> MIA | 247  |
| JFK -> ORD | 335  |
| JFK -> DFW | 1387 |
| JFK -> MIA | 903  |
| ORD -> DFW | 877  |
| ORD -> SFO | 45   |
| SFO -> LAX | 120  |
| MIA -> DFW | 523  |
| MIA -> LAX | 611  |
| DFW -> LAX | 49   |

> Observacao: essa leitura usa os 11 pesos do desenho, cada um uma vez so
> (35, 45, 49, 120, 247, 335, 523, 611, 877, 903, 1387), o que me deu
> confianca de que peguei todas as arestas. Os sentidos das setas foram lidos
> da figura do enunciado.

### a) Quantas arestas? **11** (a tabela acima).

### b) Quantos vertices? **7** (BOS, DFW, JFK, LAX, MIA, ORD, SFO).

### c) Da pra ir de DFW para JFK?

**Nao.** Seguindo as setas a partir de DFW, a unica aresta que sai eh DFW -> LAX,
e de LAX nao sai nenhuma aresta. Entao, partindo de DFW so chego em {DFW, LAX};
JFK nao esta nesse conjunto.

### d) Caminho mais curto de MIA para LAX

De MIA saem duas arestas: MIA -> LAX (611) e MIA -> DFW (523).

- Direto: MIA -> LAX = **611**.
- Por DFW: MIA -> DFW -> LAX = 523 + 49 = **572**.

O caminho **MIA -> DFW -> LAX, com custo 572**, eh mais curto que a aresta direta
de 611. Ou seja, a ligacao direta nao eh a mais barata.

### e) Matriz de adjacencia

Linhas = origem, colunas = destino; o numero eh o peso e o espaco vazio quer
dizer "nao existe essa aresta". Ordem dos vertices: BOS, DFW, JFK, LAX, MIA, ORD, SFO.

| de \ para | BOS | DFW  | JFK | LAX | MIA | ORD | SFO |
|-----------|-----|------|-----|-----|-----|-----|-----|
| **BOS**   |  .  |  .   | 35  |  .  | 247 |  .  |  .  |
| **DFW**   |  .  |  .   |  .  | 49  |  .  |  .  |  .  |
| **JFK**   |  .  | 1387 |  .  |  .  | 903 | 335 |  .  |
| **LAX**   |  .  |  .   |  .  |  .  |  .  |  .  |  .  |
| **MIA**   |  .  | 523  |  .  | 611 |  .  |  .  |  .  |
| **ORD**   |  .  | 877  |  .  |  .  |  .  |  .  | 45  |
| **SFO**   |  .  |  .   |  .  | 120 |  .  |  .  |  .  |

Como o grafo eh direcionado, a matriz NAO eh simetrica (ex.: tem 35 em
BOS->JFK, mas o espelho JFK->BOS esta vazio).

### f) Lista de adjacencia

Cada vertice aponta so para os destinos que existem (com o peso entre parenteses):

```txt
BOS -> JFK(35) -> MIA(247)
DFW -> LAX(49)
JFK -> DFW(1387) -> MIA(903) -> ORD(335)
LAX -> (vazio)
MIA -> DFW(523) -> LAX(611)
ORD -> DFW(877) -> SFO(45)
SFO -> LAX(120)
```

### g) Arvore Geradora Minima por PRIM

A AGM so faz sentido num grafo **nao direcionado e conexo**, entao tratei cada
aresta nos dois sentidos. O PRIM comeca num vertice e, a cada passo, puxa a
aresta de menor peso que liga a arvore atual a um vertice ainda de fora.
Comecando por BOS:

| Passo | Aresta escolhida | Peso | Arvore depois do passo |
|-------|------------------|------|------------------------|
| 1 | (inicio em BOS)  | -   | {BOS} |
| 2 | BOS - JFK        | 35  | {BOS, JFK} |
| 3 | BOS - MIA        | 247 | {BOS, JFK, MIA} |
| 4 | JFK - ORD        | 335 | {BOS, JFK, MIA, ORD} |
| 5 | ORD - SFO        | 45  | {BOS, JFK, MIA, ORD, SFO} |
| 6 | SFO - LAX        | 120 | {BOS, JFK, MIA, ORD, SFO, LAX} |
| 7 | LAX - DFW        | 49  | todos os 7 |

AGM (6 arestas):

```txt
        BOS
       /    \
   35 /      \ 247
     JFK      MIA
      |
  335 |
     ORD
      |
   45 |
     SFO
      |
  120 |
     LAX
      |
   49 |
     DFW
```

Peso total = 35 + 247 + 335 + 45 + 120 + 49 = **831**.

> Conferi esse resultado na maquina: o `prim_Grafo` do exercicio 5, rodando sobre
> esse mesmo grafo (`src/main.c`), imprime as mesmas arestas e da peso total 831.

---

## 3) Funcionamento das funcoes do ProjGrafo

### a) `Grafo* cria_Grafo(int nro_vertices, int grau_max, int eh_ponderado)`

Aloca a struct do grafo e prepara a matriz de adjacencia vazia. Primeiro guarda
os parametros (normalizando `eh_ponderado` pra 0 ou 1) e cria o vetor `grau` com
`calloc`, ja que todo vertice comeca com grau 0.

```c
gr->nro_vertices = nro_vertices;
gr->grau_max = grau_max;
gr->eh_ponderado = (eh_ponderado != 0)?1:0;
gr->grau = (int*) calloc(nro_vertices,sizeof(int));
```

Depois cria a matriz `arestas`: um vetor de `nro_vertices` linhas, e cada linha
com espaco pra `grau_max` destinos.

```c
gr->arestas = (int**) malloc(nro_vertices * sizeof(int*));
for(i=0; i<nro_vertices; i++)
    gr->arestas[i] = (int*) malloc(grau_max * sizeof(int));
```

A matriz `pesos` so eh alocada se o grafo for ponderado (senao seria memoria
gasta a toa). No fim devolve `gr` (ou NULL, se o `malloc` da struct falhar).

### b) `void libera_Grafo(Grafo* gr)`

Faz o caminho inverso do `cria_Grafo`, liberando de dentro pra fora pra nao
perder ponteiro. Primeiro libera cada linha da matriz `arestas` e depois o vetor
de linhas:

```c
for(i=0; i<gr->nro_vertices; i++)
    free(gr->arestas[i]);
free(gr->arestas);
```

Se o grafo for ponderado, faz o mesmo com `pesos`. Por ultimo libera `grau` e a
propria struct `gr`. O `if(gr != NULL)` no comeco evita dar `free` em ponteiro
nulo.

### c) `int insereAresta(Grafo* gr, int orig, int dest, int eh_digrafo, float peso)`

Antes de tudo valida: grafo nao nulo e os indices `orig` e `dest` dentro do
intervalo. Depois grava o destino na proxima posicao livre da linha de `orig`
(que eh exatamente `grau[orig]`), grava o peso se for ponderado, e incrementa o
grau:

```c
gr->arestas[orig][gr->grau[orig]] = dest;
if(gr->eh_ponderado)
    gr->pesos[orig][gr->grau[orig]] = peso;
gr->grau[orig]++;
```

O pulo do gato esta no fim: se o grafo NAO for digrafo (`eh_digrafo == 0`), ele
chama a si mesmo pra inserir a aresta de volta `dest -> orig`, so que ja passando
`eh_digrafo = 1` pra essa segunda chamada nao se repetir de novo:

```c
if(eh_digrafo == 0)
    insereAresta(gr,dest,orig,1,peso);
```

> Observacao: a funcao confia que ainda ha espaco na linha (nao checa contra o
> `grau_max`) e nao impede aresta repetida. Por isso, ao usar, eu chamo o
> `cria_Grafo` com um `grau_max` folgado.

### d) `int removeAresta(Grafo* gr, int orig, int dest, int eh_digrafo)`

Tambem valida grafo e indices. Depois percorre a linha de `orig` procurando o
destino `dest`:

```c
int i = 0;
while(i<gr->grau[orig] && gr->arestas[orig][i] != dest)
    i++;
if(i == gr->grau[orig])//elemento nao encontrado
    return 0;
```

Se achou, faz uma remocao esperta: em vez de empurrar todo mundo pra tras,
diminui o grau e copia o ULTIMO elemento da linha pra cima do que esta saindo
(troca com o ultimo). Isso custa O(1) e nao precisa manter ordem:

```c
gr->grau[orig]--;
gr->arestas[orig][i] = gr->arestas[orig][gr->grau[orig]];
if(gr->eh_ponderado)
    gr->pesos[orig][i] = gr->pesos[orig][gr->grau[orig]];
```

Igual ao insere, se nao for digrafo ele remove tambem a aresta de volta
`dest -> orig` (com `eh_digrafo = 1`).

---

## 4) Nova estrutura (lista de adjacencia encadeada)

O enunciado da o esqueleto `typedef struct{ Lista **vet; int nos; } Grafo` e
pede pra usar o **minimo de variaveis**. A ideia eh trocar a matriz de vizinhos
por uma lista encadeada por vertice: `vet[v]` eh a cabeca da lista de adjacencia
do vertice `v`. Implementei em `base/GrafoLista.c`.

Cada vizinho vira um no de lista com destino, peso e o proximo:

```c
struct lista{
    int dest;
    float peso;
    struct lista *prox;
};

struct grafo{
    Lista **vet;   // uma lista de adjacencia por vertice
    int nos;       // numero de vertices
};
```

**Nao precisei adicionar nenhuma variavel nova na struct do grafo** - ficou so
com `vet` e `nos`, como no esqueleto. O motivo:

- saiu o `grau_max`: a lista cresce sozinha, nao tem tamanho fixo;
- saiu o `grau[]`: o tamanho da lista de cada vertice ja diz o grau;
- saiu o `eh_ponderado`: o peso mora dentro do no da lista. Se o grafo nao for
  ponderado, basta inserir com peso 1.

As funcoes refeitas:

`cria_Grafo(int nos)` aloca o grafo e o vetor de listas, deixando toda lista como
NULL (vazia):

```c
gr->nos = nos;
gr->vet = (Lista**) malloc(nos * sizeof(Lista*));
for(i=0; i<nos; i++)
    gr->vet[i] = NULL;
```

`insereAresta` cria um no novo e coloca na CABECA da lista de `orig` (O(1)); se
nao for digrafo, insere a volta:

```c
Lista *novo = (Lista*) malloc(sizeof(Lista));
novo->dest = dest;
novo->peso = peso;
novo->prox = gr->vet[orig];
gr->vet[orig] = novo;
```

`removeAresta` anda na lista de `orig` guardando o anterior, religa os ponteiros
quando acha o `dest` e da `free` no no:

```c
if(ant == NULL)            // era o primeiro da lista
    gr->vet[orig] = p->prox;
else
    ant->prox = p->prox;
free(p);
```

`libera_Grafo` percorre cada lista liberando no por no, depois libera o `vet` e o
grafo.

Testei em `src/main_q4.c`: monto um grafo, imprimo, removo uma aresta e imprimo
de novo pra mostrar que some dos dois lados.

---

## 5) Algoritmo de PRIM

Implementei `prim_Grafo(Grafo* gr, int inicio)` em `base/Grafo.c`. PRIM cresce a
AGM a partir de um vertice, sempre puxando a aresta mais barata que liga a arvore
atual a alguem de fora. Uso tres vetores:

- `key[v]`: o menor peso ja conhecido pra ligar `v` na arvore;
- `pai[v]`: por qual vertice `v` vai entrar na arvore;
- `naAGM[v]`: 1 se `v` ja entrou.

O laco principal repete `n` vezes: escolhe o vertice de fora com menor `key`,
marca ele como dentro e relaxa os vizinhos.

```c
// 1) escolhe o vertice de fora da arvore com a menor key
int u = -1;
float menor = INFINITO;
for(j=0; j<n; j++)
    if(!naAGM[j] && key[j] < menor){ menor = key[j]; u = j; }
if(u == -1) break;            // grafo desconexo: sobrou vertice inalcancavel
naAGM[u] = 1;

// 2) relaxa os vizinhos: se chego mais barato neles passando por u, atualizo
for(j=0; j<gr->grau[u]; j++){
    int v = gr->arestas[u][j];
    float peso = gr->eh_ponderado ? gr->pesos[u][j] : 1;
    if(!naAGM[v] && peso < key[v]){ key[v] = peso; pai[v] = u; }
}
```

Cada vez que um vertice entra (menos o inicial, que nao tem pai), imprimo a
aresta `pai[u] - u` e somo o peso. No fim mostro o peso total.

No teste (`src/main.c`) rodei sobre o grafo dos aeroportos do exercicio 2 e deu
peso total **831**, batendo com a AGM que montei a mao no exercicio 2g.

---

## 6) Funcoes extras

### a) Encontrar um no especifico

No ProjGrafo o no eh identificado pelo indice (0 ate n-1), ele nao guarda valor
proprio. Entao "encontrar um no" eh confirmar que o indice existe no grafo;
quando existe, ainda imprimo os vizinhos dele pra mostrar que localizei mesmo.

```c
int buscaNo_Grafo(Grafo* gr, int no){
    if(gr == NULL) return 0;
    if(no < 0 || no >= gr->nro_vertices) return 0;   // fora do grafo
    // ... imprime grau e vizinhos ...
    return 1;
}
```

No teste, procurar o no 4 devolve "achei" (e lista os vizinhos); procurar o no
99 devolve "nao existe".

### b) Encontrar a aresta de menor peso

Percorro todas as arestas (vertice `i`, posicao `j`), guardo a de menor peso e
devolvo a origem e o destino pelos ponteiros:

```c
for(i=0; i<gr->nro_vertices; i++)
    for(j=0; j<gr->grau[i]; j++){
        float peso = gr->eh_ponderado ? gr->pesos[i][j] : 1;
        if(peso < menor){ menor = peso; *orig = i; *dest = gr->arestas[i][j]; }
    }
```

No grafo dos aeroportos a menor aresta eh a de peso **35** (BOS - JFK), que foi o
que a funcao retornou.
