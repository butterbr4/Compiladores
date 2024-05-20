#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../headers/header.h"

int main(int argc, char **argv) {

    // Verifica se a quantidade de argumentos passados é correta
    if ( argc  != 2){
        printf("Quantidade de argumentos errada. Use ""make run ARGS=seu_arquivo.txt"" \n");
        exit(-1);
    }

    // Abre o arquivo de entrada
    FILE *file_in = fopen(argv[1], "r");
    if (file_in == NULL) {
        printf("Failed to open file\n");
        exit(-1);
    }

    // Abre o arquivo de saida
    FILE *file_out = fopen("output.txt", "w");
    if (file_out == NULL) {
        printf("Failed to open file\n");
        exit(-1);
    }

    Token *token;  // Inicializa token

    // Enquanto nao terminar de receber todos os tokens, pega-se o proximo token e escreve no arquivo de saida
    while(1){
        token = lexico(file_in);
          
        if(token != NULL){  // Se nao chegou no final do arquivo escreve o token no arquivo de saida
            fprintf(file_out, "%s, %s\n", token->cadeia, token->tipo);
            free_token(token);
        } else {
            break;  // Se chegou no final do arquivo, sai do loop
        }

    }

    fclose(file_in);   // Fecha o arquivo de entrada
    fclose(file_out);   // Fecha o arquivo de saida
}