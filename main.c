
#include "TaboaSimbolos.h"
#include "AnalizadorSintactico.h"
#include "lex.yy.h"
#include "aSin.tab.h"
#include <stdio.h>
#include <stdlib.h>


int main() {
    //char numero[20];
    //inicializamos a táboa de símbolos e o analizador flex
    inicioTaboa();

    //iniciar("concurrentSum.go");

    //comezamos a análise do ficheiro indicado anteriormente
    //analise();
    /*scanf("%s", numero);
    printf("Número: %f\n", atof(numero));*/
    yyparse();


    //imprimimos a táboa de símbolos ao finalizar a análise
    //imprimirTaboa();

    //pechamos o ficheiro de entrada do analizador de flex
    //pechar();

    //eliminamos a táboa de símbolos (liberando a memoria asociada)
    destruirTaboa();

    return 0;
}
