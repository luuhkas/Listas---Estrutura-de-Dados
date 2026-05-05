# Fila Dinamica

Fila eh uma estrutura onde o primeiro elemento que entra eh o primeiro que sai.

Essa regra eh chamada de FIFO:

```txt
First In, First Out
Primeiro a entrar, primeiro a sair
```

## Como funciona

A fila possui dois pontos importantes:

- `inicio`: onde os elementos saem;
- `fim`: onde os elementos entram.

```txt
inicio -> 1 -> 2 -> 3 <- fim
```

Se remover, sai o `1`.  
Se inserir, o novo valor entra depois do `3`.

## Operacoes principais

- `enqueue`: enfileira no fim.
- `dequeue`: remove do inicio.
- `frente`: le o valor no inicio.
- verificar se esta vazia: inicio igual a `NULL`.

## Fila dinamica

Cada elemento da fila eh um no alocado com `malloc`.

Cada no guarda:

```c
int data;
struct node *next;
```

O ponteiro `fim` deixa a insercao mais direta, porque nao precisa percorrer a fila toda para inserir no final.

## Cuidados

- Quando remove o ultimo elemento, `inicio` e `fim` devem virar `NULL`.
- A fila entra pelo fim e sai pelo inicio.
- Se misturar as regras, ela deixa de ser fila.

## Neste diretorio

Os exercicios trabalham separacao de fila, combinacoes com pilha e fila, inversao, fila circular, simulacao de avioes, fusao ordenada, reverso e menu.

