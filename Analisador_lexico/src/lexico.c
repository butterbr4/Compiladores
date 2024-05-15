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

// Funcao que aloca memoria para um token
Token * alloc_token(){
        
}

// Funcao que libera a memoria alocada para um token
void free_token(Token *tk){
    free(tk->cadeia);
    free(tk->tipo);
    free(tk);
}

// Esta funcao recebe um arquivo e retorna um token 
Token * lexico(FILE *file) {

    char cadeia[tamanho_cadeia];   // Cadeia de caracteres retirada do arquivo
    char *buffer;   // Guarda os caracteres lidos pelo automato finito
    Token *tk;      // Token a ser retornado
    int *estado;
    estado = malloc(sizeof(int));
    
    fgets(cadeia, tamanho_cadeia, file);
    char c;
    int i = 0;

    // Enquanto nao chegar no final do arquivo, le os caracteres
    while((*estado >= 0) && (!feof(file))){
        // Enquanto nao chegar em um estado final continua lendo a cadeia
        for(int i = 0; (*estado >= 0) && (estado != NULL) && (i < tamanho_cadeia-1); i++, estado++){
            estado = transicao(estado, cadeia[i], buffer);
        }
    }
    free(estado);        
    return tk;
}

int transicao(int *estado, char simbolo, char *buffer){
    
}

