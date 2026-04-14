#include <stdio.h>

int main(void)
{
    char s[10] = "abcde";
    char* cptr;

    cptr = s;

    for(int i = 0; i < 5; i++)
        printf("%c ", *(cptr + i));

    return 0;
}

/*
Questão interessante. A lógica aqui é apontar pra string s. Sabendo 
que quando se aponta para uma array o ponteiro aponta para a primeira casa da mesma
depois foi preciso criar um laço com uma aritimetica de vetores para andar nas casas da string
aproveitei para fazer isso dentro de um print para já ir imprimindo.
*/