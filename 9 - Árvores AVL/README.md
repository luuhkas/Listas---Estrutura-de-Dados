# Arvores AVL

Continuacao das arvores binarias de busca, agora com balanceamento. Uma AVL eh
uma BST em que todo no mantem |altura(esq) - altura(dir)| <= 1; sempre que uma
insercao ou remocao quebra essa regra, a arvore se conserta com uma rotacao
(LL, RR, LR ou RL).

No projeto do professor o no guarda tambem a altura:

```c
struct NO{
    int info;
    int altura;
    struct NO *esq;
    struct NO *dir;
};

typedef struct NO* ArvAVL;
```

## Sobre esta lista

O enunciado pede para usar o projeto `ProjArvoreAVL` disponibilizado pelo
professor, entao a base nao foi reescrita do zero - so implementei dentro dela as
funcoes que a lista pede.

> O projeto entregue chamava `RotacaoRR` em varios pontos (`RotacaoLR`,
> `RotacaoRL`, `insere_ArvAVL`, `remove_ArvAVL`) mas NAO trazia a implementacao
> dela - sem isso nem compila. Implementa-la eh o exercicio 4, entao ela esta na
> base.

- `base/`: o projeto do professor com as funcoes novas (`ArvoreAVL.c` e `.h`).
- `src/main.c`: testes dos exercicios 2a, 4, 7 e 8.
- `enunciado/`: PDF da lista.
- `RESPOSTAS.md`: respostas e descricoes pedidas em cada exercicio.
- `build/`: executaveis gerados localmente.

## Exercicios

1. Diz se cada arvore eh AVL e justifica (resultado: NAO, NAO, SIM, NAO).
2. Montagem passo a passo das 4 sequencias (a, b, c, d), indicando rotacoes.
3. Contraexemplo provando que a ordem de insercao importa (Amongus errado).
4. `RotacaoRR`: rotacao simples a esquerda (a que faltava no projeto).
5. Descricao passo a passo do `insere_ArvAVL`.
6. Descricao passo a passo do `remove_ArvAVL`.
7. `ehAVL_ArvAVL`: verifica se uma arvore eh AVL.
8. `transforma_ArvAVL`: dada uma BST qualquer, devolve uma nova AVL.

Os exercicios 1, 5 e 6 (analise/descricao) e os 2 e 3 (montagem a mao) estao no
`RESPOSTAS.md`. Os 4, 7 e 8 (codigo) estao na base e sao testados no `main.c`.
O exercicio 7 ainda serve de conferencia do exercicio 1: a funcao `ehAVL`
classifica as 4 arvores do enunciado e da `0, 0, 1, 0`.

## Como compilar

```sh
gcc -Wall -Wextra -I '9 - Árvores AVL/base' \
  '9 - Árvores AVL/src/main.c' \
  '9 - Árvores AVL/base/ArvoreAVL.c' \
  -o /tmp/lista9

/tmp/lista9
```
