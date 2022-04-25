%{


#include <math.h>
#include <stdio.h>
#include "lex.yy.h"
#include "TaboaSimbolos.h"


void yyerror(char* s);


%}

%union {
double val; /* Para devolver números */
char *lex; /* Para devolver punteros a la tabla de símbolos */
}

/* Declaraciones de BISON */
%token <val> NUM
%token <lex> ID
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
    | error '\n' { yyerrok; }
;

exp: NUM { $$ = $1;}
    | ID    {
                if(existe($1)){
                    $$ = obterValor($1);
                }
                else{
                    yyerror("A variable non foi inicializada\n");
                }
            }
    | ID '=' exp { /* Comprobar se é unha constante cando se modifica */
                        $$ = modOUinsVar($1, $3);
                    }
    | ID '(' exp ')' { printf("Función\n");; }
    | exp '+' exp { $$ = $1 + $3;}
    | exp '-' exp { $$ = $1 - $3; }
    | exp '*' exp { $$ = $1 * $3; }
    | exp '/' exp { $$ = $1 / $3; }
    | '-' exp %prec NEG { $$ = -$2; }
    | exp '^' exp { $$ = pow ($1, $3); }
    | '(' exp ')' { $$ = $2; }
;

%%

void yyerror(char* s)
{
printf ("%s\n", s);
}
