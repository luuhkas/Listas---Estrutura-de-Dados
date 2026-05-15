# Documento do Trabalho - Matriz Esparsa

## Objetivo

Este trabalho implementa uma matriz esparsa de inteiros usando lista cruzada com
nos-cabeca. Diferente de uma matriz convencional, a matriz esparsa armazena
apenas as posicoes com valor diferente de zero. Isso economiza memoria quando a
maior parte das posicoes da matriz vale zero.

## Estruturas usadas

A estrutura `Node` guarda:

- coordenada `linha`;
- coordenada `coluna`;
- valor inteiro;
- ponteiro `direita` para o proximo no na mesma linha;
- ponteiro `abaixo` para o proximo no na mesma coluna.

A estrutura `MatrizEsparsa` guarda:

- quantidade de linhas;
- quantidade de colunas;
- ponteiro `inicio`, que aponta para o no principal da estrutura.

## Como a estrutura eh montada

A matriz esparsa eh feita com listas circulares. A montagem usa tres tipos de nos:

- Um no principal com `linha = -1` e `coluna = -1`. Eh o ponto de partida da
  estrutura inteira.
- Uma cabeca para cada coluna, com `linha = -1`. Essas cabecas ficam ligadas em
  sequencia pelo ponteiro `direita`, formando uma lista circular que comeca e
  termina no no principal.
- Uma cabeca para cada linha, com `coluna = -1`. Essas cabecas ficam ligadas em
  sequencia pelo ponteiro `abaixo`, formando outra lista circular que comeca e
  termina no no principal.

Cada no real (que guarda um valor diferente de zero) pertence a duas listas ao
mesmo tempo: a lista da linha em que esta e a lista da coluna em que esta. As
duas listas sao circulares e ordenadas por coluna (na lista da linha) e por linha
(na lista da coluna).

Apenas os valores diferentes de zero ocupam memoria. As posicoes que valem zero
nao tem no. Por isso o consumo de memoria fica proporcional ao numero de
valores nao zero, em vez de proporcional a `linhas * colunas`.

## Funcionamento dos metodos

`criarMatriz` cria o no principal e depois cria uma cabeca para cada coluna e
uma cabeca para cada linha. As duas sequencias de cabecas viram listas circulares
que comecam e terminam no no principal. Nenhum valor eh armazenado nesse
momento, a matriz comeca vazia.

`desalocarMatriz` percorre todas as cabecas de linha, libera os nos que
existem em cada linha e depois libera a propria cabeca. Em seguida libera as
cabecas de coluna, o no principal e a estrutura da matriz.

`inserirValor` recebe linha, coluna e valor. Primeiro confere se a posicao esta
dentro dos limites. Se o valor recebido for zero, chama `removerValor` para
manter a invariante de que zero nao ocupa no. Se ja existe um no naquela
posicao, atualiza o valor. Caso contrario, cria um no novo e o encaixa em ordem
nas listas da linha e da coluna correspondentes.

`removerValor` procura o no em uma posicao especifica. Se ele existe, religa
o no anterior na lista da linha e o no anterior na lista da coluna. Em
seguida libera a memoria do no removido.

`consultarPosicao` localiza a cabeca da linha desejada e percorre a lista da linha
ate achar a coluna desejada. Se achar, retorna o ponteiro do no. Se a posicao
estiver fora dos limites ou nao houver no naquela posicao, retorna `NULL`.

`obterValor` retorna o valor inteiro da posicao consultada. Se nao existir no,
retorna zero, porque essa eh a regra da matriz esparsa.

`buscarValor` percorre todos os nos da matriz procurando o primeiro com o
valor informado. Se encontrar, retorna o ponteiro daquele no. Se nao
encontrar, retorna `NULL`.

`imprimirMatriz` mostra a matriz no formato de tabela. Para cada linha percorre
a lista da linha. Quando a coluna atual da lista bate com a coluna sendo
impressa, mostra o valor armazenado. Caso contrario, imprime espaco em branco,
reforcando visualmente que aquela posicao nao ocupa memoria na estrutura.

`imprimirEsparsa` mostra apenas as coordenadas com valor diferente de zero,
junto com o total de posicoes e a contagem de armazenadas. Eh a visao mais
proxima do conceito de matriz esparsa.

`imprimirVizinhos` mostra os quatro vizinhos logicos de uma posicao (cima,
baixo, esquerda e direita). Como na matriz esparsa os ponteiros `direita` e
`abaixo` apontam para o proximo no nao zero (e nao para a posicao
imediatamente adjacente), os vizinhos sao obtidos consultando as coordenadas
`(linha-1, coluna)`, `(linha+1, coluna)`, `(linha, coluna-1)` e
`(linha, coluna+1)`. A funcao diferencia tres situacoes na saida: quando o
vizinho esta fora dos limites da matriz, imprime "fora dos limites"; quando
a posicao existe na matriz mas nao tem no armazenado, imprime "vazio";
quando a posicao tem no armazenado, imprime o valor.

`contarNaoZeros` percorre todas as listas de linha e conta quantos nos
existem.

## Interface

O arquivo `main.c` tem um menu por terminal. As opcoes sao:

- criar matriz;
- inserir valor;
- remover valor;
- consultar posicao;
- buscar valor;
- imprimir vizinhos;
- imprimir matriz completa;
- imprimir forma esparsa;
- sair.

A matriz completa eh exibida sempre que a estrutura muda, para facilitar
acompanhar o efeito de cada operacao.

## Desafios e dificuldades

O ponto mais delicado foi manter a ordenacao das duas listas em que cada
no participa. Cada insercao precisa percorrer a lista da linha para achar
o lugar certo entre os nos ja existentes e tambem percorrer a lista da
coluna pelo mesmo motivo. Sem essa ordenacao, as buscas e a impressao
ficariam incorretas, porque dependem de encontrar as colunas em ordem
crescente dentro de cada linha.

Outro cuidado importante foi a remocao. Como o no pertence a duas listas
ao mesmo tempo, para remover foi preciso localizar o no anterior em cada
uma das listas e religar os ponteiros antes de liberar a memoria. Tambem foi
preciso tratar o caso de inserir o valor zero, que na matriz esparsa significa
remover o no da estrutura em vez de armazenar.

A liberacao tambem exigiu cuidado, porque as cabecas de linha e de coluna
formam listas circulares. Foi preciso percorrer cada lista comparando o
ponteiro atual com o no principal para nao entrar em loop infinito.

## Referencias

A representacao de matriz esparsa por lista cruzada de listas circulares com
nos-cabeca usada neste trabalho eh descrita no livro *Projeto de Algoritmos
com Implementacoes em Pascal e C*, de Nivio Ziviani, no exercicio sobre
matrizes esparsas do capitulo de listas encadeadas.
