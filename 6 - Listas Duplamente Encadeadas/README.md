# Listas Duplamente Encadeadas

Lista duplamente encadeada eh uma estrutura formada por nos ligados por dois ponteiros.

Cada no guarda um valor e aponta para o proximo no e tambem para o no anterior:

```c
typedef struct node
{
    int data;
    struct node *ant;
    struct node *prox;
} Node;
```

No projeto, a lista foi definida assim:

```c
typedef Node *Lista;
```

Ou seja, `Lista` eh um ponteiro para o primeiro no.

## Como funciona

Uma lista dupla fica assim:

```txt
NULL <- 1 <-> 2 <-> 3 -> NULL
```

A diferenca principal para a lista simples eh que cada no conhece o anterior e o proximo.
Isso facilita percorrer a lista nos dois sentidos e remover nos sem depender sempre do no anterior.

## Operacoes comuns

- inserir no inicio;
- inserir no fim;
- inserir em ordem;
- remover pelo valor;
- remover do inicio ou do fim;
- buscar um valor;
- percorrer do inicio ao fim;
- percorrer do fim ao inicio;
- verificar tamanho e se esta vazia.

## Cuidados

- Ao inserir um no, atualize `ant` e `prox` dos nos vizinhos.
- Ao remover um no, religue o anterior ao proximo e o proximo ao anterior.
- Se remover o primeiro no, o inicio da lista deve mudar.
- Se remover o ultimo no, o novo ultimo deve apontar `prox` para `NULL`.
- Antes de acessar um ponteiro, confira se ele nao eh `NULL`.

## Neste diretorio

Os exercicios estao organizados em `src/ex1` ate `src/ex5`, seguindo o mesmo padrao das listas anteriores.

A base usa `int data`, como na lista encadeada simples. Quando o exercicio precisa
guardar aluno, ele cria uma estrutura propria dentro do arquivo do exercicio.
