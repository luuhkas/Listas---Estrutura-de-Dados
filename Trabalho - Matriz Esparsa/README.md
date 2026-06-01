# Trabalho - Matriz Esparsa

Projeto em C que implementa uma matriz esparsa usando lista cruzada com nos-cabeca.

A matriz armazena apenas os valores diferentes de zero. Cada valor armazenado eh
um no que pertence a duas listas circulares ao mesmo tempo: a lista da linha
(ligada pelo ponteiro `direita`) e a lista da coluna (ligada pelo ponteiro `abaixo`).

A estrutura usada eh a representacao classica de matriz esparsa descrita por
Nivio Ziviani no livro *Projeto de Algoritmos com Implementacoes em Pascal e C*.

## Estrutura

- `src/`: codigo do trabalho em C (matriz.h, matriz.c, main.c, testes.c).
- `build/`: executaveis gerados localmente.
- `DOCUMENTO.md`: explicacao dos metodos criados e dos desafios.
- `interface-web/`: interface web auxiliar para visualizar a estrutura interna
  em tempo real, com demo animada. Veja o `README.md` dentro da pasta.

## Como compilar

Use:

```sh
gcc -Wall -Wextra src/main.c src/matriz.c -o build/trabalho_matriz_esparsa
```

Depois execute:

```sh
./build/trabalho_matriz_esparsa
```

O programa principal abre um menu no terminal para criar a matriz, inserir valor,
remover valor, consultar posicao, buscar valor, imprimir vizinhos, imprimir a matriz
completa, imprimir a forma esparsa com apenas as coordenadas armazenadas e
demonstrar as operacoes de soma e multiplicacao de matrizes.

## Como testar

Use:

```sh
gcc -Wall -Wextra src/testes.c src/matriz.c -o build/testes_matriz_esparsa
./build/testes_matriz_esparsa
```

A suite cobre criacao, insercao, remocao, consulta, busca, contagem, casos de
borda, a estrutura interna completa do exemplo classico do Ziviani (verificando
cada ponteiro um a um) e as operacoes de soma e multiplicacao de matrizes.

## Interface web (extra)

A pasta `interface-web/` contem uma pagina HTML que executa o programa em C real
e mostra a estrutura interna sendo construida em tempo real, com:

- demo animada do exemplo do Ziviani com narracao passo a passo do algoritmo
- painel de comparacao de memoria entre matriz densa e esparsa
- saida exata do programa em C no mesmo painel

Para usar, rode `python3 server.py` na pasta `interface-web` e abra
`http://127.0.0.1:8080`.
