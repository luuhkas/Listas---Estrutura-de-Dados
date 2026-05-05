# Listas Encadeadas

Lista encadeada eh uma estrutura formada por nos ligados por ponteiros.

Cada no guarda um valor e aponta para o proximo no:

```c
typedef struct node
{
    int data;
    struct node *next;
} Node;
```

No projeto, a lista foi definida assim:

```c
typedef Node *Lista;
```

Ou seja, `Lista` eh um ponteiro para o primeiro no.

## Como funciona

Uma lista simples fica assim:

```txt
lista -> 1 -> 2 -> 3 -> NULL
```

Diferente da pilha e da fila, a lista nao tem uma regra fixa de entrada e saida. Ela permite inserir, remover, buscar e alterar elementos em varias posicoes.

## Operacoes comuns

- inserir no inicio;
- inserir no fim;
- inserir em uma posicao;
- remover pelo valor;
- remover do inicio ou do fim;
- buscar um valor;
- percorrer a lista;
- comparar listas;
- concatenar listas.

## Diferenca para pilha e fila

- Pilha: entra e sai pelo topo.
- Fila: entra pelo fim e sai pelo inicio.
- Lista: pode manipular nos em diferentes pontos.

## Cuidados

- Para mexer no primeiro no, muitas vezes a funcao recebe `Lista *lista`.
- Antes de acessar um ponteiro, confira se ele nao eh `NULL`.
- Ao remover um no, religue o anterior ao proximo antes de liberar memoria.
- Quando inserir no meio, primeiro ache o no anterior da posicao.

## Neste diretorio

Os exercicios trabalham buscas, remocoes recursivas, insercao por posicao, criacao de lista a partir de vetor, remocao de repetidos, concatenacao, fusao ordenada e troca de nos usando ponteiros.

