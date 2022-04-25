#ifndef P2_LEX_YY_H
#define P2_LEX_YY_H

typedef struct{
    // array de caracteres que almacena o lexema
    char* lex;
    // tipo de compoñente léxico segundo Definicions.h
    int tipo;
}CompLex;

//función que abre o arquivo co que traballará o analizador
void iniciar(char* arquivo);

// función que devolve o seguinte lexema e un 0 cando se chega ao final
int sigLex(CompLex *lex);

// función que pecha o arquivo que le o analizador
void pechar();

extern int yylex();

#endif //P2_LEX_YY_H
