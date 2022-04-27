
#include "TaboaSimbolos.h"
#include "lex.yy.h"
#include "aSin.tab.h"
#include <stdio.h>
#include <stdlib.h>

int imp;

int main(int argc, char **argv) {

    //inicializamos a táboa de símbolos
    inicioTaboa();

    printf("-------------------Información sobre a calculadora-------------------\n"
           "\n"
           "Nesta calculadora é posible facer operación básicas e chamar a distintas función, así como introducir comandos.\n"
           "A continuación explicaranse as distintas posibilidades.\n"
           "\n"
           "Comandos dispoñibles:\n"
           "- axd: mostra a axuda.\n"
           "- verva: mostra o espazo de traballo (variables e o seu valor).\n"
           "- ler: a sintaxe é 'ler(arquivo)'. Executa as instrucións contidas nun arquivo.\n"
           "- limpar: elimina o espazo de traballo.\n"
           "- sair: sae do programa, eliminando todas as variables almacenadas.\n"
           "\n"
           "Funcións dispoñibles:\n"
           "- sqrt: a sintaxe é 'sqrt(expresión)'. Calcula a raíz cadrada dun número.\n"
           "- pow: a sintaxe é 'pow(base, expoñenete)'. Calcula a potencia do primeiro número elevado ao segundo. Outra posibilidade é realizalo da forma 'número^número'.\n"
           "- sen: a sintaxe é 'sin(expresión)'. Calcula o seno dun ángulo en radiáns.\n"
           "- cos: igual que a anterior función, pero calcula o coseno.\n"
           "- tan: como nos casos anteriores, pero calcula a tanxente do ángulo.\n"
           "- asen: calcula o arcoseno dun ángulo.\n"
           "- acos: calcula o arcocoseno.\n"
           "- atan: calcula o arcotanxente.\n"
           "- mod: calcula o módulo da división de dous números. A sintaxe é 'mod(n1,n1)'.\n"
           "- exp: calcula o valor exponencial dun número.\n"
           "- ln: calcula o logaritmo en base e do número.\n"
           "- log: logaritmo en base 10 do número.\n"
           "\n"
           "Operacións dispoñibles:\n"
           "- asignación '=': asigna un resultado a unha variables. Se esta non existe créase.\n"
           "- suma '+': realiza a suma de dúas expresións.\n"
           "- resta '-': realiza a resta.\n"
           "- multiplicación '*': realiza a multiplicación.\n"
           "- división '/': realiza a división.\n"
           "- parénteses '()': modifican a precedencia nas operacións.\n"
           "\n"
           "As variables son cadeas alfanuméricas que comezan por unha letra ou un '_'\n"
           "\n"
           "Están definidas as seguintes constantes:\n"
           "- pi: número pi.\n"
           "- e: número de Euler.\n"
           "\n"
           "Se se inclúe o ';' ao final da sentenza, non se imprimirá o resultado;\n"
           "\n");

    printf("***** Esta é a calculadora científica. Para información sobre a axuda introduza 'axd'\n\n> ");


    imp = 1;
    // comprobamos os argumentos e realizamos a análise do ficheiro se procede
    if(argc > 2){
        printf("Introduce %s e opcionalmente un arquivo para realizar a lectura\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    else if(argc == 2){
        iniciar(argv[1]);
    }

    // iniciamos o analizador
    yyparse();


    //imprimimos a táboa de símbolos ao finalizar a análise
    //imprimirTaboa();


    //eliminamos a táboa de símbolos (liberando a memoria asociada)
    printf("Eliminando táboa\n");
    destruirTaboa();

    return 0;
}
