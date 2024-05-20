#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../headers/lexico.h"
#include "../headers/hash_2d.h"

// Cria um token
Token* create_token(char *cadeia, char *tipo){
    Token *tk = malloc(sizeof(Token));
    tk->cadeia = strdup(cadeia);    // Copia a cadeia para o token
    tk->tipo = strdup(tipo);        // Copia o tipo para o token
    return tk;
}




// Libera a memoria alocada para um token
void free_token(Token *tk){
    if(tk == NULL || (tk->cadeia) == NULL || (tk->tipo) == NULL){
        return;
    }
    // Libera a memoria alocada para a cadeia e o tipo
    free(tk->cadeia);
    free(tk->tipo);
    free(tk);
}




// Coloca a tabela de transicao em uma tabela hash 2d
hash_table_2d_t* create_transition_table(){
    hash_table_2d_t* table = create_table();

    // Insere os valores na tabela hash 2d
    for(int i = 0; transition_table[i][0] != NULL; i++){
        insert(table, transition_table[i][0], transition_table[i][1], transition_table[i][2]);
    }

    return table;
}




// Esta funcao recebe um arquivo e retorna um token 
Token* lexico(FILE *file) {
    if(feof(file)) return NULL;                                     // Se o arquivo estiver vazio, retorna NULL  
    hash_table_2d_t *table = create_transition_table();             // Cria a tabela de transição
    //char cadeia[tamanho_cadeia];                                    // Cadeia de caracteres retirada do arquivo
    char buffer[tamanho_cadeia];    // Guarda os caracteres lidos pelo automato finito
    buffer[tamanho_cadeia] = '\0';                                               // Inicializa o buffer
    Token *tk;                                                      // Token a ser retornado
    char state[10] = "q0";                                          // Estado atual do automato finito
    char tempStr[2] = {' ', '\0'};                                  // String temporaria para o caracterer lido
    
    char error = 0;                         // Flag de estado final erro
    char final_state = 0;                   // Flag de estado final

    //fgets(cadeia, tamanho_cadeia, file);    // Le a cadeia de caracteres do arquivo
    // Enquanto nao chegar no final do arquivo ou nao encontrar um estado final, le os caracteres
    for(int i = 0; !(final_state || error ); i++){

        tempStr[0] = fgetc(file);                         // Pega o caractere da cadeia

        // Se chegou no final do arquivo, adiciona um espaço para indicar o fim da cadeia
        if(fgetc(file) == EOF){
        tempStr[0] = ' ';
        }

        strcat(buffer, tempStr);                          // Guarda o caractere lido
        printf("Estado atual: x%sx\n", state);
        printf("find: %s\n", find(table, state, tempStr));
        strcpy(state, find(table, state, tempStr));     // Pega o proximo estado do automato finito
       
        printf("Novo estado: x%sx\n", state);
        printf("Buffer: x%sx\n", buffer);
        printf("Caractere lido: x%sx\n", tempStr);
        printf("i = %d\n", i);
    
        final_state = (strncmp(state, "f", 1) == 0);    // Verifica se o estado atual é final
        error = (strncmp(state, "e", 1) == 0);          // Verifica se o estado atual é de erro
        printf("error: %d\n", error);
        printf("final_state: %d\n", final_state);
    }
    if(error){
        if(strcmp(state, "e1") == 0){
            tk = create_token(buffer, "<ERRO_LEXICO>");
        } else {
            tk = create_token("\n", "<ERRO_COMENTARIO>");
        }
        free_table(table);    
        return tk;
    }
    if(final_state){
        //if()
        tk = create_token(buffer, "<ARGUMETO_VALIDO>");
        free_table(table);    
        return tk;
    }

    // Se chegou aqui significa que a variavel "state" nao e um estado final e terminou de ler o arquivo 
    tk = create_token(buffer, "<ERRO_ARGUMETO_INCOMPLETO>");
    free_table(table);    
    return tk;
}
