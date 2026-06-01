#pragma once

typedef struct node
{
    int linha;
    int coluna;
    int valor;
    struct node *direita;
    struct node *abaixo;
} Node;

typedef struct matrizEsparsa
{
    int linhas;
    int colunas;
    Node *inicio;
} MatrizEsparsa;

MatrizEsparsa *criarMatriz(int linhas, int colunas);
void desalocarMatriz(MatrizEsparsa *matriz);
int inserirValor(MatrizEsparsa *matriz, int linha, int coluna, int valor);
int removerValor(MatrizEsparsa *matriz, int linha, int coluna);
Node *consultarPosicao(MatrizEsparsa *matriz, int linha, int coluna);
int obterValor(MatrizEsparsa *matriz, int linha, int coluna);
Node *buscarValor(MatrizEsparsa *matriz, int valor);
void imprimirMatriz(MatrizEsparsa *matriz);
void imprimirEsparsa(MatrizEsparsa *matriz);
void imprimirVizinhos(MatrizEsparsa *matriz, int linha, int coluna);
int contarNaoZeros(MatrizEsparsa *matriz);

MatrizEsparsa *somarMatrizes(MatrizEsparsa *a, MatrizEsparsa *b);
MatrizEsparsa *multiplicarMatrizes(MatrizEsparsa *a, MatrizEsparsa *b);
