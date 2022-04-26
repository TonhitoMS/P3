
#include "TaboaSimbolos.h"
#include "AnalizadorSintactico.h"
#include "lex.yy.h"
#include "aSin.tab.h"
#include <stdio.h>
#include <stdlib.h>

int imp;

int main(int argc, char **argv) {
    //char numero[20];
    //inicializamos a táboa de símbolos e o analizador flex
    inicioTaboa();

    //iniciar("concurrentSum.go");

    //comezamos a análise do ficheiro indicado anteriormente
    //analise();
    imp = 1;
    if(argc > 2){
        printf("Introduce %s e opcionalmente un arquivo para realizar a lectura\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    else if(argc == 2){
        iniciar(argv[1]);
    }

    yyparse();


    //imprimimos a táboa de símbolos ao finalizar a análise
    //imprimirTaboa();

    //pechamos o ficheiro de entrada do analizador de flex
    //pechar();

    //eliminamos a táboa de símbolos (liberando a memoria asociada)
    printf("Eliminando táboa\n");
    destruirTaboa();

    return 0;
}
