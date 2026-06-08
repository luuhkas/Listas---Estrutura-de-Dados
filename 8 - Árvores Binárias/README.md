# Arvores Binarias

Continuacao da lista anterior, ainda sobre arvore binaria de busca: cada no guarda
um valor e tem dois ponteiros, um para o filho da esquerda e outro para o da
direita. Os valores menores ficam a esquerda e os maiores a direita.

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
professor, entao aqui tambem nao foi reescrito do zero. Reaproveitei a base que ja
tinha completado na Lista 7 e implementei dentro dela as funcoes novas que esta
lista pede.

- `base/`: o projeto do professor com as funcoes completas, incluindo as desta
  lista (`ArvoreBinaria.c` e `ArvoreBinaria.h`).
- `src/main.c`: testes de todos os exercicios.
- `enunciado/`: PDF da lista.
- `RESPOSTAS.md`: respostas e descricoes pedidas em cada exercicio.
- `build/`: executaveis gerados localmente.

## Exercicios

1. `contaFolhas_ArvBin`: conta os nos folha (sem filhos).
2. `imprimeRelacoes_ArvBin`: imprime cada no como raiz, pai ou folha.
3. `contaValor_ArvBin`: conta quantas vezes um valor aparece.
4. `imprimeFolhasDecrescente_ArvBin`: imprime so as folhas em ordem decrescente.
5. `saoIguais_ArvBin`: verifica se duas arvores sao iguais (forma e valores).
6. `eliminaPares_ArvBin`: remove todos os valores pares.
7. `saoSimilares_ArvBin`: verifica se duas arvores tem a mesma forma.
8. Insercao e impressao das letras `M, F, S, D, J, P, U, A, E, H, Q, T, W, K`.
9. Arvore de expressao matematica: monta pela ordem prefixa, calcula o resultado
   e imprime nas notacoes infixa, prefixa e posfixa.

## Notacoes da expressao (exercicio 9)

- Infixa: esquerda, raiz, direita (com parenteses).
- Prefixa: raiz, esquerda, direita.
- Posfixa: esquerda, direita, raiz.

## Como compilar

```sh
gcc -Wall -Wextra -I '8 - Árvores Binárias/base' \
  '8 - Árvores Binárias/src/main.c' \
  '8 - Árvores Binárias/base/ArvoreBinaria.c' \
  -o /tmp/lista8

/tmp/lista8
```
