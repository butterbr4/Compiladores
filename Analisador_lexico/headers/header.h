#ifndef HEADER_H
#define HEADER_H

#define tamanho_cadeia 100   // Define o tamanho da string que sera armazenada na cadeia

typedef struct Token {
    char *cadeia;
    char *tipo;
} Token;

Token * alloc_token();      // Funcao que aloca memoria para um token
void free_token(Token *tk); // Funcao que libera a memoria alocada para um token

#endif