
#ifndef P1_TABOASIMBOLOS_H
#define P1_TABOASIMBOLOS_H

// función que inicializa a estrutura de datos e inserta as palabras reservadas
void inicioTaboa();

/* función que inserta na táboa un compoñente léxico
 * e devolve o número asociado
 * (se xa existe devolve o número asociado)
 * */
int insertarNaTaboa(char* cadea);

// función que imprime a táboa recorrendo a estrutura de datos
void imprimirTaboa();

/* función que elimina a táboa destruíndo a estrutura de datos
 * e liberando a memoria asociada
 * */
void destruirTaboa();

//obtén o valor dunha variable ou constante
double obterValor(char* cadea);

//comproba se existe un lexema na táboa
int existe(char* cadea, int tipo);

//inserta ou modifica unha variable
double modOUinsVar(char* cadea, double val);

// executa unha función dunha variable
double execFunc(char* cl, double val);

// executa unha función de dúas variables
double exec2Func(char* cl, double val1, double val2);

// imprime o espazo de traballo
void mostrarVal();


#endif //P1_TABOASIMBOLOS_H
