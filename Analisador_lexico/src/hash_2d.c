#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/hash_2d.h"

// Função de hash
unsigned int hash_function(const char* key) {
    unsigned long int value = 0;
    unsigned int key_len = strlen(key);

    // Percorrer cada caractere da chave e calcular o valor hash
    for (unsigned int i = 0; i < key_len; ++i) {
        value = value * 37 + key[i];    
    }
    return value % TABLE_SIZE;  
}


// Função para criar uma tabela hash 2D
hash_table_2d_t* create_table() {
    hash_table_2d_t* table = malloc(sizeof(hash_table_2d_t));
    table->buckets = malloc(sizeof(node_t**) * TABLE_SIZE);

    for (int i = 0; i < TABLE_SIZE; i++) {
        table->buckets[i] = malloc(sizeof(node_t*) * TABLE_SIZE);
        for (int j = 0; j < TABLE_SIZE; j++) {
            table->buckets[i][j] = NULL;
        }
    }

    return table;
}

// Função para inserir um valor na tabela
void insert(hash_table_2d_t* table, const char* key1, const char* key2, const char* value) {
    unsigned int index1 = hash_function(key1);
    unsigned int index2 = hash_function(key2);
    node_t* new_node = malloc(sizeof(node_t));
    new_node->key1 = strdup(key1);
    new_node->key2 = strdup(key2);
    new_node->value = strdup(value);
    new_node->next = table->buckets[index1][index2];
    table->buckets[index1][index2] = new_node;
}

// Função que encontra um valor da tabela
char* find(hash_table_2d_t* table, const char* key1, const char* key2) {
    unsigned int index1 = hash_function(key1);
    unsigned int index2 = hash_function(key2);
    node_t* node = table->buckets[index1][index2];  // Obter o primeiro nó do "bucket"

    // Percorrer a lista encadeada para encontrar o valor
    while (node) {
        if (strcmp(node->key1, key1) == 0 && strcmp(node->key2, key2) == 0) {
            return node->value;
        }
        node = node->next;  
    }

    // Essa parte tem como papel simular o comportamento da transicao pelo caracter "outros"
    if((strcmp(key1, "q1")) == 0){  // Se o estado atual for q1 e o simbolo for "outros" vai para o estado f1
        return "f1";
    }
    if(strcmp(key1, "q2") == 0){    // Se o estado atual for q2 e o simbolo for "outros" vai para o estado f2
        return "f2";
    }
    if(strcmp(key1, "q3") == 0){    // Se o estado atual for q3 e o simbolo for "outros" vai para o estado f10
        return "f10";
    }
    if((strcmp(key1, "q4")) == 0){  // Se o estado atual for q4 e o simbolo for "outros" vai para o estado f12
        return "f12";
    }
    if((strcmp(key1, "q0") == 0) || (strcmp(key1, "q5") == 0)){ // Se o estado atual for q0 ou q5 e o simbolo for "outros" vai para o estado e1
        return "e1";
    }
    if((strcmp(key1, "q6")) == 0){  // Se o estado atual for q6 e o simbolo for "outros" vai para o estado q6
        return "q6";
    }
    return NULL;
}

// Função para contar as colisões em toda a tabela hash
int count_collisions(hash_table_2d_t* table) {
    int total_collisions = 0;

    // Percorrer cada "bucket" ou slot da tabela hash 2D
    for (int i = 0; i < TABLE_SIZE; i++) {
        for (int j = 0; j < TABLE_SIZE; j++) {
            node_t* current_node = table->buckets[i][j];
            int bucket_collision_count = 0;

            // Contar os nós na lista encadeada
            while (current_node != NULL && current_node->next != NULL) {
                bucket_collision_count++;
                current_node = current_node->next;
            }

            if (bucket_collision_count > 0) {
                // Somente incrementar total de colisões se mais de um elemento estiver presente no bucket
                total_collisions += bucket_collision_count;
            }
        }
    }
    return total_collisions;
}

// Função para deletar um valor da tabela
int delete(hash_table_2d_t* table, const char* key1, const char* key2) {
    unsigned int index1 = hash_function(key1);
    unsigned int index2 = hash_function(key2);
    node_t** node = &(table->buckets[index1][index2]);

    while (*node) {
        if (strcmp((*node)->key1, key1) == 0 && strcmp((*node)->key2, key2) == 0) {
            node_t* temp = *node;
            *node = (*node)->next;
            free(temp->key1);
            free(temp->key2);
            free(temp->value);
            free(temp);
            return 1;
        }
        node = &((*node)->next);
    }

    return 0;
}

// Função para liberar a memória alocada para a tabela hash
void free_table(hash_table_2d_t* table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        for (int j = 0; j < TABLE_SIZE; j++) {
            node_t* node = table->buckets[i][j];
            while (node) {
                node_t* temp = node;
                node = node->next;
                free(temp->key1);
                free(temp->key2);
                free(temp->value);
                free(temp);
            }
        }
        free(table->buckets[i]);
    }
    free(table->buckets);
    free(table);
}