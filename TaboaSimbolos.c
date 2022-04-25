#include "TaboaSimbolos.h"
#include "abb.h"
#include <stdio.h>
#include "Definicions.h"
#include <math.h>
#include "aSin.tab.h"


// declaramos a estrutura de datos como variable global
abb taboa;

void inicioTaboa(){
    // array de estruturas que conteñen as palabras reservadas e o número asociado
    tipoelem palabras[] = {
            {"pi", CONS, .valor.var = PI},
            {"e", CONS, .valor.var = EU},
            {"sen", FUNC, .valor.func = sin},
            {"cos", FUNC, .valor.func = cos},
            {"sqrt", FUNC, .valor.func = sqrt},
    };

    // inicializamos a estrutura de datos
    crear(&taboa);

    // recorremos o array de palabras reservadas insertándoas na estrutura de datos
    for (int i = 0; i < sizeof(palabras) / sizeof(tipoelem); ++i) {
        insertar(&taboa, palabras[i]);
    }

    // mostramos a táboa por pantalla
    imprimirTaboa(taboa);
}

void imprimirTaboa(){
    // chamamos á función que imprime a estrutura de datos
    printf("\n\n-------------------Táboa de símbolos-------------------\n");
    imprimir(taboa);
    printf("-------------------------------------------------------\n\n");

}

void destruirTaboa(){
    // destruímos a táboa eliminando a estrutura de datos (libera a memoria asociada)
    destruir(&taboa);
}

int insertarNaTaboa(char* cadea){
    /* introducimos a cadea na estrutura tipoelem que recibirá e función da estrutura de datos.
     * O número asociado é 0 por elección, xa que todos os lexemas novos que se introducen na
     * táboa de símbolos son identificadores
     * */
    tipoelem elemento = {cadea, 0};
    // chamamos á función da estrutura de datos e devolvemos o número asociado ao lexema
    return buscarInsertar(&taboa, elemento);
}

int existe(char* cadea, int tipo){
    return existeComp(taboa, cadea, tipo);
}

double obterValor(char* cadea){
    return obterValorVar(taboa, cadea);
}

double modOUinsVar(char* cadea, double val){
    return modInsVar(&taboa, cadea, val);
}

double execFunc(char* cl, double val){
    return execFuncVar(taboa, cl, val);

}

void mostrarVal(){
    imprimirVar(taboa);
}

