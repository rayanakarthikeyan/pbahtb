#include "hash_table.h"
#include <stdlib.h>

HashTable* create_table(int size) {
    HashTable *ht = (HashTable*)malloc(sizeof(HashTable));
    ht->size = size;
    ht->count = 0;
    ht->table = (HashNode**)malloc(sizeof(HashNode*) * size);
    for(int i = 0; i < size; i++)
        ht->table[i] = NULL;
    return ht;
}

void free_table(HashTable *ht) {
    for(int i = 0; i < ht->size; i++) {
        HashNode *node = ht->table[i];
        while(node) {
            HashNode *temp = node;
            node = node->next;
            free(temp);
        }
    }
    free(ht->table);
    free(ht);
}

int hash_function(int key, int size) {
    return key % size;
}
