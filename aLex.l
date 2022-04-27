%{

//yylex_destroy(); yylexterminate();

//incluímos as cabeceiras necesarias


#include "Definicions.h"
#include "XestionErros.h"
#include "TaboaSimbolos.h"
#include "lex.yy.h"
#include "aSin.tab.h"
#include <stdlib.h>

extern int imp;
%}
/* 	
	opcións para evitar erros e warnings,
	e para almacenar o número de liñas na
	variable yylineno
*/
%option noyywrap noinput nounput yylineno

/*
	zona de definicicións, realizadas como aparecen
	na páxina oficial da linguaxe.
	As regras devolven o valor correspondente do arquivo 
	de definicións, segundo o patrón que se emparelle coa entrada.
*/

U_LINEANOVA		\n
U_CARACTER		.
ESPAZOTAB		[[:blank:]]+
U_LETRA			[[:alpha:]]
U_NUMERO		[[:digit:]]	
LETRA			{U_LETRA}|_
DECIMAL_D		{U_NUMERO}
BIN_D			0|1
OCTAL_D			[0-7]
HEX_D			[[:xdigit:]]

COM_LINEA		"//".*
FIN_COM_BLOQUE		"*/"
COM_BLOQUE		"/*"[^{FIN_COM_BLOQUE}]*"*/"

IDENTIFICADOR		{LETRA}({LETRA}|{U_NUMERO})*


OPEPUN			[+\-*/%&|^<>=!~,.;:[\]{}()]

DECIMAL_DS		{DECIMAL_D}(_?{DECIMAL_D})*
DECIMAL_L		0|([1-9]_?{DECIMAL_DS}?)
INT_L			{DECIMAL_L}


DECIMAL_E		[Ee][+-]?{DECIMAL_DS}
DECIMAL_FL_L		({DECIMAL_DS}\.{DECIMAL_DS}?{DECIMAL_E}?)|({DECIMAL_DS}{DECIMAL_E})|(\.{DECIMAL_DS}{DECIMAL_E}?)
FLOAT_L			{DECIMAL_FL_L}




FICHEIRO         ({LETRA}|{U_NUMERO}|\.)+


%%

"limpar"        return LIMPAR;
"ler"           return LER;
"sair"          yyterminate();
"axd"           return AXUDA;
"verva"         return VERVA;
{U_LINEANOVA}   return ((int) *yytext);
{ESPAZOTAB}
{COM_LINEA}
{COM_BLOQUE}
{IDENTIFICADOR}		yylval.lex = strdup(yytext); return ID;
{OPEPUN}		return (int) *yytext;
{INT_L}			yylval.val = atof(yytext); return NUM;
{FLOAT_L}		yylval.val = atof(yytext); return NUM;
{FICHEIRO}       yylval.lex = strdup(yytext); return ARQUIVO;
.		    	erroLexico(yylineno);
<<EOF>>         {pechar(); yyrestart(stdin); printf("> ");}


%%

void iniciar(char* arquivo){
	//abrimos os arquivo comprobando os posibles erros

	printf("Abrindo %s\n", arquivo);
	if((yyin = fopen(arquivo, "r")) == NULL)
		erroLE("Erro abrindo o ficheiro\n");

	// desactivamos a impresión do símbolo '>'
    imp = 0;
}

// pechamos o ficheiro cando rematamos a análise
void pechar(){
	fclose(yyin);
	imp=1;
}





























