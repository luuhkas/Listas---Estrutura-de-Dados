# Lista 9 - Arvores AVL

Todos os exercicios foram feitos sobre o projeto `ProjArvoreAVL` do professor,
como pede o enunciado. As funcoes novas (exercicios 4, 7 e 8) foram implementadas
em `base/ArvoreAVL.c` e os testes ficam em `src/main.c`.

Uma arvore AVL eh uma arvore binaria de busca em que, para TODO no, a diferenca
de altura entre a subarvore esquerda e a direita (o fator de balanceamento, fb)
eh no maximo 1. Quando uma insercao/remocao deixa algum no com fb 2, a arvore se
conserta sozinha com uma rotacao (LL, RR, LR ou RL).

> Observacao importante sobre o projeto: a funcao `RotacaoRR` ja era CHAMADA pelo
> projeto (dentro de `RotacaoLR`, `RotacaoRL`, `insere_ArvAVL` e `remove_ArvAVL`),
> mas NAO estava implementada no `.c` entregue - sem ela o projeto nem compila.
> Implementa-la eh justamente o exercicio 4, entao a coloquei na base.

---

## 1) Cada arvore eh AVL? Justifique

Conferi cada no calculando o fb = |altura(esq) - altura(dir)| (folha tem altura
0, ponteiro nulo conta como -1). Tambem confirmei esse resultado pela maquina,
com a funcao do exercicio 7 (ver `arvoreExercicio1` no `.c` e a saida do
programa: da 0, 0, 1, 0).

**Arvore 1 - NAO eh AVL.**
```txt
        57
       /  \
     22    60
    /        \
   10         88
  /  \
 0   15
```
O no **22** tem subarvore esquerda de altura 1 (o 10 com os filhos 0 e 15) e
subarvore direita vazia (altura -1). fb = |1 - (-1)| = **2**. Basta um no com
fb 2 para nao ser AVL.

**Arvore 2 - NAO eh AVL.**
```txt
         57
       /    \
     22      60
    /       /  \
   10      58   88
  /  \      \
 0   15     59
```
O lado direito agora esta cheio, mas o no **22** continua com so o filho
esquerdo (10) de altura 1 contra direita vazia: fb = |1 - (-1)| = **2**.

**Arvore 3 - eh AVL.**
```txt
   57
```
Um unico no, sem filhos: fb = 0. Toda arvore com 0 ou 1 no eh trivialmente AVL.

**Arvore 4 - NAO eh AVL.**
```txt
           8
        /     \
       4       12
      / \        \
     2   6       14
    /\   /\      / \
   1 3  5  7   13   15
```
O lado esquerdo (raiz 4) eh perfeito e balanceado, mas o no **12** tem subarvore
esquerda vazia (altura -1) e direita de altura 1 (o 14 com 13 e 15):
fb = |-1 - 1| = **2**.

---

## 2) Montagem passo a passo

Convencao das rotacoes (igual ao codigo do projeto, decidida no no que ficou com
fb 2): **LL** = uma rotacao simples a direita; **RR** = simples a esquerda;
**LR** = RR no filho esquerdo + LL na raiz; **RL** = LL no filho direito + RR na
raiz. A cada passo abaixo eu marco onde houve rotacao. O log real das rotacoes
sai no terminal ao rodar `src/main.c` (exercicio 2a) e bateu com o que esta aqui.

### a) 50, 30, 20, 70, 40, 35, 37, 38, 10, 32, 45, 42, 25, 47, 36

| Insere | O que acontece |
|--------|----------------|
| 50 | raiz |
| 30 | vai a esquerda |
| 20 | 50 fica com fb 2 (esq-esq) -> **LL no 50**, sobe o 30 |
| 70 | a direita, ok |
| 40 | ok |
| 35 | 30 fica com fb 2 (dir-esq) -> **RL no 30** (LL no 50, RR no 30) |
| 37 | ok |
| 38 | 35 fica com fb 2 (dir-dir) -> **RR no 35** |
| 10 | ok |
| 32 | 40 (a raiz) fica com fb 2 (esq-dir) -> **LR no 40**, sobe o 37 |
| 45 | ok |
| 42 | 40 fica com fb 2 (dir-esq) -> **RL no 40** |
| 25 | ok |
| 47 | ok |
| 36 | ok |

Arvore final (completa e perfeitamente balanceada, altura 3, todo no com fb 0):
```txt
                 37
            /          \
          30            45
         /  \          /   \
       20    35      40     50
      / \   /  \    /  \   /  \
    10  25 32  36  38  42 47   70
```

### b) 100, 80, 60, 40, 20, 70, 30, 50, 35, 45, 55, 75, 65, 73, 77

| Insere | O que acontece |
|--------|----------------|
| 100 | raiz |
| 80 | a esquerda |
| 60 | 100 com fb 2 (esq-esq) -> **LL no 100**, sobe o 80 |
| 40 | ok |
| 20 | 60 com fb 2 (esq-esq) -> **LL no 60**, sobe o 40 |
| 70 | 80 (raiz) com fb 2 (esq-dir) -> **LR no 80**, sobe o 60 |
| 30 | 40 com fb 2 (esq-dir) -> **LR no 40**, sobe o 30 |
| 50 | ok |
| 35 | ok |
| 45 | 30 com fb 2 (dir-dir) -> **RR no 30**, sobe o 40 |
| 55 | ok |
| 75 | ok |
| 65 | ok |
| 73 | 80 com fb 2 (esq-dir) -> **LR no 80**, sobe o 75 |
| 77 | ok |

Arvore final (completa, altura 3, todo no com fb 0):
```txt
                60
           /          \
         40            75
        /  \          /   \
      30    50       70     80
     / \   / \      /  \   /  \
   20  35 45 55   65   73 77   100
```

### c) 41, 38, 31, 12, 19, 8, 27, 49

| Insere | O que acontece |
|--------|----------------|
| 41 | raiz |
| 38 | a esquerda |
| 31 | 41 com fb 2 (esq-esq) -> **LL no 41**, sobe o 38 |
| 12 | ok |
| 19 | 31 com fb 2 (esq-dir) -> **LR no 31**, sobe o 19 |
| 8  | 38 (raiz) com fb 2 (esq-esq) -> **LL no 38**, sobe o 19 |
| 27 | ok |
| 49 | ok |

Arvore final (altura 3):
```txt
          19
        /     \
      12       38
     /        /   \
    8       31     41
           /         \
         27           49
```

### d) 10, 21, 15, 17, 16, 19, 20

| Insere | O que acontece |
|--------|----------------|
| 10 | raiz |
| 21 | a direita |
| 15 | 10 com fb 2 (dir-esq) -> **RL no 10**, sobe o 15 |
| 17 | ok |
| 16 | 21 com fb 2 (esq-esq) -> **LL no 21**, sobe o 17 |
| 19 | 15 (raiz) com fb 2 (dir-dir) -> **RR no 15**, sobe o 17 |
| 20 | 21 com fb 2 (esq-dir) -> **LR no 21**, sobe o 20 |

Arvore final (completa, altura 2):
```txt
         17
       /     \
     15       20
    /  \     /  \
  10    16  19    21
```

---

## 3) O professor Amongus esta errado

Ele diz que a ordem de insercao nao importa, que o conjunto fixo sempre gera a
mesma AVL. Contraexemplo com o conjunto **{1, 2, 3, 4}**:

Inserindo na ordem **1, 2, 3, 4** (ao inserir o 3 ha uma RR que sobe o 2):
```txt
    2
   / \
  1   3
       \
        4
```

Inserindo o MESMO conjunto na ordem **4, 3, 2, 1** (ao inserir o 2 ha uma LL que
sobe o 3):
```txt
      3
     / \
    2   4
   /
  1
```

As duas sao AVL validas, com os mesmos elementos, mas tem raizes diferentes
(2 contra 3) e formatos diferentes. Logo, a ordem de insercao **importa** - o
professor esta errado.

---

## 4) RotacaoRR (rotacao simples a esquerda)

Eh o espelho da `RotacaoLL` que ja vinha no projeto. O no desbalanceado esta
pesado a direita: o filho da direita (`B`) sobe e vira a raiz da subarvore, o no
antigo desce para a esquerda de `B`, e o filho esquerdo de `B` (que estava "no
meio") passa a ser o filho direito do no antigo. So os ponteiros e as alturas
mudam; a ordem da busca continua valendo.

```c
void RotacaoRR(ArvAVL *raiz){//RR
    printf("RotacaoRR\n");
    struct NO *B;
    B = (*raiz)->dir;            // B = filho direito, que vai subir
    (*raiz)->dir = B->esq;       // o "neto" da esquerda de B vira filho direito do no antigo
    B->esq = *raiz;              // o no antigo desce para a esquerda de B
    (*raiz)->altura = maior(altura_NO((*raiz)->esq),altura_NO((*raiz)->dir)) + 1;
    B->altura = maior(altura_NO(B->dir),(*raiz)->altura) + 1;
    *raiz = B;                   // B vira a nova raiz da subarvore
}
```

Teste (exercicio 4 no `main.c`): inserindo 10, 20, 30 em ordem crescente, ao
chegar o 30 a arvore fica `10 -> 20 -> 30` pesada a direita e dispara a RR, que
deixa o 20 na raiz com 10 e 30 como filhos.

---

## 5) Como funciona o `insere_ArvAVL`

A funcao eh recursiva e desce pela arvore como numa BST comum; a diferenca eh que,
ao VOLTAR da recursao, ela checa o balanceamento e gira se preciso.

1. **Caso base / criacao do no.** Se chegou num ponto vazio, cria o no novo com
   altura 0 e devolve 1 (inseriu).
   ```c
   if(*raiz == NULL){
       struct NO *novo = (struct NO*)malloc(sizeof(struct NO));
       novo->info = valor; novo->altura = 0;
       novo->esq = NULL; novo->dir = NULL;
       *raiz = novo;
       return 1;
   }
   ```
2. **Desce para o lado certo.** Se `valor < info` vai para a esquerda, se for
   maior vai para a direita; se for igual, recusa (sem duplicados).
3. **Rebalanceia na volta.** Depois que a chamada recursiva devolve 1, calcula o
   fator de balanceamento com `fatorBalanceamento_NO`. Se deu 2, escolhe a
   rotacao olhando POR ONDE a insercao entrou. No lado esquerdo:
   ```c
   if((res = insere_ArvAVL(&(atual->esq), valor)) == 1){
       if(fatorBalanceamento_NO(atual) >= 2){
           if(valor < (*raiz)->esq->info) RotacaoLL(raiz); // esq-esq
           else                            RotacaoLR(raiz); // esq-dir
       }
   }
   ```
   No lado direito eh simetrico, usando `RotacaoRR` (dir-dir) ou `RotacaoRL`
   (dir-esq).
4. **Atualiza a altura** do no antes de retornar:
   ```c
   atual->altura = maior(altura_NO(atual->esq),altura_NO(atual->dir)) + 1;
   ```

Funcoes auxiliares usadas: `fatorBalanceamento_NO` (mede o desnivel),
`altura_NO` e `maior` (recalculam a altura), e as quatro rotacoes.

---

## 6) Como funciona o `remove_ArvAVL`

Tambem eh recursiva e tem duas partes: achar/remover o no (como numa BST) e
rebalancear na volta - so que, na remocao, o lado que "encolhe" eh o oposto, entao
a rotacao usada eh a do OUTRO lado.

1. **Procura.** Se `valor` eh menor desce a esquerda, se maior desce a direita.
   Se nao existe, avisa e devolve 0.
2. **Remocao quando acha o no** (`(*raiz)->info == valor`):
   - **0 ou 1 filho:** o no eh substituido pelo filho que existe (ou por NULL) e
     liberado.
     ```c
     struct NO *oldNode = (*raiz);
     if((*raiz)->esq != NULL) *raiz = (*raiz)->esq;
     else                     *raiz = (*raiz)->dir;
     free(oldNode);
     ```
   - **2 filhos:** acha o menor da subarvore direita com `procuraMenor` (o
     sucessor em ordem), copia o valor dele para o no atual e remove esse menor
     la embaixo (que cai num caso de 0/1 filho).
     ```c
     struct NO* temp = procuraMenor((*raiz)->dir);
     (*raiz)->info = temp->info;
     remove_ArvAVL(&(*raiz)->dir, (*raiz)->info);
     ```
3. **Rebalanceia na volta.** Como a remocao encurta um lado, o no pode ficar com
   fb 2 pesado para o lado oposto. Aqui a escolha LL/LR ou RR/RL eh feita
   comparando ALTURAS das subarvores do filho (e nao o valor inserido). Exemplo
   do ramo em que removi pela esquerda e o lado direito ficou mais alto:
   ```c
   if(fatorBalanceamento_NO(*raiz) >= 2){
       if(altura_NO((*raiz)->dir->esq) <= altura_NO((*raiz)->dir->dir))
           RotacaoRR(raiz);
       else
           RotacaoRL(raiz);
   }
   ```
4. **Atualiza a altura** de cada no na volta, igual ao insere.

Auxiliares: `procuraMenor` (sucessor), `fatorBalanceamento_NO`, `altura_NO`,
`maior` e as rotacoes.

---

## 7) Funcao que verifica se uma arvore eh AVL

Para cada no checo se |altura(esq) - altura(dir)| <= 1 e se os dois lados tambem
sao AVL. Calculo a altura REAL na hora com `alturaReal_NO`, sem confiar no campo
`->altura` (uma arvore montada na mao pode nao te-lo preenchido).

```c
int alturaReal_NO(struct NO* no){
    if(no == NULL) return -1;
    return maior(alturaReal_NO(no->esq), alturaReal_NO(no->dir)) + 1;
}

int ehAVL_NO(struct NO* no){
    if(no == NULL) return 1;                 // vazia eh AVL
    int he = alturaReal_NO(no->esq);
    int hd = alturaReal_NO(no->dir);
    if(labs(he - hd) >= 2) return 0;         // achou no desbalanceado
    return ehAVL_NO(no->esq) && ehAVL_NO(no->dir);
}

int ehAVL_ArvAVL(ArvAVL *raiz){
    if(raiz == NULL) return 1;
    return ehAVL_NO(*raiz);
}
```

No teste, classifiquei as 4 arvores do exercicio 1 e deu **0, 0, 1, 0**,
batendo com a analise feita a mao.

---

## 8) `transforma` - BST qualquer vira AVL

Estrategia em dois passos:

1. **Percorro em ordem** (esq, raiz, dir), o que joga os valores num vetor JA
   ordenado.
2. **Reinsiro sempre o elemento do meio primeiro** (e recursivamente o meio de
   cada metade). Colocando o meio como raiz, a arvore ja nasce balanceada, e como
   uso o proprio `insere_ArvAVL` ela continua AVL de qualquer jeito.

```c
void coletaEmOrdem(struct NO* no, int *vet, int *n){
    if(no == NULL) return;
    coletaEmOrdem(no->esq, vet, n);
    vet[(*n)++] = no->info;
    coletaEmOrdem(no->dir, vet, n);
}

void insereMeio(ArvAVL *nova, int *vet, int ini, int fim){
    if(ini > fim) return;
    int meio = (ini + fim) / 2;
    insere_ArvAVL(nova, vet[meio]);
    insereMeio(nova, vet, ini, meio - 1);
    insereMeio(nova, vet, meio + 1, fim);
}

ArvAVL* transforma_ArvAVL(ArvAVL *raiz){
    ArvAVL* nova = cria_ArvAVL();
    if(raiz == NULL || *raiz == NULL) return nova;
    int total = totalNO_ArvAVL(raiz);
    int *vet = (int*) malloc(total * sizeof(int));
    int n = 0;
    coletaEmOrdem(*raiz, vet, &n);    // vet ordenado
    insereMeio(nova, vet, 0, n - 1);
    free(vet);
    return nova;
}
```

> O enunciado escreve `Arv* transforma(Arv *raiz)`. No projeto o tipo se chama
> `ArvAVL`, entao a funcao ficou `ArvAVL* transforma_ArvAVL(ArvAVL *raiz)` - a
> ideia eh exatamente a mesma. Devolvo uma arvore NOVA e nao mexo na original.

No teste passei `{1,2,3,4,5,6,7}` (que numa busca comum viraria uma escada de
altura 6) e a saida voltou balanceada (altura 2) e com `ehAVL = 1`.
