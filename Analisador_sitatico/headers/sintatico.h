#ifndef SINTATICO_H
#define SINTATICO_H

#include "lexico.h"
#include <stdio.h>

typedef struct{
    int linha;
    
} Erro;

// Verifica o tipo do token
int is_tk_type(const char *type);

// Funcao que verifica a sintaxe do codigo e retorna 1 se nao houver erros, 0 caso contrario
int sintatico(FILE *file_in, FILE *file_out);

extern char *folower_table[][3];  // Tabela de seguidor

#endif