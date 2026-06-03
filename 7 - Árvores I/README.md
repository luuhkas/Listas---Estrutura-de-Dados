# Arvores I

Arvore binaria de busca: cada no guarda um valor e tem dois ponteiros, um para o
filho da esquerda e outro para o da direita. Os valores menores ficam a esquerda
e os maiores a direita, o que facilita inserir, buscar e remover.

No projeto do professor o no eh definido assim:

```c
struct NO{
    int info;
    struct NO *esq;
    struct NO *dir;
};

typedef struct NO* ArvBin;
```

E a arvore eh manipulada por um ponteiro `ArvBin*` (ponteiro para a raiz).

## Sobre esta lista

O enunciado pede para usar o projeto `ProjArvoreBinaria` disponibilizado pelo
professor, entao aqui nao foi reescrito do zero como nas listas anteriores. As
funcoes que faltavam foram implementadas dentro do proprio projeto.

- `base/`: o projeto do professor com as funcoes completas
  (`ArvoreBinaria.c` e `ArvoreBinaria.h`).
- `src/main.c`: testes de todos os exercicios.
- `enunciado/`: PDF da lista.
- `RESPOSTAS.md`: respostas e descricoes pedidas em cada exercicio.
- `build/`: executaveis gerados localmente.

## Varreduras

- PRE ordem: raiz, esquerda, direita.
- EM ordem: esquerda, raiz, direita (em arvore de busca sai em ordem crescente).
- POS ordem: esquerda, direita, raiz.

## Como compilar

```sh
gcc -Wall -Wextra -I '7 - Árvores I/base' \
  '7 - Árvores I/src/main.c' \
  '7 - Árvores I/base/ArvoreBinaria.c' \
  -o /tmp/lista7

/tmp/lista7
```
