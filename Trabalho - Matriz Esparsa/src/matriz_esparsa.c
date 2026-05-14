#include <stdio.h>
#include <stdlib.h>
#include "matriz_esparsa.h"

/*
 * Estrutura usada:
 *   - 1 no principal com linha=-1 e coluna=-1
 *   - N cabecas de coluna (linha=-1, coluna=c) ligadas pela direita a partir do principal
 *   - M cabecas de linha (linha=l, coluna=-1) ligadas pela abaixo a partir do principal
 *   - Cada cabeca de linha forma uma lista circular pela direita com os nos
 *     daquela linha (apenas os que tem valor diferente de zero).
 *   - Cada cabeca de coluna forma uma lista circular pela abaixo com os nos
 *     daquela coluna (apenas os que tem valor diferente de zero).
 *   - Cada no real pertence a duas listas ao mesmo tempo.
 */

Node *criarNode(int linha, int coluna, int valor)
{
    Node *node = malloc(sizeof(Node));

    if (node == NULL)
        return NULL;

    node->linha = linha;
    node->coluna = coluna;
    node->valor = valor;
    node->direita = node;
    node->abaixo = node;

    return node;
}

Node *acharCabecaLinha(MatrizEsparsa *matriz, int linha)
{
    Node *cabeca = matriz->inicio->abaixo;
    int i;

    for (i = 0; i < linha; i++)
        cabeca = cabeca->abaixo;

    return cabeca;
}

Node *acharCabecaColuna(MatrizEsparsa *matriz, int coluna)
{
    Node *cabeca = matriz->inicio->direita;
    int i;

    for (i = 0; i < coluna; i++)
        cabeca = cabeca->direita;

    return cabeca;
}

MatrizEsparsa *criarMatriz(int linhas, int colunas)
{
    MatrizEsparsa *matriz;
    Node *principal;
    Node *anterior;
    Node *cabeca;
    int i;

    if (linhas <= 0 || colunas <= 0)
        return NULL;

    matriz = malloc(sizeof(MatrizEsparsa));
    if (matriz == NULL)
        return NULL;

    principal = criarNode(-1, -1, 0);
    if (principal == NULL)
    {
        free(matriz);
        return NULL;
    }

    matriz->linhas = linhas;
    matriz->colunas = colunas;
    matriz->inicio = principal;

    anterior = principal;
    for (i = 0; i < colunas; i++)
    {
        cabeca = criarNode(-1, i, 0);
        if (cabeca == NULL)
        {
            desalocarMatriz(matriz);
            return NULL;
        }
        anterior->direita = cabeca;
        cabeca->direita = principal;
        anterior = cabeca;
    }

    anterior = principal;
    for (i = 0; i < linhas; i++)
    {
        cabeca = criarNode(i, -1, 0);
        if (cabeca == NULL)
        {
            desalocarMatriz(matriz);
            return NULL;
        }
        anterior->abaixo = cabeca;
        cabeca->abaixo = principal;
        anterior = cabeca;
    }

    return matriz;
}

void desalocarMatriz(MatrizEsparsa *matriz)
{
    Node *cabecaLinha;
    Node *proximaLinha;
    Node *node;
    Node *proxNode;
    Node *cabecaColuna;
    Node *proximaColuna;

    if (matriz == NULL)
        return;

    if (matriz->inicio == NULL)
    {
        free(matriz);
        return;
    }

    cabecaLinha = matriz->inicio->abaixo;
    while (cabecaLinha != matriz->inicio)
    {
        proximaLinha = cabecaLinha->abaixo;

        node = cabecaLinha->direita;
        while (node != cabecaLinha)
        {
            proxNode = node->direita;
            free(node);
            node = proxNode;
        }

        free(cabecaLinha);
        cabecaLinha = proximaLinha;
    }

    cabecaColuna = matriz->inicio->direita;
    while (cabecaColuna != matriz->inicio)
    {
        proximaColuna = cabecaColuna->direita;
        free(cabecaColuna);
        cabecaColuna = proximaColuna;
    }

    free(matriz->inicio);
    free(matriz);
}

int inserirValor(MatrizEsparsa *matriz, int linha, int coluna, int valor)
{
    Node *cabecaLinha;
    Node *cabecaColuna;
    Node *antLinha;
    Node *antColuna;
    Node *nova;

    if (matriz == NULL || linha < 0 || coluna < 0)
        return 0;
    if (linha >= matriz->linhas || coluna >= matriz->colunas)
        return 0;

    if (valor == 0)
    {
        removerValor(matriz, linha, coluna);
        return 1;
    }

    cabecaLinha = acharCabecaLinha(matriz, linha);
    cabecaColuna = acharCabecaColuna(matriz, coluna);

    antLinha = cabecaLinha;
    while (antLinha->direita != cabecaLinha && antLinha->direita->coluna < coluna)
        antLinha = antLinha->direita;

    if (antLinha->direita != cabecaLinha && antLinha->direita->coluna == coluna)
    {
        antLinha->direita->valor = valor;
        return 1;
    }

    antColuna = cabecaColuna;
    while (antColuna->abaixo != cabecaColuna && antColuna->abaixo->linha < linha)
        antColuna = antColuna->abaixo;

    nova = criarNode(linha, coluna, valor);
    if (nova == NULL)
        return 0;

    nova->direita = antLinha->direita;
    antLinha->direita = nova;

    nova->abaixo = antColuna->abaixo;
    antColuna->abaixo = nova;

    return 1;
}

int removerValor(MatrizEsparsa *matriz, int linha, int coluna)
{
    Node *cabecaLinha;
    Node *cabecaColuna;
    Node *antLinha;
    Node *antColuna;
    Node *alvo;

    if (matriz == NULL || linha < 0 || coluna < 0)
        return 0;
    if (linha >= matriz->linhas || coluna >= matriz->colunas)
        return 0;

    cabecaLinha = acharCabecaLinha(matriz, linha);
    cabecaColuna = acharCabecaColuna(matriz, coluna);

    antLinha = cabecaLinha;
    while (antLinha->direita != cabecaLinha && antLinha->direita->coluna < coluna)
        antLinha = antLinha->direita;

    if (antLinha->direita == cabecaLinha || antLinha->direita->coluna != coluna)
        return 0;

    alvo = antLinha->direita;

    antColuna = cabecaColuna;
    while (antColuna->abaixo != alvo)
        antColuna = antColuna->abaixo;

    antLinha->direita = alvo->direita;
    antColuna->abaixo = alvo->abaixo;

    free(alvo);
    return 1;
}

Node *consultarPosicao(MatrizEsparsa *matriz, int linha, int coluna)
{
    Node *cabecaLinha;
    Node *atual;

    if (matriz == NULL || linha < 0 || coluna < 0)
        return NULL;
    if (linha >= matriz->linhas || coluna >= matriz->colunas)
        return NULL;

    cabecaLinha = acharCabecaLinha(matriz, linha);
    atual = cabecaLinha->direita;

    while (atual != cabecaLinha)
    {
        if (atual->coluna == coluna)
            return atual;
        if (atual->coluna > coluna)
            return NULL;
        atual = atual->direita;
    }

    return NULL;
}

int obterValor(MatrizEsparsa *matriz, int linha, int coluna)
{
    Node *node = consultarPosicao(matriz, linha, coluna);

    if (node == NULL)
        return 0;

    return node->valor;
}

Node *buscarValor(MatrizEsparsa *matriz, int valor)
{
    Node *cabecaLinha;
    Node *node;

    if (matriz == NULL)
        return NULL;

    cabecaLinha = matriz->inicio->abaixo;
    while (cabecaLinha != matriz->inicio)
    {
        node = cabecaLinha->direita;
        while (node != cabecaLinha)
        {
            if (node->valor == valor)
                return node;
            node = node->direita;
        }
        cabecaLinha = cabecaLinha->abaixo;
    }

    return NULL;
}

void imprimirMatriz(MatrizEsparsa *matriz)
{
    Node *cabecaLinha;
    Node *node;
    int i;
    int j;

    if (matriz == NULL)
    {
        printf("Matriz nao alocada.\n");
        return;
    }

    printf("\nMatriz esparsa %dx%d\n", matriz->linhas, matriz->colunas);
    printf("      ");
    for (j = 0; j < matriz->colunas; j++)
        printf("%6d", j);
    printf("\n");

    printf("      ");
    for (j = 0; j < matriz->colunas; j++)
        printf("------");
    printf("\n");

    cabecaLinha = matriz->inicio->abaixo;
    for (i = 0; i < matriz->linhas; i++)
    {
        printf("%3d | ", i);
        node = cabecaLinha->direita;

        for (j = 0; j < matriz->colunas; j++)
        {
            if (node != cabecaLinha && node->coluna == j)
            {
                printf("%6d", node->valor);
                node = node->direita;
            }
            else
                printf("%6d", 0);
        }
        printf("\n");
        cabecaLinha = cabecaLinha->abaixo;
    }
}

void imprimirEsparsa(MatrizEsparsa *matriz)
{
    Node *cabecaLinha;
    Node *node;
    int total;
    int ocupados;

    if (matriz == NULL)
    {
        printf("Matriz nao alocada.\n");
        return;
    }

    total = matriz->linhas * matriz->colunas;
    ocupados = contarNaoZeros(matriz);

    printf("\nForma esparsa da matriz\n");
    printf("-----------------------\n");
    printf("Linhas: %d | Colunas: %d | Posicoes totais: %d | Valores nao zero: %d\n",
           matriz->linhas, matriz->colunas, total, ocupados);

    if (ocupados == 0)
    {
        printf("Nenhum valor diferente de zero foi inserido.\n");
        return;
    }

    printf("\nCoordenadas armazenadas:\n");
    printf("Linha Coluna Valor\n");
    printf("----- ------ -----\n");

    cabecaLinha = matriz->inicio->abaixo;
    while (cabecaLinha != matriz->inicio)
    {
        node = cabecaLinha->direita;
        while (node != cabecaLinha)
        {
            printf("%5d %6d %5d\n", node->linha, node->coluna, node->valor);
            node = node->direita;
        }
        cabecaLinha = cabecaLinha->abaixo;
    }
}

void imprimirVizinhos(MatrizEsparsa *matriz, int linha, int coluna)
{
    int valorCentro;

    if (matriz == NULL)
    {
        printf("Matriz nao alocada.\n");
        return;
    }
    if (linha < 0 || coluna < 0 || linha >= matriz->linhas || coluna >= matriz->colunas)
    {
        printf("Posicao (%d,%d) invalida.\n", linha, coluna);
        return;
    }

    valorCentro = obterValor(matriz, linha, coluna);

    printf("\nVizinhos da posicao (%d,%d)\n", linha, coluna);
    printf("Valor central: %d\n", valorCentro);
    printf("--------------------------\n");

    if (linha - 1 >= 0)
        printf("Cima     : (%d,%d) = %d\n", linha - 1, coluna, obterValor(matriz, linha - 1, coluna));
    else
        printf("Cima     : null\n");

    if (linha + 1 < matriz->linhas)
        printf("Baixo    : (%d,%d) = %d\n", linha + 1, coluna, obterValor(matriz, linha + 1, coluna));
    else
        printf("Baixo    : null\n");

    if (coluna - 1 >= 0)
        printf("Esquerda : (%d,%d) = %d\n", linha, coluna - 1, obterValor(matriz, linha, coluna - 1));
    else
        printf("Esquerda : null\n");

    if (coluna + 1 < matriz->colunas)
        printf("Direita  : (%d,%d) = %d\n", linha, coluna + 1, obterValor(matriz, linha, coluna + 1));
    else
        printf("Direita  : null\n");
}

int contarNaoZeros(MatrizEsparsa *matriz)
{
    Node *cabecaLinha;
    Node *node;
    int quantidade = 0;

    if (matriz == NULL)
        return 0;

    cabecaLinha = matriz->inicio->abaixo;
    while (cabecaLinha != matriz->inicio)
    {
        node = cabecaLinha->direita;
        while (node != cabecaLinha)
        {
            quantidade++;
            node = node->direita;
        }
        cabecaLinha = cabecaLinha->abaixo;
    }

    return quantidade;
}
