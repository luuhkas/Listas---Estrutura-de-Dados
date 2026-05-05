# Listas - Estrutura de Dados

Exercicios em C desenvolvidos para praticar recursividade, ponteiros e estruturas de dados dinamicas.

## Estrutura

- `1 - Recursividade/`
- `2 - Ponteiros/`
- `3 - Pilha Dinâmica/`
- `4 - Fila Dinâmica/`
- `5 - Listas/`

Nas listas com estrutura dinamica, o padrao usado eh:

- `base/`: funcoes e headers da estrutura.
- `src/exN/`: resolucao de cada exercicio.
- `enunciado/`: PDF da lista.
- `build/`: executaveis gerados localmente.

## Estruturas

- Pilha: usa `topo`; quem entra por ultimo sai primeiro.
- Fila: usa `inicio` e `fim`; quem entra primeiro sai primeiro.
- Lista: usa `Lista` como ponteiro para o primeiro no, seguindo a ideia da base do professor, mas com `Node`, `data` e `next`.

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
