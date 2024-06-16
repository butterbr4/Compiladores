#ifndef LEXICO_H
#define LEXICO_H

#define tamanho_cadeia 1024   // Define o tamanho da string que sera armazenada na cadeia


typedef struct Token {
    char *cadeia;
    char *tipo;
    unsigned int line;
} Token;

void free_token(Token *tk);  // Funcao que libera a memoria alocada para um token
Token * create_token(char *cadeia, char *tipo, unsigned int line);  // Funcao que cria um token
Token * lexico(FILE *file);  // Funcao que le um arquivo e retorna o proximo token a cada chamada

extern char *transition_table[][3];  // Tabela de transição

#endif
