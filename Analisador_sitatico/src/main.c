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

    if(sintatico(file_in)){  // Se nao houver erros sintaticos na compilacao
        fprintf(file_out, "Compilação realizada com sucesso, parece que você se tornou um mestre da programação!\n");
    } else {
        fprintf(file_out, "\nCada erro é uma chance de aprender. Não desista!\n");
    }

    fclose(file_in);   // Fecha o arquivo de entrada
    // Ao chamar a funcao sintatico() é criado um arquivo
    // de saida "saida.txt" e é preciso fechá-lo
    fclose(file_out);   // Fecha o arquivo de saida
}