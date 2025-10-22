#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#define MAX_SIZE 100

typedef struct HashNode {
    int key;
    struct HashNode *next;
} HashNode;

typedef struct HashTable {
    HashNode **table;
    int size;
    int count;
} HashTable;

HashTable* create_table(int size);
void free_table(HashTable *ht);
int hash_function(int key, int size);
#endif
