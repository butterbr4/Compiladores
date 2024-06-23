#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../headers/sintatico.h"
#include "../headers/hash_2d.h"

// Variaveis globais
FILE *file_out; // Arquivo de saida
FILE *file_in;  // Arquivo de entrada
Token *token;   // Token atual
int erros = 0;  // Contador de erros
hash_table_2d_t *table;  // Tabela de seguidor



// Coloca a tabela de seguidor em uma tabela hash 2d
hash_table_2d_t* create_folower_table(){
    hash_table_2d_t* table = create_table();

    // Insere os valores na tabela hash 2d
    for(int i = 0; folower_table[i][0] != NULL; i++){
        insert(table, folower_table[i][0], folower_table[i][1], folower_table[i][2]);
    }
    return table;
}

// Verifica o tipo do token
int is_tk_type(const char *type){
    return (strcmp(token->tipo, type) == 0);    // Retorna 1 se for do tipo passado, 0 caso contrario
}

// Pega o proximo token e verifica um erro lexico
void next_tk(){
    free_token(token);  // Libera o token atual
    token = lexico(file_in);  // Pega o proximo token
    if(is_tk_type("<ERRO_LEXICO>")){  // Se for um erro lexico
        fprintf(file_out, "Erro léxico na linha %d: %s\n", token->line, token->cadeia);  // Imprime o erro lexico
        erros++;    // Incrementa o contador de erros
    }
    if(is_tk_type("<ERRO_COMENTARIO_NAO_TERMINADO>")){  // Se for um erro de comentario nao terminado
        fprintf(file_out, "Erro léxico na linha %d: comentário não terminado\n", token->line);  // Imprime o erro de comentario nao terminado
        erros++;    // Incrementa o contador de erros
    }
}

// Funcao panico que sicroniza o token
int panic(const char *n_terminal, const char *sinc){       
    printf("token->cadeia: %s\n", token->cadeia);
    printf("n_terminal: %s\n", n_terminal);
    printf("sinc: %s\n", sinc);
    // Enquanto nao encontrar um simbolo de sicronizacao ou o final do arquivo pega o proximo token
    while(((find(table, n_terminal, token->tipo)) == NULL) || (is_tk_type("final"))){ 
        next_tk();  // Pega o proximo token
        printf("token->cadeia: %s\n", token->cadeia);
        if(is_tk_type(sinc)){  // Se encontrar o simbolo de sincronizacao passado
            return 1;  // Retorna 1
        }
    }
    if(is_tk_type("final")){
        fprintf(file_out, "Erro sintático na linha %d: final inesperado\n", token->line);
    }
    return 0;  // Retorna 0 caso outro simbolo de sincronizacao seja encontrado
}


void programa(){
    next_tk();  // Pega o proximo token

    bloco();  // Chama bloco
    printf("token cadeia: %s\n", token->cadeia);
    while(!(is_tk_type("ponto") || (is_tk_type("final")))){
        next_tk();  // Pega o proximo token
        // Se encontrar o final do programa o "." significa que ouve um final inesperado do bloco()
        if(is_tk_type("ponto")){
            fprintf(file_out, "Erro sintático na linha %d: final inesperado\n", token->line);
        }
    }
    if(is_tk_type("ponto") || is_tk_type("final")){  // Se terminar o programa com ponto
        free_token(token);  // Libera o token atual
        token = lexico(file_in);  // Pega o proximo token

        // Erro de argumento fora do programa e de comentario
        while(!(is_tk_type("final"))){  // Enquanto nao chegar no final do arquivo
            if(is_tk_type("<ERRO_COMENTARIO_NAO_TERMINADO>")){
                fprintf(file_out, "Erro léxico na linha %d: comentário não terminado\n", token->line);
            }else{
                fprintf(file_out, "Erro sintático na linha %d: argumento fora do programa\n", token->line);
            }
            erros++;    // Incrementa o contador de erros
            free_token(token);  // Libera o token atual
            token = lexico(file_in);  // Pega o proximo token
        }
        return;
    }
    fprintf(file_out, "Erro sintático na linha %d: ponto final esperado\n", token->line);
    return;
}

void bloco(){
    declaracao(); 
    comando();
}

void declaracao(){
    constante();
    variavel();
    procedimento(); 
}

void constante(){
    if(is_tk_type("CONST")){
        next_tk();  
        if(is_tk_type("id")){
            next_tk(); 
            if(is_tk_type("igual")){
                next_tk();  
                if(is_tk_type("numero")){
                    next_tk();  
                    mais_const( );  
                    if(is_tk_type("ponto_virgula")){
                        return;
                    } else {
                        fprintf(file_out, "Erro sintático na linha %d: ponto e vírgula esperado\n", token->line);
                        return;
                    }
                } else {
                    erros++;
                    panic("constante", "");
                    fprintf(file_out, "Erro sintático na linha %d: número esperado\n", token->line);
                }
            } else {
                erros++;
                panic("constante", "");
                fprintf(file_out, "Erro sintático na linha %d: sinal de igual esperado\n", token->line);
            }
        } else {
            erros++;
            if(panic("constante", "id")){
                // Se encontrar um identificador como simbolo de sincronizacao significa que ouve um token inesperado
                fprintf(file_out, "Erro sintático na linha %d: token inesperado\n", token->line);
                return;
            }
            // Se nao encontrar um identificador como simbolo de sincronizacao, erro
            fprintf(file_out, "Erro sintático na linha %d: identificador esperado\n", token->line);
        }
    }
    return;
}

void variavel(){
    if(is_tk_type("VAR")){
        next_tk();  
        if(is_tk_type("id")){
            next_tk();  
            mais_var(); 
            if(is_tk_type("ponto_virgula")){
                next_tk(); 
                return;
            } else {
                erros++;
                if(panic("variavel", "ponto_virgula")){
                    // Se encontrar um ponto e virgula como simbolo de sincronizacao significa que ouve um token inesperado
                    fprintf(file_out, "Erro sintático na linha %d: token inesperado\n", token->line);
                    // Esse ponto e virgula encontrado pode ser o final de variavel portanto escolheu-se pegar o proximo token
                    next_tk();
                    return;
                }
                // Se nao encontrar um ponto e virgula como simbolo de sincronizacao, erro
                fprintf(file_out, "Erro sintático na linha %d: ponto e virgula esperado\n", token->line);
                return;
            }
        }else{
            erros++;
            if(panic("variavel", "id")){
                // Se encontrar um identificador como simbolo de sincronizacao significa que ouve um token inesperado
                fprintf(file_out, "Erro sintático na linha %d: token inesperado\n", token->line);
                return;
            }
            fprintf(file_out, "Erro sintático na linha %d: identificador esperado\n", token->line);
        }
    }
    return;
}

void procedimento(){
    if(is_tk_type("PROCEDURE")){
        next_tk();  
        if(is_tk_type("id")){
            next_tk();
            if(is_tk_type("ponto_virgula")){
                next_tk();
                bloco();  
                if(is_tk_type("ponto_virgula")){
                    next_tk(); 
                    procedimento();  // Recursao
                    return;
                } else {
                    fprintf(file_out, "Erro sintático na linha %d: ponto e vírgula esperado\n", token->line);
                    return;
                }
            } else {
                fprintf(file_out, "Erro sintático na linha %d: ponto e vírgula esperado\n", token->line);
                return;
            }
        } else {
            fprintf(file_out, "Erro sintático na linha %d: identificador esperado\n", token->line);
            return;
        }
        return;
    }
    return;
}

void comando(){
    if(is_tk_type("id")){
        next_tk(); 
        if(is_tk_type("atribuicao")){
            next_tk();
            expressao();
            return;
        }else{
            fprintf(file_out, "Erro sintático na linha %d: dois pontos e igual esperado\n", token->line);
            return;
        }
    }
    if(is_tk_type("CALL")){
        next_tk();  
        if(is_tk_type("id")){
            next_tk();
            return;
        } else {
            fprintf(file_out, "Erro sintático na linha %d: identificador esperado\n", token->line);
            return;
        }
    }
    if(is_tk_type("IF")){
        next_tk();  
        condicao(); 
        if(is_tk_type("THEN")){
            next_tk();  
            comando();  // Recursao
            return;
        } else {
            fprintf(file_out, "Erro sintático na linha %d: ""THEN"" esperado\n", token->line);
            return;
        }
    }
    if(is_tk_type("WHILE")){
        next_tk();  
        condicao(); 
        if(is_tk_type("DO")){
            next_tk();
            comando();  // Recursao
            return;
        } else {
            fprintf(file_out, "Erro sintático na linha %d: ""DO"" esperado\n", token->line);
            return;
        }
    }
    if(is_tk_type("BEGIN")){
        next_tk();
        comando();  // Recursao
        mais_cmd();  
        if(is_tk_type("END")){
            next_tk();
            return;
        } else {
            fprintf(file_out, "Erro sintático na linha %d: ""END"" esperado\n", token->line);
            return;
        }
    }
    return;
}

void expressao(){
    operador_unario();
    termo();  
    mais_termos();  
}

void mais_cmd(){
    if(is_tk_type("ponto_virgula")){
        next_tk(); 
        comando(); 
        mais_cmd();  // Recursao
    }
    return;
}

void mais_termos(){
    if(is_tk_type("sub") || is_tk_type("suma")){
        next_tk();
        termo();
        mais_termos();  // Recursao
    }
    return;
}

void mais_const(){
    if(is_tk_type("virgula")){
        next_tk();
        if(is_tk_type("id")){
            next_tk();
            if(is_tk_type("igual")){
                next_tk();
                if(is_tk_type("numero")){
                    next_tk();
                    mais_const();  // Recursao
                } else {
                    fprintf(file_out, "Erro sintático na linha %d: numero esperado\n", token->line);
                    return;
                }
            } else {
                fprintf(file_out, "Erro sintático na linha %d: sinal de igual esperado\n", token->line);
                return;
            }
        } else {
            fprintf(file_out, "Erro sintático na linha %d: identificador esperado\n", token->line);
            return;
        }
    }
    return;
}

void mais_var(){
    if(is_tk_type("virgula")){
        next_tk();
        if(is_tk_type("id")){
            next_tk();
            mais_var();  // Recursao
        } else {
            fprintf(file_out, "Erro sintático na linha %d: identificador esperado\n", token->line);
        }
    }
    return;
}

void termo(){
    fator();
    mais_fatores();
}

void mais_fatores(){
    if(is_tk_type("mult") || is_tk_type("div")){
        next_tk();
        fator();
        mais_fatores();  // Recursao
    }
    return;
}

void fator(){
    if(is_tk_type("id")){
        next_tk();
        return;
    }
    if(is_tk_type("numero")){
        next_tk();
        return;
    }
    if(is_tk_type("abre_parenteses")){
        next_tk();
        expressao();
        if(is_tk_type("fecha_parenteses")){
            next_tk();
            return;
        }else{
            fprintf(file_out, "Erro sintático na linha %d: fecha parenteses esperado\n", token->line);
            return;
        }
    }else{
        fprintf(file_out, "Erro sintático na linha %d: identificador, número ou abre parenteses esperado\n", token->line);
        return;
    }

    // Caso nao encotre nenhum dos casos acima, erro
    fprintf(file_out, "Erro sintático na linha %d: identificador, numero ou abre parenteses esperado\n", token->line);
}

void operador_unario(){
    if(is_tk_type("mais")){
        next_tk();
        return;
    }
    if(is_tk_type("sub")){
        next_tk();
        return;
    }
    return;
}

void condicao(){
    if(is_tk_type("ODD")){
        next_tk();
        expressao();
        return;
    }
    expressao();
    relacional();
    expressao();
}

void relacional(){
    if(is_tk_type("igual")){
        next_tk();
        return;
    }
    if(is_tk_type("diferente")){
        next_tk();
        return;
    }
    if(is_tk_type("menor_igual")){
        next_tk();
        return;
    }
    if(is_tk_type("menor")){
        next_tk();
        return;
    }
    if(is_tk_type("maior_igual")){
        next_tk();
        return;
    }
    if(is_tk_type("maior")){
        next_tk();
        return;
    }

    // Caso nao encontre nenhum dos casos acima, erro
    fprintf(file_out, "Erro sintático na linha %d: operador relacional esperado\n", token->line);
}



// Funcao que verifica a sintaxe do codigo e retorna 1 se nao houver erros, 0 caso contrario
int sintatico(FILE *in, FILE *out){
    file_in = in;  // Arquivo de entrada
    file_out = out;  // Arquivo de saida
    table = create_folower_table();  // Cria a tabela de seguidor apenas uma vez

    programa();  // Chama programa

    free_token(token);  // Libera o token
    free_table(table);  // Libera a tabela de seguidor
    if(erros == 0){  // Se nao houver erros sintaticos na compilacao
        return 1;
    } else {
        return 0;
    }
}