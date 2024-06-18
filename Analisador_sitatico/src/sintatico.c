#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../headers/sintatico.h"

FILE *file_out;  // Arquivo de saida

// Verifica o tipo do token
int tk_type(Token *token, const char *type){
    if(token == NULL){
        return 0;
    }
    return (strcmp(token->tipo, type) == 0);
}

// Funcao que verifica a sintaxe do codigo e retorna 1 se nao houver erros, 0 caso contrario
int sintatico(FILE *file){
    // Abre o arquivo de saida
    file_out = fopen("saida.txt", "w");
    if (file_out == NULL) {
        printf("Failed to open file\n");
        return 0;
    }

    bloco( );   
    
    Token *token = lexico(file);  // Le o proximo token

    if(tk_type(token,"ponto")){  // Se terminar o programa com ponto
        free_token(token);
        return 1;
    }
    fprintf(file_out, "Erro sintático na linha %d: ponto final esperado\n", token->line);
    free_token(token);
    return 0;
}


void bloco( ){
    Token *token = lexico(file_out);  // Le o proximo token

    if(tk_type(token,"const")){  // Se for const
        dcl_const( );  // Chama dcl_const
        token = lexico(file_out);  // Le o proximo token
    }

    if(tk_type(token,"ponto_virgula")){  // Se for ponto_virgula
        dcl_var( );  // Chama dcl_var
        token = lexico(file_out);  // Le o proximo token
    }

    if(tk_type(token,"ponto_virgula")){  // Se for ponto_virgula
        dcl_proc( );  // Chama dcl_proc
        token = lexico(file_out);  // Le o proximo token
    }

    comando( );  // Chama comando
}

// procedimento( );
    // mais_const( );
    // mais_var( );
    // comando( );
    // expressao( );
    // mais_cmd( );
    // mais_termos( );