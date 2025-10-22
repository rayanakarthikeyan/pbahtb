#include "collision.h"
#include <stdio.h>
#include <stdlib.h>

void insert_chaining(HashTable *ht, int key) {
    int index = hash_function(key, ht->size);
    HashNode *node = (HashNode*)malloc(sizeof(HashNode));
    node->key = key;
    node->next = ht->table[index];
    ht->table[index] = node;
    ht->count++;
}

void print_chaining(HashTable *ht) {
    printf("\n--- Chaining Hash Table ---\n");
    for(int i = 0; i < ht->size; i++) {
        printf("%d: ", i);
        HashNode *node = ht->table[i];
        while(node) {
            printf("%d -> ", node->key);
            node = node->next;
        }
        printf("NULL\n");
    }
}

void insert_linear(int table[], int size, int key, int *collisions) {
    int index = key % size;
    int i = 0;
    while(table[(index + i) % size] != -1) {
        i++;
        (*collisions)++;
    }
    table[(index + i) % size] = key;
}

void print_linear(int table[], int size) {
    printf("\n--- Linear Probing Table ---\n");
    for(int i = 0; i < size; i++)
        printf("%d: %d\n", i, table[i]);
}

void insert_quadratic(int table[], int size, int key, int *collisions) {
    int index = key % size;
    int i = 0;
    while(table[(index + i*i) % size] != -1) {
        i++;
        (*collisions)++;
    }
    table[(index + i*i) % size] = key;
}

void print_quadratic(int table[], int size) {
    printf("\n--- Quadratic Probing Table ---\n");
    for(int i = 0; i < size; i++)
        printf("%d: %d\n", i, table[i]);
}

int hash2(int key, int size) {
    return 1 + (key % (size - 1));
}

void insert_double(int table[], int size, int key, int *collisions) {
    int index = key % size;
    int step = hash2(key, size);
    int i = 0;
    while(table[(index + i*step) % size] != -1) {
        i++;
        (*collisions)++;
    }
    table[(index + i*step) % size] = key;
}

void print_double(int table[], int size) {
    printf("\n--- Double Hashing Table ---\n");
    for(int i = 0; i < size; i++)
        printf("%d: %d\n", i, table[i]);
}
