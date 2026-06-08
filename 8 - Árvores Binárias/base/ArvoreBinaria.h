
typedef struct NO* ArvBin;

ArvBin* cria_ArvBin();
void libera_ArvBin(ArvBin *raiz);
int insere_ArvBin(ArvBin* raiz, int valor);
int remove_ArvBin(ArvBin *raiz, int valor);
struct NO* remove_atual(struct NO* atual);
int estaVazia_ArvBin(ArvBin *raiz);
int altura_ArvBin(ArvBin *raiz);
int totalNO_ArvBin(ArvBin *raiz);
int consulta_ArvBin(ArvBin *raiz, int valor);
void preOrdem_ArvBin(ArvBin *raiz);
void emOrdem_ArvBin(ArvBin *raiz);
void posOrdem_ArvBin(ArvBin *raiz);

// Lista 8 - Arvores Binarias
int contaFolhas_ArvBin(ArvBin *raiz);
void imprimeRelacoes_ArvBin(ArvBin *raiz);
int contaValor_ArvBin(ArvBin *raiz, int valor);
void imprimeFolhasDecrescente_ArvBin(ArvBin *raiz);
int saoIguais_ArvBin(ArvBin *a, ArvBin *b);
void eliminaPares_ArvBin(ArvBin *raiz);
int saoSimilares_ArvBin(ArvBin *a, ArvBin *b);
void preOrdemChar_ArvBin(ArvBin *raiz);
void emOrdemChar_ArvBin(ArvBin *raiz);
void posOrdemChar_ArvBin(ArvBin *raiz);
ArvBin* criaExpressao_ArvBin(char *prefixa);
int calculaExpressao_ArvBin(ArvBin *raiz);
void infixa_ArvBin(ArvBin *raiz);
