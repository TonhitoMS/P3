cmake_minimum_required(VERSION 3.22)
project(P3 C)

set(CMAKE_C_STANDARD 99)

add_compile_options(-Wall -Wextra -pedantic)

add_executable(P3 main.c abb.h Definicions.h TaboaSimbolos.h XestionErros.h lex.yy.h aSin.tab.h
        main.c abb.c TaboaSimbolos.c XestionErros.c lex.yy.c aSin.tab.c)

target_link_libraries(P3 m)
