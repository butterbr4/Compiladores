#ifndef SINTATICO_H
#define SINTATICO_H

#include "lexico.h"
#include <stdio.h>

// Verifica o tipo do token
int tk_type(Token *token, const char *type);

// Funcao que verifica a sintaxe do codigo e retorna 1 se nao houver erros, 0 caso contrario
int sintatico(FILE *file); 

#endif