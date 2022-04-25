%{


#include <math.h>
#include <stdio.h>
#include "lex.yy.h"
#include "TaboaSimbolos.h"
#include "Definicions.h"


void yyerror(char* s);


%}

%union {
double val; /* Para devolver números */
char *lex; /* Para devolver punteros a la tabla de símbolos */
}



/* Declaraciones de BISON */
%token <val> NUM
%token <lex> ID
%token AXUDA
%token VERVA
%token LIMPAR
%token LER
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
    | exp '\n' { printf ("\t%.10f\n", $1);}
    | comando '\n'
    | comando '\n' ';'
    | error '\n' { yyclearin; }
;

exp: NUM { $$ = $1;}
    | ID    {
                if(existe($1, ID)){
                    $$ = obterValor($1);
                }
                else{
                    yyerror("A variable non foi inicializada\n");
                }
                free($1);
            }
    | ID '=' exp { if(!existe($1, CONS)){
                        $$ = modOUinsVar($1, $3);
                    }
                    else{
                        printf("%s é unha constante\n", $1);
                    }
                    free($1);
                }
    | ID '(' exp ')' {
                            $$ = execFunc($1, $3);
                        }
    | exp '+' exp { $$ = $1 + $3;}
    | exp '-' exp { $$ = $1 - $3; }
    | exp '*' exp { $$ = $1 * $3; }
    | exp '/' exp { $$ = $1 / $3; }
    | '-' exp %prec NEG { $$ = -$2; }
    | exp '^' exp { $$ = pow ($1, $3); }
    | '(' exp ')' { $$ = $2; }
;

comando:    AXUDA { printf("Axuda\n");}
        |   VERVA {mostrarVal();}
        |   LER {/*empezar ficheiro*/ printf("Ler");}
        |   LIMPAR {destruirTaboa(); inicioTaboa();}
;

%%

void yyerror(char* s)
{
printf ("%s\n", s);
}
