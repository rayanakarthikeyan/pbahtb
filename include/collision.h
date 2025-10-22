#ifndef COLLISION_H
#define COLLISION_H

#include "hash_table.h"

void insert_chaining(HashTable *ht, int key);
void print_chaining(HashTable *ht);
void insert_linear(int table[], int size, int key, int *collisions);
void print_linear(int table[], int size);
void insert_quadratic(int table[], int size, int key, int *collisions);
void print_quadratic(int table[], int size);
int hash2(int key, int size);
void insert_double(int table[], int size, int key, int *collisions);
void print_double(int table[], int size);

#endif
