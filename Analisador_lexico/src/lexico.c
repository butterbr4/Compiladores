/*
s=estado inicial
c=próximo símbolo da cadeia
enquanto (c!=EOF) faça
s=transição(s,c)
se s for indefinido
então retornar “falhou”
c=próximo símbolo da cadeia
fim-enquanto
se s for um estado final
então retornar “cadeia aceita”
senão retornar “falhou”
*/

#include <stdio.h>
#include "headers/header.h"

Token * lexico(FILE *file) {
    char *cadeia;
    Token *tk;
    int estado = 0;
    cadeia = fgets();
    char c;
    int i = 0;
    
    while(estado != estado_final){
        estado = transicao(estado, simbolo_cadeia);
    }
   
    return tk;
}

