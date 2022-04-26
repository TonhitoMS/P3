%{


#include <math.h>
#include <stdio.h>
#include "lex.yy.h"
#include "TaboaSimbolos.h"
#include "Definicions.h"


void yyerror(char* s);
void simbolo();
extern int imp = 1;

%}

%union {
double val; /* Para devolver números */
char *lex; /* Para devolver punteros a la tabla de símbolos */
}

//directiva para liberar a memoria dunha cadea en caso de erro
%destructor { free($$);} <lex>
%destructor { free($$);} ARQUIVO

/* Declaraciones de BISON */
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
%left NEG /* negación--menos unario */
%right '^' /* exponenciación */
/* A continuación la gramática */

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
    | ID    {
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
    | ID '=' exp { if(!existe($1, CONS)){
                        $$ = modOUinsVar($1, $3);
                    }
                    else{
                        printf("%s é unha constante\n", $1);
                        simbolo();
                    }
                    free($1);
                }
    | ID '(' exp ')' {
                            $$ = execFunc($1, $3);
                            free($1);
                        }
    | exp '+' exp { $$ = $1 + $3;}
    | exp '-' exp { $$ = $1 - $3; }
    | exp '*' exp { $$ = $1 * $3; }
    | exp '/' exp { $$ = $1 / $3; }
    | '-' exp %prec NEG { $$ = -$2; }
    | exp '^' exp { $$ = pow ($1, $3); }
    | '(' exp ')' { $$ = $2; }
;

comando:    AXUDA { printf("Axuda\n"); simbolo();}
        |   VERVA {
                    mostrarVal();
                    printf("\n");
                    simbolo();
                    }
        |   LER '(' ARQUIVO ')' {
                                    imp=0;
                                    iniciar($3);
                                    free($3);
                                }
        |   LIMPAR {destruirTaboa(); inicioTaboa();}
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
