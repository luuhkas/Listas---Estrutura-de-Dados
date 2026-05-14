#include <stdio.h>
#include "matriz_esparsa.h"

static int testesExecutados = 0;
static int testesFalharam = 0;

static void verificar(int condicao, const char *descricao)
{
    testesExecutados++;

    if (condicao)
        printf("[OK] %s\n", descricao);
    else
    {
        printf("[FALHOU] %s\n", descricao);
        testesFalharam++;
    }
}

static void testarMatriz4x4(void)
{
    MatrizEsparsa *matriz = criarMatriz(4, 4);
    Node *node;

    printf("\nTeste com matriz 4x4 (exemplo do Ziviani)\n");

    verificar(matriz != NULL, "aloca matriz 4x4");
    verificar(matriz->linhas == 4 && matriz->colunas == 4, "dimensoes corretas");
    verificar(contarNaoZeros(matriz) == 0, "matriz comeca vazia");

    verificar(inserirValor(matriz, 0, 0, 50) == 1, "insere 50 em (0,0)");
    verificar(inserirValor(matriz, 1, 0, 10) == 1, "insere 10 em (1,0)");
    verificar(inserirValor(matriz, 1, 2, 20) == 1, "insere 20 em (1,2)");
    verificar(inserirValor(matriz, 3, 0, -30) == 1, "insere -30 em (3,0)");
    verificar(inserirValor(matriz, 3, 2, -60) == 1, "insere -60 em (3,2)");
    verificar(inserirValor(matriz, 3, 3, 5) == 1, "insere 5 em (3,3)");

    verificar(contarNaoZeros(matriz) == 6, "conta 6 nao zeros");

    verificar(inserirValor(matriz, 4, 0, 1) == 0, "rejeita linha fora do limite");
    verificar(inserirValor(matriz, 0, 4, 1) == 0, "rejeita coluna fora do limite");
    verificar(inserirValor(matriz, -1, 0, 1) == 0, "rejeita coordenada negativa");

    node = consultarPosicao(matriz, 1, 2);
    verificar(node != NULL && node->valor == 20, "consulta (1,2) retorna 20");
    verificar(consultarPosicao(matriz, 2, 2) == NULL, "consulta posicao zero retorna NULL");
    verificar(consultarPosicao(matriz, 9, 9) == NULL, "consulta fora dos limites retorna NULL");
    verificar(obterValor(matriz, 2, 2) == 0, "obterValor em posicao zero retorna 0");
    verificar(obterValor(matriz, 0, 0) == 50, "obterValor em (0,0) retorna 50");

    node = buscarValor(matriz, -60);
    verificar(node != NULL && node->linha == 3 && node->coluna == 2, "busca -60 acha em (3,2)");
    verificar(buscarValor(matriz, 1234) == NULL, "busca valor ausente retorna NULL");

    verificar(inserirValor(matriz, 1, 2, 99) == 1, "atualiza valor em (1,2)");
    verificar(obterValor(matriz, 1, 2) == 99, "valor atualizado para 99");
    verificar(contarNaoZeros(matriz) == 6, "atualizar nao muda contagem de nao zeros");

    verificar(inserirValor(matriz, 1, 2, 0) == 1, "inserir zero remove o node");
    verificar(consultarPosicao(matriz, 1, 2) == NULL, "(1,2) volta a ser zero");
    verificar(contarNaoZeros(matriz) == 5, "contagem cai para 5 apos remover");

    verificar(removerValor(matriz, 0, 0) == 1, "remove (0,0) explicitamente");
    verificar(contarNaoZeros(matriz) == 4, "contagem cai para 4");
    verificar(removerValor(matriz, 0, 0) == 0, "remover posicao vazia retorna 0");

    desalocarMatriz(matriz);
}

static void testarMatriz1x1(void)
{
    MatrizEsparsa *matriz = criarMatriz(1, 1);

    printf("\nTeste com matriz 1x1\n");

    verificar(matriz != NULL, "aloca matriz 1x1");
    verificar(inserirValor(matriz, 0, 0, 42) == 1, "insere unico valor");
    verificar(obterValor(matriz, 0, 0) == 42, "consulta unico valor");
    verificar(contarNaoZeros(matriz) == 1, "contagem 1");
    verificar(removerValor(matriz, 0, 0) == 1, "remove unico valor");
    verificar(contarNaoZeros(matriz) == 0, "contagem zera apos remover");

    desalocarMatriz(matriz);
}

static void testarOrdemDeInsercao(void)
{
    MatrizEsparsa *matriz = criarMatriz(3, 5);
    Node *node;

    printf("\nTeste de ordem das listas\n");

    verificar(matriz != NULL, "aloca matriz 3x5");

    verificar(inserirValor(matriz, 1, 4, 4) == 1, "insere (1,4)");
    verificar(inserirValor(matriz, 1, 0, 1) == 1, "insere (1,0)");
    verificar(inserirValor(matriz, 1, 2, 2) == 1, "insere (1,2)");
    verificar(inserirValor(matriz, 1, 1, 12) == 1, "insere (1,1)");

    node = consultarPosicao(matriz, 1, 0);
    verificar(node != NULL && node->direita != NULL && node->direita->coluna == 1, "(1,0) -> direita = coluna 1");
    verificar(node->direita->direita->coluna == 2, "coluna 1 -> direita = coluna 2");
    verificar(node->direita->direita->direita->coluna == 4, "coluna 2 -> direita = coluna 4");

    desalocarMatriz(matriz);
}

static void testarDimensoesInvalidas(void)
{
    printf("\nTeste com dimensoes invalidas\n");

    verificar(criarMatriz(0, 3) == NULL, "nao aloca com zero linhas");
    verificar(criarMatriz(3, 0) == NULL, "nao aloca com zero colunas");
    verificar(criarMatriz(-2, 3) == NULL, "nao aloca com linhas negativas");
}

static void testarInserirZeroEmPosicaoVazia(void)
{
    MatrizEsparsa *matriz = criarMatriz(3, 3);

    printf("\nTeste de inserir zero em posicao ja vazia\n");

    verificar(matriz != NULL, "aloca matriz 3x3");
    verificar(contarNaoZeros(matriz) == 0, "matriz comeca vazia");
    verificar(inserirValor(matriz, 1, 1, 0) == 1, "inserir 0 em posicao vazia retorna 1");
    verificar(contarNaoZeros(matriz) == 0, "contagem segue zero");
    verificar(consultarPosicao(matriz, 1, 1) == NULL, "(1,1) continua sem no");
    verificar(inserirValor(matriz, 1, 1, 0) == 1, "inserir 0 de novo continua retornando 1");

    verificar(inserirValor(matriz, 1, 1, 7) == 1, "agora insere valor 7");
    verificar(obterValor(matriz, 1, 1) == 7, "valor 7 esta la");
    verificar(inserirValor(matriz, 1, 1, 0) == 1, "inserir 0 sobre valor existente retorna 1");
    verificar(consultarPosicao(matriz, 1, 1) == NULL, "(1,1) volta a ser zero");
    verificar(contarNaoZeros(matriz) == 0, "contagem volta a zero");

    desalocarMatriz(matriz);
}

static void testarOrdemNaColuna(void)
{
    MatrizEsparsa *matriz = criarMatriz(5, 3);
    Node *node;

    printf("\nTeste de ordem das listas de coluna\n");

    verificar(matriz != NULL, "aloca matriz 5x3");

    verificar(inserirValor(matriz, 4, 1, 40) == 1, "insere (4,1)");
    verificar(inserirValor(matriz, 0, 1, 10) == 1, "insere (0,1)");
    verificar(inserirValor(matriz, 2, 1, 20) == 1, "insere (2,1)");
    verificar(inserirValor(matriz, 1, 1, 15) == 1, "insere (1,1)");

    node = consultarPosicao(matriz, 0, 1);
    verificar(node != NULL && node->abaixo != NULL && node->abaixo->linha == 1, "(0,1) -> abaixo = linha 1");
    verificar(node->abaixo->abaixo->linha == 2, "linha 1 -> abaixo = linha 2");
    verificar(node->abaixo->abaixo->abaixo->linha == 4, "linha 2 -> abaixo = linha 4");

    desalocarMatriz(matriz);
}

static void testarInserirAposRemover(void)
{
    MatrizEsparsa *matriz = criarMatriz(3, 3);

    printf("\nTeste de reinsercao apos remocao\n");

    verificar(matriz != NULL, "aloca matriz 3x3");

    verificar(inserirValor(matriz, 1, 1, 100) == 1, "insere 100");
    verificar(removerValor(matriz, 1, 1) == 1, "remove (1,1)");
    verificar(contarNaoZeros(matriz) == 0, "contagem zero apos remover");
    verificar(inserirValor(matriz, 1, 1, 200) == 1, "reinsere 200 no mesmo lugar");
    verificar(obterValor(matriz, 1, 1) == 200, "novo valor 200 esta la");
    verificar(contarNaoZeros(matriz) == 1, "contagem volta a 1");

    desalocarMatriz(matriz);
}

static void testarRemoverDoMeio(void)
{
    MatrizEsparsa *matriz = criarMatriz(3, 5);
    Node *node;

    printf("\nTeste de remocao do meio da lista\n");

    verificar(matriz != NULL, "aloca matriz 3x5");

    verificar(inserirValor(matriz, 1, 0, 1) == 1, "insere (1,0)");
    verificar(inserirValor(matriz, 1, 1, 2) == 1, "insere (1,1)");
    verificar(inserirValor(matriz, 1, 2, 3) == 1, "insere (1,2)");
    verificar(inserirValor(matriz, 1, 3, 4) == 1, "insere (1,3)");
    verificar(contarNaoZeros(matriz) == 4, "contagem 4");

    verificar(removerValor(matriz, 1, 2) == 1, "remove (1,2) do meio");
    verificar(consultarPosicao(matriz, 1, 2) == NULL, "(1,2) sumiu");
    verificar(contarNaoZeros(matriz) == 3, "contagem 3");

    node = consultarPosicao(matriz, 1, 1);
    verificar(node != NULL && node->direita->coluna == 3, "religacao: (1,1) -> direita = coluna 3");

    node = consultarPosicao(matriz, 1, 3);
    verificar(node != NULL && node->valor == 4, "(1,3) ainda existe com valor 4");

    desalocarMatriz(matriz);
}

static void testarVizinhosNasBordas(void)
{
    MatrizEsparsa *matriz = criarMatriz(3, 3);
    Node *centro;

    printf("\nTeste de vizinhos nas bordas\n");

    verificar(matriz != NULL, "aloca matriz 3x3");

    verificar(inserirValor(matriz, 0, 0, 1) == 1, "insere canto sup esq");
    verificar(inserirValor(matriz, 0, 2, 3) == 1, "insere canto sup dir");
    verificar(inserirValor(matriz, 2, 0, 7) == 1, "insere canto inf esq");
    verificar(inserirValor(matriz, 2, 2, 9) == 1, "insere canto inf dir");
    verificar(inserirValor(matriz, 1, 1, 5) == 1, "insere centro");

    centro = consultarPosicao(matriz, 1, 1);
    verificar(centro != NULL && centro->valor == 5, "centro tem valor 5");

    verificar(obterValor(matriz, 0, 1) == 0, "cima do centro vale 0");
    verificar(obterValor(matriz, 2, 1) == 0, "baixo do centro vale 0");
    verificar(obterValor(matriz, 1, 0) == 0, "esquerda do centro vale 0");
    verificar(obterValor(matriz, 1, 2) == 0, "direita do centro vale 0");

    verificar(obterValor(matriz, 0, 0) == 1, "canto sup esq tem valor");
    verificar(obterValor(matriz, 2, 2) == 9, "canto inf dir tem valor");

    desalocarMatriz(matriz);
}

static void testarMatrizGrande(void)
{
    MatrizEsparsa *matriz = criarMatriz(50, 50);
    int i;

    printf("\nTeste de matriz grande (50x50)\n");

    verificar(matriz != NULL, "aloca matriz 50x50");

    for (i = 0; i < 50; i++)
        verificar(inserirValor(matriz, i, i, i + 1) == 1, "insere diagonal");

    verificar(contarNaoZeros(matriz) == 50, "diagonal completa: 50 nao zeros");
    verificar(obterValor(matriz, 25, 25) == 26, "diagonal: (25,25) = 26");
    verificar(obterValor(matriz, 0, 0) == 1, "diagonal: (0,0) = 1");
    verificar(obterValor(matriz, 49, 49) == 50, "diagonal: (49,49) = 50");
    verificar(obterValor(matriz, 10, 20) == 0, "fora da diagonal vale 0");

    for (i = 0; i < 50; i += 2)
        verificar(removerValor(matriz, i, i) == 1, "remove pares da diagonal");

    verificar(contarNaoZeros(matriz) == 25, "sobraram 25 valores");
    verificar(obterValor(matriz, 0, 0) == 0, "(0,0) removido");
    verificar(obterValor(matriz, 1, 1) == 2, "(1,1) ainda existe");

    desalocarMatriz(matriz);
}

int main(void)
{
    testarMatriz4x4();
    testarMatriz1x1();
    testarOrdemDeInsercao();
    testarDimensoesInvalidas();
    testarInserirZeroEmPosicaoVazia();
    testarOrdemNaColuna();
    testarInserirAposRemover();
    testarRemoverDoMeio();
    testarVizinhosNasBordas();
    testarMatrizGrande();

    printf("\nTestes executados: %d\n", testesExecutados);
    printf("Testes com falha: %d\n", testesFalharam);

    return testesFalharam == 0 ? 0 : 1;
}
