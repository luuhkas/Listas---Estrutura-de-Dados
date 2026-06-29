# Listas - Estrutura de Dados

Exercicios e trabalhos em C desenvolvidos para praticar recursividade, ponteiros
e estruturas de dados dinamicas.

## Estrutura

- `1 - Recursividade/`: exercicios de funcoes recursivas.
- `2 - Ponteiros/`: exercicios de ponteiros, vetores, matrizes e alocacao.
- `3 - Pilha Dinâmica/`: implementacao base de pilha dinamica e exercicios.
- `4 - Fila Dinâmica/`: implementacao base de fila dinamica e exercicios.
- `5 - Listas/`: implementacao base de lista simplesmente encadeada e exercicios.
- `6 - Listas Duplamente Encadeadas/`: implementacao base de lista dupla e exercicios.
- `7 - Árvores I/`: arvore binaria de busca usando o projeto do professor.
- `8 - Árvores Binárias/`: mais exercicios de arvore binaria (folhas, similares, expressao matematica).
- `9 - Árvores AVL/`: arvore AVL com rotacoes, verificacao de balanceamento e transformacao de BST em AVL.
- `10 - Grafos/`: grafos com o projeto do professor (PRIM/AGM, busca de no e nova estrutura por lista de adjacencia).
- `Trabalho - Matriz Esparsa/`: trabalho em C com matriz esparsa usando lista cruzada.
- `Trabalho 2 - Árvores/`: trabalho em C com arvore generica de diretorios (representacao filho-irmao + indice Trie).

Nas listas com estrutura dinamica, o padrao geral usado eh:

- `base/`: funcoes e headers da estrutura.
- `src/exN/`: resolucao de cada exercicio.
- `enunciado/`: PDF da lista.
- `build/`: executaveis gerados localmente.

## Estruturas

- Pilha: usa `topo`; quem entra por ultimo sai primeiro.
- Fila: usa `inicio` e `fim`; quem entra primeiro sai primeiro.
- Lista: usa `Lista` como ponteiro para o primeiro no, seguindo a ideia da base do professor, mas com `Node`, `data` e `next`.
- Lista dupla: usa nos com ponteiros para o anterior e para o proximo.
- Arvore AVL: arvore binaria de busca que mantem o balanceamento com rotacoes LL, RR, LR e RL.
- Grafo: vertices ligados por arestas; guardado por lista de adjacencia (matriz de vizinhos no projeto do professor) e, quando ponderado, com peso por aresta.
- Matriz esparsa: armazena apenas valores diferentes de zero em listas cruzadas por linha e coluna.

## Como compilar

Exemplo para pilha:

```sh
gcc -Wall -Wextra -I '3 - Pilha Dinâmica/base' \
  '3 - Pilha Dinâmica/src/ex1/ex1.c' \
  '3 - Pilha Dinâmica/base/pilha_functions.c' \
  -o /tmp/ex1
```

Exemplo para fila:

```sh
gcc -Wall -Wextra -I '4 - Fila Dinâmica/base' \
  '4 - Fila Dinâmica/src/ex1/ex1.c' \
  '4 - Fila Dinâmica/base/fila_functions.c' \
  -o /tmp/ex1
```

Exemplo para lista:

```sh
gcc -Wall -Wextra -I '5 - Listas/base' \
  '5 - Listas/src/ex1/ex1.c' \
  '5 - Listas/base/lista_functions.c' \
  -o /tmp/ex1
```

Exemplo para lista duplamente encadeada:

```sh
gcc -Wall -Wextra -I '6 - Listas Duplamente Encadeadas/base' \
  '6 - Listas Duplamente Encadeadas/src/ex1/ex1.c' \
  '6 - Listas Duplamente Encadeadas/base/lista_dupla_functions.c' \
  -o /tmp/ex1
```

Exemplo para a arvore binaria (Lista 7):

```sh
gcc -Wall -Wextra -I '7 - Árvores I/base' \
  '7 - Árvores I/src/main.c' \
  '7 - Árvores I/base/ArvoreBinaria.c' \
  -o /tmp/lista7
```

Exemplo para a arvore AVL (Lista 9):

```sh
gcc -Wall -Wextra -I '9 - Árvores AVL/base' \
  '9 - Árvores AVL/src/main.c' \
  '9 - Árvores AVL/base/ArvoreAVL.c' \
  -o /tmp/lista9

/tmp/lista9
```

Exemplo para grafos (Lista 10) - exercicios 5 e 6:

```sh
gcc -Wall -Wextra -I '10 - Grafos/base' \
  '10 - Grafos/src/main.c' \
  '10 - Grafos/base/Grafo.c' \
  -o /tmp/lista10

/tmp/lista10
```

E o exercicio 4 da Lista 10 (estrutura nova por lista de adjacencia):

```sh
gcc -Wall -Wextra -I '10 - Grafos/base' \
  '10 - Grafos/src/main_q4.c' \
  '10 - Grafos/base/GrafoLista.c' \
  -o /tmp/lista10_q4

/tmp/lista10_q4
```

Exemplo para o trabalho de matriz esparsa:

```sh
gcc -Wall -Wextra \
  'Trabalho - Matriz Esparsa/src/main.c' \
  'Trabalho - Matriz Esparsa/src/matriz_esparsa.c' \
  -o /tmp/trabalho_matriz_esparsa
```

Para executar os testes da matriz esparsa:

```sh
gcc -Wall -Wextra \
  'Trabalho - Matriz Esparsa/src/testes.c' \
  'Trabalho - Matriz Esparsa/src/matriz_esparsa.c' \
  -o /tmp/testes_matriz_esparsa

/tmp/testes_matriz_esparsa
```

Exemplo para o trabalho 2 (arvore de diretorios):

```sh
gcc -Wall -Wextra -std=c11 \
  'Trabalho 2 - Árvores/src/arvore.c' \
  'Trabalho 2 - Árvores/src/main.c' \
  -o /tmp/trabalho_arvores

/tmp/trabalho_arvores
```
