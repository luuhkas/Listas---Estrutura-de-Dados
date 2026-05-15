# Trabalho - Matriz Esparsa

Projeto em C que implementa uma matriz esparsa usando lista cruzada com nos-cabeca.

A matriz armazena apenas os valores diferentes de zero. Cada valor armazenado eh
um no que pertence a duas listas circulares ao mesmo tempo: a lista da linha
(ligada pelo ponteiro `direita`) e a lista da coluna (ligada pelo ponteiro `abaixo`).

A estrutura usada eh a representacao classica de matriz esparsa descrita por
Nivio Ziviani no livro *Projeto de Algoritmos com Implementacoes em Pascal e C*.

## Estrutura

- `src/`: codigo do trabalho em C (matriz_esparsa.h, matriz_esparsa.c, main.c, testes.c).
- `build/`: executaveis gerados localmente.
- `DOCUMENTO.md`: explicacao dos metodos criados e dos desafios.
- `estudo.html`: material visual de estudo com diagrama da estrutura, traces de
  operacoes passo a passo, complexidades e referencias bibliograficas. Abra
  direto no navegador.
- `interface-web/`: interface web auxiliar para visualizar a estrutura interna
  em tempo real, com demo animada. Veja o `README.md` dentro da pasta.

## Como compilar

Use:

```sh
gcc -Wall -Wextra src/main.c src/matriz_esparsa.c -o build/trabalho_matriz_esparsa
```

Depois execute:

```sh
./build/trabalho_matriz_esparsa
```

O programa principal abre um menu no terminal para criar a matriz, inserir valor,
remover valor, consultar posicao, buscar valor, imprimir vizinhos, imprimir a matriz
completa e imprimir a forma esparsa com apenas as coordenadas armazenadas.

## Como testar

Use:

```sh
gcc -Wall -Wextra src/testes.c src/matriz_esparsa.c -o build/testes_matriz_esparsa
./build/testes_matriz_esparsa
```

A suite cobre criacao, insercao, remocao, consulta, busca, contagem, casos de
borda e a estrutura interna completa do exemplo classico do Ziviani (verificando
cada ponteiro um a um).

## Material de estudo

O arquivo `estudo.html` (basta abrir no navegador) reune em uma so pagina:

- motivacao da matriz esparsa e quando vale a pena
- diagrama SVG da estrutura interna (lista cruzada com nos-cabeca)
- codigo real comentado das principais funcoes
- traces de insercao, remocao e consulta passo a passo
- analise de complexidade de todas as operacoes
- comparacao com matriz densa
- perguntas e respostas para apresentacao
- referencias bibliograficas

## Interface web (extra)

A pasta `interface-web/` contem uma pagina HTML que executa o programa em C real
e mostra a estrutura interna sendo construida em tempo real, com:

- demo animada do exemplo do Ziviani com narracao passo a passo do algoritmo
- painel de comparacao de memoria entre matriz densa e esparsa
- saida exata do programa em C no mesmo painel

Para usar, rode `python3 server.py` na pasta `interface-web` e abra
`http://127.0.0.1:8080`.
