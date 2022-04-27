
#include "TaboaSimbolos.h"
#include "lex.yy.h"
#include "aSin.tab.h"
#include <stdio.h>
#include <stdlib.h>

int imp;

int main(int argc, char **argv) {

    //inicializamos a táboa de símbolos
    inicioTaboa();

    printf("***** Esta é a calculadora científica. Para información sobre a axuda introduza 'axd'\n\n> ");

    //activamos a impresión do símbolo '>'
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
    imprimirTaboa();


    //eliminamos a táboa de símbolos (liberando a memoria asociada)
    printf("Eliminando táboa\n");
    destruirTaboa();

    return 0;
}
