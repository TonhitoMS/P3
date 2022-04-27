%{

#include <math.h>
#include <stdio.h>
#include "lex.yy.h"
#include "TaboaSimbolos.h"
#include "Definicions.h"

//funcións e variables que se empregan
void axuda();
void yyerror(char* s);
void simbolo();
int imp;

%}

%union {
double val; // no caso de números
char *lex; // no caso de caracteres
}

//directiva para liberar a memoria dunha cadea en caso de erro
%destructor { free($$);} <lex>
%destructor { free($$);} ARQUIVO

//declaración de bison
%token <val> NUM
%token <lex> ID
%token AXUDA
%token VERVA
%token LIMPAR
%token LER
%token ARQUIVO
%type <lex>ARQUIVO
%type <val> exp

%right '='
%left '-' '+'
%left '*' '/'
%left NEG /* negación*/
%right '^' /* exponenciación */

%%

input: /* cadena vacía */
    | input line
;

line: '\n'
    | exp '\n' { printf ("\t%.10f\n", $1); simbolo();}
    | exp ';' '\n' {printf("\n"); simbolo();}
    | comando '\n'
    | comando '\n' ';'
    | error '\n' { yyclearin; }
;

exp: NUM { $$ = $1;}
    | ID    {   //comprobamos se existe a variable ou constante
                if(existe($1, ID) || existe($1, CONS)){
                    $$ = obterValor($1);
                }
                else{
                    yyerror("A variable non foi inicializada\n");
                    free($1);
                    YYERROR;
                }
                free($1);
            }
    | ID '=' exp {
                    if(!existe($1, CONS)){
                        $$ = modOUinsVar($1, $3);
                    }
                    else{
                        yyerror("O identificador é unha constante\n");
                        free($1);
                        YYERROR;
                    }
                    free($1);
                }
    | ID '(' exp ')' {
                        if(existe($1, FUNC)){
                            $$ = execFunc($1, $3);
                            free($1);
                        }
                        else{
                            yyerror("A función non existe\n");
                            YYERROR;
                        }
                    }
    | ID '(' exp ',' exp ')' {
                            if(existe($1, FUNC)){
                                $$ = exec2Func($1, $3, $5);
                                free($1);
                            }
                            else{
                                yyerror("A función non existe\n");
                                YYERROR;
                            }
                        }
    | exp '+' exp { $$ = $1 + $3;}
    | exp '-' exp { $$ = $1 - $3; }
    | exp '*' exp { $$ = $1 * $3; }
    | exp '/' exp { $$ = $1 / $3; }
    | '-' exp %prec NEG { $$ = -$2; }
    | exp '^' exp {
                    $$ = exec2Func("pow", $1, $3);
                }
    | '(' exp ')' { $$ = $2; }
;

comando:    AXUDA { axuda(); simbolo();}
        |   VERVA {
                    mostrarVal();
                    printf("\n");
                    simbolo();
                    }
        |   LER '(' ARQUIVO ')' {
                                    iniciar($3);
                                    free($3);
                                    simbolo();
                                }
        |   LIMPAR {destruirTaboa(); inicioTaboa(); simbolo();}
;

%%

void yyerror(char* s)
{
    printf ("%s\n", s);
    simbolo();
}

void simbolo(){
    if(imp)
        printf("> ");
}

void axuda(){
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
}
