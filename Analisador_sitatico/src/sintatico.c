#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../headers/sintatico.h"


// Verifica o tipo do token
int tk_type(Token *token, const char *type){
    return (strcmp(token->tipo, type) == 0);
}

// Funcao que verifica a sintaxe do codigo e retorna 1 se nao houver erros, 0 caso contrario
int sintatico(FILE *file){
    Token *token = lexico(file);  // Le o primeiro token
    if(tk_type(token,"ponto")){  // Se nao terminar o programa com ponto
        free_token(token);
        return 1;
    }
    free_token(token);  // Libera a memoria alocada para o token
    return 0;
}
