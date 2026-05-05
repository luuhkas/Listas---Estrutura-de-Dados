# Pilha Dinamica

Pilha eh uma estrutura onde o ultimo elemento que entra eh o primeiro que sai.

Essa regra eh chamada de LIFO:

```txt
Last In, First Out
Ultimo a entrar, primeiro a sair
```

## Como funciona

Na pilha, tudo acontece pelo topo.

```txt
topo -> 3 -> 2 -> 1 -> NULL
```

Se inserir um novo valor, ele entra antes do topo atual.  
Se remover, sai o valor que esta no topo.

## Operacoes principais

- `push`: empilha um valor no topo.
- `pop`: remove o valor do topo.
- `topo`: le o valor que esta no topo.
- verificar se esta vazia: topo igual a `NULL`.

## Pilha dinamica

Aqui a pilha eh dinamica porque cada elemento eh um no criado com `malloc`.

Cada no guarda:

```c
int data;
struct node *next;
```

O `next` aponta para o elemento que estava antes no topo.

## Cuidados

- Ao remover um no, primeiro o topo precisa andar para o proximo.
- Depois disso, o no antigo pode receber `free`.
- Se `topo == NULL`, a pilha esta vazia.

## Neste diretorio

Os exercicios trabalham funcoes extras de pilha, copia, comparacao, palindromo, inversao de texto e menu usando a estrutura dinamica.

