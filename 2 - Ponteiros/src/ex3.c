#include <stdio.h>

void questao3()
{
    printf(
        "#include <stdio.h>\n"
        "int main() {\n"
        " int x, *p, **q;\n"
        " p = &x;\n"
        " q = &p;\n"
        " x = 10;\n"
        " printf(\"\\n%%d\\n\", &q);\n"
        " return(0);\n"
        "}\n\n"
        "O erro desse codigo está na linha do printf, como a questao pede que o numero 10 apareca na saida, o \"&q\" deveria ser\n"
        "\"**q\". Da forma que está, o que aparece eh o endereco de memoria do ponteiro duplo q, para desferenciá-lo eh necessario\n"
        "\"**q\".\n"
    );
}

int main (void)
{
    questao3();
    return 1;
}
