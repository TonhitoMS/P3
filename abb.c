#include "abb.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Definicions.h"
#include "aSin.tab.h"


///////////////////////// ESTRUTURAS DE DATOS



struct celda {
    tipoelem info;
    struct celda *izq, *der;
};

//////////////////////// FUNCIÓNS



/*Extraer la clave de una celda */
tipoclave _clave_elem(tipoelem *E) {
    return E->lexema;
}

/* Esta funcion puente nos permite modificar el tipo de
 * de datos del TAD sin tener que cambiar todas las 
 * comparaciones del resto de la biblioteca y en su lugar
 * cambiando solo esta. */
int _comparar_claves(tipoclave cl1, tipoclave cl2) {
    return strcmp(cl1,cl2) == 0 ? 0 : strcmp(cl1, cl2) > 0 ? 1 : -1;
}

/* Si tipoelem tiene alguna estructura que necesite 
 * destruirse ha de hacerse aqui. El uso de esta funcion
 * permite hacer mas eficiente la destruccion del arbol.*/
void _destruir_elem(struct tipoelem *E) {
    free(E->lexema);
}

//OPERACIONES DE CREACIÓN Y DESTRUCCIÓN

void crear(abb *A) {
    *A = NULL;
}

void destruir(abb *A) {
    if (*A != NULL) {
        destruir(&(*A)->izq);
        destruir(&(*A)->der);
        _destruir_elem(&((*A)->info));
        free(*A);
        *A = NULL;
    }
}

//OPERACIONES DE INFORMACIÓN

unsigned es_vacio(abb A) {
    return A == NULL;
}

abb izq(abb A) {
    return A->izq;
}

abb der(abb A) {
    return A->der;
}

void leer(abb A, tipoelem *E) {
    *E = A->info;
}
// Función privada para comparar las claves

int _comparar_clave_elem(tipoclave cl, tipoelem E) {
    return _comparar_claves(cl, _clave_elem(&E));
}
//Función privada para informar si una clave está en el árbol

unsigned _es_miembro_clave(abb A, tipoclave cl) {
    if (es_vacio(A)) {
        return 0;
    }
    int comp = _comparar_clave_elem(cl, A->info);

    if (comp == 0) { //cl == A->info
        return 1;
    }
    if (comp > 0) { //cl > A->info
        return _es_miembro_clave(der(A), cl);
    }
    //cl < A->info
    return _es_miembro_clave(izq(A), cl);
}

//Funciones públicas

unsigned es_miembro(abb A, tipoelem E) {
    return _es_miembro_clave(A, _clave_elem(&E));
}

void buscar_nodo(abb A, tipoclave cl, tipoelem *nodo) {
    if (es_vacio(A)) {
        return;
    }
    int comp = _comparar_clave_elem(cl, A->info);

    if (comp == 0) { // cl == A->info
        *nodo = A->info;
    } else if (comp < 0) { // cl < A->info
        buscar_nodo(A->izq, cl, nodo);
    } else { // cl > A->info
        buscar_nodo(A->der, cl, nodo);
    }
}
//OPERACIONES DE MODIFICACIÓN

/* Funcion recursiva para insertar un nuevo nodo 
   en el arbol. Se presupone que no existe un nodo
   con la misma clave en el arbol. */
void insertar(abb *A, tipoelem E) {
    if (es_vacio(*A)) {
        *A = (abb) malloc(sizeof (struct celda));
        (*A)->info.lexema = (char*) malloc(strlen(E.lexema) * sizeof(char) +1);
        (*A)->info.lexema[0] = '\0';
        strncat((*A)->info.lexema, E.lexema, strlen(E.lexema));
        (*A)->info.tipo = E.tipo;
        (*A)->info.valor = E.valor;
        (*A)->izq = NULL;
        (*A)->der = NULL;
        return;
    }
    tipoclave cl = _clave_elem(&E);
    int comp = _comparar_clave_elem(cl, (*A)->info);
    if (comp > 0) {
        insertar(&(*A)->der, E);
    } else {
        insertar(&(*A)->izq, E);
    }
}
/* Funcion privada que devuelve mínimo de subárbol dcho */
tipoelem _suprimir_min(abb * A) {//Se devuelve el elemento más a la izquierda
    abb aux;
    tipoelem ele;
    if (es_vacio((*A)->izq)) {//Si izquierda vacía, se devuelve valor nodo actual A
        ele = (*A)->info;
        aux = *A;
        *A = (*A)->der;
        free(aux);
        return ele;
    } else {
        return _suprimir_min(&(*A)->izq); //se vuelve a buscar mínimo rama izquierda
    }
}

/* Funcion que permite eliminar un nodo del arbol */
void suprimir(abb *A, tipoelem E) {
    abb aux;
    if (es_vacio(*A)) {
        return;
    }

    tipoclave cl = _clave_elem(&E);
    int comp = _comparar_clave_elem(cl, (*A)->info);
    if (comp < 0) { //if (E < (*A)->info) {
        suprimir(&(*A)->izq, E);
    } else if (comp > 0) { //(E > (*A)->info) {
        suprimir(&(*A)->der, E);
    } else if (es_vacio((*A)->izq) && es_vacio((*A)->der)) {
        _destruir_elem(&((*A)->info));
        free(*A);
        *A = NULL;
    } else if (es_vacio((*A)->izq)) { // pero no es vacio derecha
        aux = *A;
        *A = (*A)->der;
        _destruir_elem(&aux->info);
        free(aux);
    } else if (es_vacio((*A)->der)) { //pero no es vacio izquierda
        aux = *A;
        *A = (*A)->izq;
        _destruir_elem(&aux->info);
        free(aux);
    } else { //ni derecha ni izquierda esta vacio, busco mínimo subárbol derecho
        _destruir_elem(&(*A)->info); //elimino la info pero no libero el nodo,
        //pues en su sitio voy a poner el mínimo del subárbol derecho
        (*A)->info = _suprimir_min(&(*A)->der);
    }
}

/* Funcion privada para pasar la clave y no tener que
   extraerla del nodo en las llamadas recursivas.*/
void _modificar(abb A, tipoclave cl, tipoelem nodo) {
    if (es_vacio(A)) {
        return;
    }
    int comp = _comparar_clave_elem(cl, A->info);
    if (comp == 0) {
        A->info = nodo;
    } else if (comp < 0) {
        _modificar(A->izq, cl, nodo);
    } else {
        _modificar(A->der, cl, nodo);
    }
}


/* Permite modificar el nodo extrayendo del mismo la clave */
void modificar(abb A, tipoelem nodo) {
    tipoclave cl = _clave_elem(&nodo);
    _modificar(A, cl, nodo);
}

void imprimir(abb A){

    if(!es_vacio(A)){
        if(A->izq != NULL)
            imprimir(A->izq);
        printf("Lexema: %-20s\t", A->info.lexema);
        printf("Compoñente Léxico: %d\n", A->info.tipo);

        if(A->der != NULL)
            imprimir(A->der);

    }
}


int buscarInsertar(abb *A, tipoelem E) {
    //printf("\nLexema árbore: %s\n", E.lexema);
    if (es_vacio(*A)) {
        //printf("\nBaleiro\n");
        //E.tipo = IDENTIFICADOR;
        *A = (abb) malloc(sizeof (struct celda));
        (*A)->info.lexema = (char*) malloc(strlen(E.lexema) * sizeof(char) +1);
        (*A)->info.lexema[0] = '\0';
        strncat((*A)->info.lexema, E.lexema, strlen(E.lexema));
        (*A)->info.tipo = IDENTIFICADOR;
        //printf("\nInfo insertamos: %s\n", (*A)->info.lexema);
        (*A)->izq = NULL;
        (*A)->der = NULL;
        return IDENTIFICADOR;
    }
    tipoclave cl = _clave_elem(&E);
    int comp = _comparar_clave_elem(cl, (*A)->info);
    //printf("Info: %s\nCl: %s\nComp: %d\nTipo: %d\n", (*A)->info.lexema, cl, comp, E.tipo);
    if (comp > 0) {
        return buscarInsertar(&(*A)->der, E);
    } else if(comp == 0){
        //printf("\nIguais\n");
        return (*A)->info.tipo;
    } else {
        return buscarInsertar(&(*A)->izq, E);
    }
}

int existeComp(abb A, char* cl, int tipo){
    if (es_vacio(A)) {
        return 0;
    }
    int comp = _comparar_clave_elem(cl, A->info);

    if (comp == 0 && A->info.tipo == tipo) { // cl == A->info
        return 1;
    } else if (comp < 0) { // cl < A->info
        return existeComp(A->izq, cl, tipo);
    } else { // cl > A->info
        return existeComp(A->der, cl, tipo);
    }

}

double obterValorVar(abb A, char* cl){

    if (es_vacio(A)) {
        return 0;
    }
    int comp = _comparar_clave_elem(cl, A->info);

    if (comp == 0) { // cl == A->info
        return A->info.valor.var;
    } else if (comp < 0) { // cl < A->info
        return obterValorVar(A->izq, cl);
    } else { // cl > A->info
        return obterValorVar(A->der, cl);
    }

    return 0;
}


double modInsVar(abb *A, char* cl, double val) {
    //printf("\nLexema árbore: %s\n", E.lexema);
    if (es_vacio(*A)) {
        //printf("\nBaleiro\n");
        //E.tipo = IDENTIFICADOR;
        *A = (abb) malloc(sizeof (struct celda));
        (*A)->info.lexema = (char*) malloc(strlen(cl) * sizeof(char) +1);
        (*A)->info.lexema[0] = '\0';
        strncat((*A)->info.lexema, cl, strlen(cl));
        (*A)->info.tipo = ID;
        (*A)->info.valor.var = val;
        //printf("\nInfo insertamos: %s\n", (*A)->info.lexema);
        (*A)->izq = NULL;
        (*A)->der = NULL;
        return val;
    }
    int comp = _comparar_clave_elem(cl, (*A)->info);
    //printf("Info: %s\nCl: %s\nComp: %d\nTipo: %d\n", (*A)->info.lexema, cl, comp, E.tipo);
    if (comp > 0) {
        return modInsVar(&(*A)->der, cl, val);
    } else if(comp == 0){
        (*A)->info.valor.var = val;
        return (*A)->info.valor.var;
    } else {
        return modInsVar(&(*A)->izq, cl, val);
    }
}

double execFuncVar(abb A, char* cl, double val){

    if (es_vacio(A)) {
        return 0;
    }
    int comp = _comparar_clave_elem(cl, A->info);

    if (comp == 0) { // cl == A->info
        return A->info.valor.func(val);
    } else if (comp < 0) { // cl < A->info
        return execFuncVar(A->izq, cl, val);
    } else { // cl > A->info
        return execFuncVar(A->der, cl, val);
    }

    return 0;
}

double execFunc2Var(abb A, char* cl, double val1, double val2){

    if (es_vacio(A)) {
        return 0;
    }
    int comp = _comparar_clave_elem(cl, A->info);

    if (comp == 0) { // cl == A->info
        //printf("%lf\n", A->info.valor.func(val1, val2));
        return A->info.valor.func(val1, val2);
    } else if (comp < 0) { // cl < A->info
        return execFunc2Var(A->izq, cl, val1, val2);
    } else { // cl > A->info
        return execFunc2Var(A->der, cl, val1, val2);
    }

    return 0;
}

void imprimirVar(abb A){
    if(!es_vacio(A) ){
        if(A->izq != NULL)
            imprimirVar(A->izq);
        if(A->info.tipo == ID) {
            printf("Nome: %-20s\t", A->info.lexema);
            printf("Valor: %lf\n", A->info.valor.var);
        }

        if(A->der != NULL)
            imprimirVar(A->der);

    }
}



