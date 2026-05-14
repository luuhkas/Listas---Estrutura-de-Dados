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
- `Trabalho - Matriz Esparsa/`: trabalho em C com matriz esparsa usando lista cruzada.

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
