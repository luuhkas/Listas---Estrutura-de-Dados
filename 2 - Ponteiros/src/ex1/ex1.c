#include <stdio.h>

void questao1()
{
    printf(
        "p++: O ponteiro p passa a apontar para o proximo endereco de memoria.\n"
        "(*p)++: *p o ponteiro eh desferenciado, ou seja, o que esta sendo acessado eh o conteudo do endereco de memoria. Nesse caso em especifico, esta sendo adicionado 1 ao endereco.\n"
        "*(p++): o ponteiro primeiro passa a apontar para o proximo endereco de memoria e depois eh desferenciado, como no exemplo anterior, acessa o conteudo do endereco de memoria.\n"
        "*(p+10): bem similar a questao anterior, a diferenca aqui eh que o inves de ser adicionado 1 ao endereco de memoria, aqui sao adicionados 10 ao endereco. E depois eh desferenciado.\n");
}

int main(void)
{
    questao1();
    return 0;
}