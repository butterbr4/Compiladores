#ifndef HEADER_H
#define HEADER_H

#define tamanho_token 100   // Define o tamanho do token

typedef struct {
    char cadeia[tamanho_token];
    char *tipo = NULL;
} Token;

#endif