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




// Retorna 1 se for uma palavra reservada, 0 caso contrario
int is_keyword(const char *str) {
    const char *keywords[] = {"CONST", "VAR", "PROCEDURE", "CALL", "BEGIN", "END", "IF", "THEN", "WHILE", "DO", "ODD", NULL};

    for (int i = 0; keywords[i] != NULL; i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return 1; // Verdadeiro, a string é uma das palavras-chave
        }
    }
    return 0; // Falso, a string não é uma das palavras-chave
}




// Esta funcao recebe um arquivo e retorna um token 
Token* lexico(FILE *file) {
    if(feof(file)) return NULL;                                     // Se chegou no final do arquivo, retorna NULL 
    hash_table_2d_t *table = create_transition_table();             // Cria a tabela de transição
    
    char *buffer = calloc(tamanho_cadeia + 1, sizeof(char));        // Guarda os caracteres lidos pelo automato finito
    Token *tk;                                                      // Token a ser retornado
    char state[10] = "q0";                                          // Estado atual do automato finito
    char tempStr[] = {' ', '\0'};                                   // String temporaria para o caracterer lido
    
    char error = 0;                         // Flag de estado final erro
    char final_state = 0;                   // Flag de estado final
    
    // Enquanto nao chegar no final do arquivo ou nao encontrar um estado final ou de erro, le os caracteres
    for(int i = 0; !(final_state || error || feof(file)) && (i < tamanho_cadeia); i++){
        // Pega o caractere do arquivo
        tempStr[0] = fgetc(file);  
        
        // Se chegou no final do arquivo, adiciona um espaço para indicar o fim do arquivo
        if(feof(file)){
            tempStr[0] = ' ';
        } 
        

        printf("Caractere lido: x%sx\n", tempStr);

        printf("Estado atual: x%sx\n", state);
        printf("find: %s\n", find(table, state, tempStr));
        strcpy(state, find(table, state, tempStr));     // Pega o proximo estado do automato finito
        
        // Se o estado atual for q0, f1, f2, e2, f10, f12 desconsidera o caractere lido
        if(strcmp(state, "q0") && strcmp(state, "f1") && strcmp(state, "f2") && strcmp(state, "e2") && strcmp(state, "f10") && strcmp(state, "f12"))
            strcat(buffer, tempStr);                    // Adiona o caractere lido ao buffer
        else
            printf("Desconsiderando: x%sx\n", tempStr);
        printf("Novo estado: x%sx\n", state);
        printf("Buffer: x%sx\n", buffer);
        printf("i = %d\n", i);
    
        final_state = (strncmp(state, "f", 1) == 0);    // Verifica se o estado atual é final
        error = (strncmp(state, "e", 1) == 0);          // Verifica se o estado atual é de erro
        printf("error: %d\n", error);
        printf("final_state: %d\n\n", final_state);

    }
    
    if(error){
        if(strcmp(state, "e1") == 0){
            tk = create_token(buffer, "<ERRO_LEXICO>");
        } else {
            tk = create_token("\\n", "<ERRO_COMENTARIO>");
        }
        free_table(table);    
        free(buffer); 
        return tk;
    }
    if(final_state){
        if(strcmp(state, "f1") == 0){
            if(is_keyword(buffer)){ // Se for uma palavra reservada o token é "keyword" senão é "id"
                tk = create_token(buffer, buffer);
            }else
                tk = create_token(buffer, "id");
            if(!feof(file)) ungetc(tempStr[0],file); // Devolve o ultimo caractere lido para o arquivo
        }else if(strcmp(state, "f2") == 0){
            if(!feof(file)) ungetc(tempStr[0],file); // Devolve o ultimo caractere lido para o arquivo
            tk = create_token(buffer, "numero");
        }else if(strcmp(state, "f3") == 0){
            tk = create_token(buffer, "soma");
        }else if(strcmp(state, "f4") == 0){
            tk = create_token(buffer, "sub");
        }else if(strcmp(state, "f5") == 0){
            tk = create_token(buffer, "mult");
        }else if(strcmp(state, "f6") == 0){
            tk = create_token(buffer, "div");
        }else if(strcmp(state, "f7") == 0){
            tk = create_token(buffer, "igual");
        }else if(strcmp(state, "f8") == 0){
            tk = create_token(buffer, "diferente");
        }else if(strcmp(state, "f9") == 0){
            tk = create_token(buffer, "menor_igual");
        }else if(strcmp(state, "f10") == 0){
            tk = create_token(buffer, "menor");
            if(!feof(file)) ungetc(tempStr[0],file); // Devolve o ultimo caractere lido para o arquivo
        }else if(strcmp(state, "f11") == 0){
            tk = create_token(buffer, "maior_igual");
        }else if(strcmp(state, "f12") == 0){
            tk = create_token(buffer, "maior");
            if(!feof(file)) ungetc(tempStr[0],file); // Devolve o ultimo caractere lido para o arquivo
        }else if(strcmp(state, "f13") == 0){
            tk = create_token(buffer, "atribuicao");
        }else if(strcmp(state, "f14") == 0){
            tk = create_token(buffer, "ponto_virgula");
        }else if(strcmp(state, "f15") == 0){
            tk = create_token(buffer, "ponto");
        }else if(strcmp(state, "f16") == 0){
            tk = create_token(buffer, "abre_parenteses");
        }else if(strcmp(state, "f17") == 0){
            tk = create_token(buffer, "fecha_parenteses");
        }else if(strcmp(state, "f18") == 0){
            tk = create_token(buffer, "comentario");
        }else if(strcmp(state, "f19") == 0){
            tk = create_token(buffer, "virgula");
        }
    
        free_table(table);  
        free(buffer);   
        return tk;
    }

    // Terminou de ler o arquivo mas ele pode nao estar em um estado final
    printf("Terminou de ler o arquivo\n");
    if(strcmp(state, "q0") == 0){   // Se o estado atual for q0, retorna NULL
        free_table(table);  
        free(buffer);  
        return NULL;
    }

    // Se nao estiver em um estado final, retorna um erro lexico
    tk = create_token(buffer, "<ERRO_LEXICO>");
    free_table(table);  
    free(buffer);  
    return tk;
}