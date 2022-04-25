%{

//yylex_destroy(); yylexterminate();

//incluímos as cabeceiras necesarias


#include "Definicions.h"
#include "XestionErros.h"
#include "TaboaSimbolos.h"
#include "lex.yy.h"
#include "aSin.tab.h"
#include <stdlib.h>

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

OP_ASIG			:=
OP_FRECHA		<-
OP_SUMA_ASIG		\+=
OPEPUN			[+\-*/%&|^<>=!~,.;:[\]{}()]

DECIMAL_DS		{DECIMAL_D}(_?{DECIMAL_D})*
OCTAL_DS		{OCTAL_D}(_?{OCTAL_D})*
BIN_DS			{BIN_D}(_?{BIN_D})*
HEX_DS			{HEX_D}(_?{HEX_D})*
DECIMAL_L		0|([1-9]_?{DECIMAL_DS}?)
BIN_L			0[Bb]_?{BIN_DS}
OCTAL_L			0[Oo]?_?{OCTAL_DS}
HEX_L			0[Xx]_?{HEX_DS}
INT_L			{DECIMAL_L}|{OCTAL_L}|{HEX_L}|{BIN_L} 

HEX_E			[Pp][+-]?{DECIMAL_DS}
HEX_M			_?{HEX_DS}\.{HEX_DS}?|_?{HEX_DS}|\.{HEX_DS}
HEX_FL_L		0[Xx]{HEX_M}{HEX_E}
DECIMAL_E		[Ee][+-]?{DECIMAL_DS}
DECIMAL_FL_L		({DECIMAL_DS}\.{DECIMAL_DS}?{DECIMAL_E}?)|({DECIMAL_DS}{DECIMAL_E})|(\.{DECIMAL_DS}{DECIMAL_E}?)
FLOAT_L			{DECIMAL_FL_L}|{HEX_FL_L} 

IMAG_L			({DECIMAL_DS}|{INT_L}|{FLOAT_L})i 

ESC_LETRA		\\[abfnrtv'"\\]
GRAN_U_V		\\U{HEX_D}[8]
MINI_U_V		\\u{HEX_D}[4]
HEX_B_V			\\x{HEX_D}[2]
OCTAL_B_V		\\{OCTAL_D}[3]
BYTE_V			{OCTAL_B_V}|{HEX_B_V}
UNICODE_V		{U_CARACTER}|{MINI_U_V}|{GRAN_U_V}|{ESC_LETRA}
RUNE_L			['](UNICODE_V|BYTE_VALUE)[']

CADEA_I_L		["]({UNICODE_V}|{BYTE_V})*["]
CADEA_R_L		[']({U_CARACTER}|{U_LINEANOVA})*[']
CADEA_L			{CADEA_R_L}|{CADEA_I_L}


%%

""
"sair"          yyterminate();
"axd"           return AXUDA;
"verva"         return VERVA;
{U_LINEANOVA}   return ((int) *yytext);
{ESPAZOTAB}
{COM_LINEA}
{COM_BLOQUE}
{IDENTIFICADOR}		yylval.lex = strdup(yytext); return ID;
{OP_ASIG}		return OP_ASIG;
{OP_FRECHA}		return OP_FRECHA;
{OP_SUMA_ASIG}		return OP_SUMA_ASIG;
{OPEPUN}		return (int) *yytext;
{CADEA_L}		return STRING;
{INT_L}			yylval.val = atof(yytext); return NUM;
{FLOAT_L}		yylval.val = atof(yytext); return NUM;
{IMAG_L}		return IMAXINARIO;
.			return -1;
<<EOF>>         yyterminate();
	

%%































