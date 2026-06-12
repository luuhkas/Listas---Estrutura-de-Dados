
typedef struct NO* ArvAVL;

ArvAVL* cria_ArvAVL();
void libera_ArvAVL(ArvAVL *raiz);
int insere_ArvAVL(ArvAVL *raiz, int data);
int remove_ArvAVL(ArvAVL *raiz, int valor);
int estaVazia_ArvAVL(ArvAVL *raiz);
int altura_ArvAVL(ArvAVL *raiz);
int totalNO_ArvAVL(ArvAVL *raiz);
int consulta_ArvAVL(ArvAVL *raiz, int valor);
void preOrdem_ArvAVL(ArvAVL *raiz);
void emOrdem_ArvAVL(ArvAVL *raiz);
void posOrdem_ArvAVL(ArvAVL *raiz);

/* Rotacoes (exercicio 4 implementa a RotacaoRR, que faltava no projeto) */
void RotacaoLL(ArvAVL *raiz);
void RotacaoRR(ArvAVL *raiz);
void RotacaoLR(ArvAVL *raiz);
void RotacaoRL(ArvAVL *raiz);

/* Exercicio 7: verifica se a arvore eh AVL */
int ehAVL_ArvAVL(ArvAVL *raiz);

/* Exercicio 8: dada uma arvore de busca qualquer, devolve uma nova AVL */
ArvAVL* transforma_ArvAVL(ArvAVL *raiz);

/* Auxiliar de teste: monta "na mao" cada uma das 4 arvores do exercicio 1
   (qual = 1..4), inclusive as desbalanceadas, para conferir com o ehAVL. */
ArvAVL* arvoreExercicio1(int qual);
