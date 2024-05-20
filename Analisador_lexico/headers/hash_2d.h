#ifndef HASH_2D_H
#define HASH_2D_H

#define TABLE_SIZE 499

typedef struct node {
    char* key1;
    char* key2;
    char* value;
    struct node* next;
} node_t;

typedef struct {
    node_t*** buckets;
} hash_table_2d_t;

unsigned int hash_function(const char* key);    // Função de hash
hash_table_2d_t* create_table();            // Cria uma tabela hash
void insert(hash_table_2d_t* table, const char* key1, const char* key2, const char* value);   // Insere um valor na tabela
char* find(hash_table_2d_t* table, const char* key1, const char* key2);  // Encontra um valor da tabela
int delete(hash_table_2d_t* table, const char* key1, const char* key2);   // Deleta um valor da tabela
void free_table(hash_table_2d_t* table);   // Libera a memória alocada pela tabela
int count_collisions(hash_table_2d_t* table);  // Conta as colisões na tabela

#endif