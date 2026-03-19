#include <stdio.h>

void questao2()
{
    printf(
        "#include <stdio.h>\n\n"
        "int main()\n"
        "{\n"
        "    int y, *p, x;\n"
        "    y = 0; // a variavel y esta recebendo o valor de 0.\n"
        "    p = &y; // o ponteiro p agora esta apontando para o endereco de memoria da variavel y\n"
        "    x = *p; // *p: esta desferenciando o ponteiro p e acessando o conteudo desse endereco, que nesse caso eh 0. x recebe esse valor\n"
        "    x = 4; // a variavel x recebe o valor 4\n"
        "    (*p)++; // novamente, o ponteiro p eh desferenciado e o conteudo de p eh acessado, em seguida, eh adicionado 1 a esse conteudo. 0 + 1 = 1.\n"
        "    x--; // eh subtraido 1 da variavel x. que era 4 e agora fica 3.\n"
        "    (*p) += x; // p eh desferenciado, novamente. O valor do endereco de memoria que p aponta era 1 e agora foi somado a x q eh 3. Depois da soma, o valor do conteudo desse endereco fica 4.\n"
        "    printf(\"y = %%d\\n\", y); // o valor encontrado aqui eh 4, pois as mudancas foram feitas atraves do acesso do ponteiro p e p estava apontando para o endereco de y.\n"
        "    return(0);\n"
        "}\n"
    );
}

int main (void)
{
    questao2();
    return 0;
}