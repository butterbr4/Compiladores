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
void programa();
void bloco();
void declaracao();
void constante();
void variavel();
void procedimento();
void comando();
void expressao();
void variavel();
void termo();
void fator();
void condicao();
void relacional();
void mais_fatores();
void mais_termos();
void mais_variaveis();
void operador_unario();
void mais_cmd();
void mais_var();
void mais_const();



extern char *folower_table[][3];  // Tabela de seguidor

#endif