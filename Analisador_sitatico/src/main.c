#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../headers/header.h"

int main(int argc, char **argv) {

    // Verifica se a quantidade de argumentos passados é correta
    // if ( argc  != 2){
    //     printf("Quantidade de argumentos errada. Use ""make run ARGS=seu_arquivo.txt"" \n");
    //     exit(-1);
    // }

    // Abre o arquivo de entrada
    FILE *file_in = fopen("teste.txt", "r");
    if (file_in == NULL) {
        printf("Failed to open file\n");
        exit(-1);
    }

    // Abre o arquivo de saida
    FILE *file_out = fopen("saida.txt", "w");
    if (file_out == NULL) {
        printf("Failed to open file\n");
        exit(-1);
    }

   

    if(sintatico(file_in)){  // Se nao houver erros sintaticos na compilacao
        printf("Compilacao realizada com sucesso\n");
    } else {
        printf("Erro na compilacao\n");
    }

    fclose(file_in);   // Fecha o arquivo de entrada
    fclose(file_out);   // Fecha o arquivo de saida
}