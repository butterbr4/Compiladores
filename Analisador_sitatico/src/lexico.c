#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../headers/lexico.h"
#include "../headers/hash_2d.h"

// Cria um token
Token* create_token(char *cadeia, char *tipo, unsigned int linha){
    Token *tk = malloc(sizeof(Token));
    tk->cadeia = strdup(cadeia);    // Copia a cadeia para o token
    tk->tipo = strdup(tipo);        // Copia o tipo para o token
    tk->line = linha;              // Copia a linha para o token
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
    static hash_table_2d_t *table = NULL;   // Static para manter a tabela toda vez que a funcao for chamada
    if (!table) {
        table = create_transition_table();  // Cria a tabela de transição apenas uma vez
    }

    static unsigned int line = 1;          // Contador de linhas
    
    if(feof(file)){
        free_table(table);
        return (create_token("", "final", line));  // Token de final de arquivo
    }

    char *buffer = calloc(tamanho_cadeia + 1, sizeof(char));        // Guarda os caracteres lidos pelo automato finito
    Token *tk = NULL;                                                      // Token a ser retornado
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
        
        strcpy(state, find(table, state, tempStr));     // Pega o proximo estado do automato finito

        // Se o estado atual for f1, f2, e2, f10, f12 nao adiciona o caractere lido ao buffer
        if(strcmp(state, "f1") && strcmp(state, "f2") && strcmp(state, "e2") && strcmp(state, "f10") && strcmp(state, "f12")){
            // Se o caractere lido for um \n, incrementa o contador de linhas
            if(tempStr[0] == '\n'){
                line++;
            }
            strcat(buffer, tempStr);        // Adiona o caractere lido ao buffer
        }

        // Se o estado atual for q0, zera o contador de caracteres lidos e limpa o buffer
        if(strcmp(state, "q0") == 0){
            i = 0;  // Se o estado atual for q0, zera o contador de caracteres lidos
            for(int j = 0; j <= tamanho_cadeia; j++) buffer[j] = '\0'; // Limpa o buffer
        }

        final_state = (strncmp(state, "f", 1) == 0);    // Verifica se o estado atual é final
        error = (strncmp(state, "e", 1) == 0);          // Verifica se o estado atual é de erro
    }
    
    if(error){  // Se o estado atual for de erro, retorna um erro lexico ou de comentario
        if(strcmp(state, "e1") == 0){
            tk = create_token(buffer, "<ERRO_LEXICO>", line);
        } else {
            tk = create_token(buffer, "<ERRO_COMENTARIO_NAO_TERMINADO>", line);
            if(!feof(file)) ungetc(tempStr[0],file); // Devolve o ultimo caractere lido para o arquivo
        }
    
        free(buffer); 
        return tk;
    }

    if(final_state){    // Se o estado atual for final, cria o token correspondente
        if(strcmp(state, "f1") == 0){
            if(is_keyword(buffer)){ // Se for uma palavra reservada o token é "keyword" senão é "id"
                tk = create_token(buffer, buffer, line);
            }else
                tk = create_token(buffer, "id", line);
            if(!feof(file)) ungetc(tempStr[0],file); // Devolve o ultimo caractere lido para o arquivo
        }else if(strcmp(state, "f2") == 0){
            if(!feof(file)) ungetc(tempStr[0],file); // Devolve o ultimo caractere lido para o arquivo
            tk = create_token(buffer, "numero", line);
        }else if(strcmp(state, "f3") == 0){
            tk = create_token(buffer, "soma", line);
        }else if(strcmp(state, "f4") == 0){
            tk = create_token(buffer, "sub", line);
        }else if(strcmp(state, "f5") == 0){
            tk = create_token(buffer, "mult", line);
        }else if(strcmp(state, "f6") == 0){
            tk = create_token(buffer, "div", line);
        }else if(strcmp(state, "f7") == 0){
            tk = create_token(buffer, "igual", line);
        }else if(strcmp(state, "f8") == 0){
            tk = create_token(buffer, "diferente", line);
        }else if(strcmp(state, "f9") == 0){
            tk = create_token(buffer, "menor_igual", line);
        }else if(strcmp(state, "f10") == 0){
            tk = create_token(buffer, "menor", line);
            if(!feof(file)) ungetc(tempStr[0],file); // Devolve o ultimo caractere lido para o arquivo
        }else if(strcmp(state, "f11") == 0){
            tk = create_token(buffer, "maior_igual", line);
        }else if(strcmp(state, "f12") == 0){
            tk = create_token(buffer, "maior", line);
            if(!feof(file)) ungetc(tempStr[0],file); // Devolve o ultimo caractere lido para o arquivo
        }else if(strcmp(state, "f13") == 0){
            tk = create_token(buffer, "atribuicao", line);
        }else if(strcmp(state, "f14") == 0){
            tk = create_token(buffer, "ponto_virgula", line);
        }else if(strcmp(state, "f15") == 0){
            tk = create_token(buffer, "ponto", line);
        }else if(strcmp(state, "f16") == 0){
            tk = create_token(buffer, "abre_parenteses", line);
        }else if(strcmp(state, "f17") == 0){
            tk = create_token(buffer, "fecha_parenteses", line);
        }else if(strcmp(state, "f19") == 0){
            tk = create_token(buffer, "virgula", line);
        }
  
        free(buffer);   
        return tk;
    }

    // Terminou de ler o arquivo mas ele pode nao estar em um estado final
    if(strcmp(state, "q0") == 0){   // Se o estado atual for q0, retorna NULL pois só leu espaços em branco
        tk = create_token("", "final", line);  // Token de final de arquivo
        free_table(table);
        free(buffer);  
        return tk;
    }

    // Se nao estiver em um estado final, retorna um erro lexico
    tk = create_token(buffer, "<ERRO_LEXICO>", line);  
    free(buffer);  
    return tk;
}