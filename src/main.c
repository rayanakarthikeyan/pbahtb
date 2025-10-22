#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hash_table.h"
#include "collision.h"
#include "utils.h"

int main() {
    srand(time(0));
    int table_size = 10;
    int num_keys = 10;
    int collisions;

    int *keys = generate_random_keys(num_keys, 50);
    printf("Generated Keys: ");
    print_array(keys, num_keys);

    HashTable *ht = create_table(table_size);
    for(int i = 0; i < num_keys; i++)
        insert_chaining(ht, keys[i]);
    print_chaining(ht);
    free_table(ht);

    int linear_table[table_size];
    for(int i=0;i<table_size;i++) linear_table[i]=-1;
    collisions=0;
    for(int i = 0; i < num_keys; i++)
        insert_linear(linear_table, table_size, keys[i], &collisions);
    print_linear(linear_table, table_size);
    printf("Linear Collisions: %d\n", collisions);

    int quad_table[table_size];
    for(int i=0;i<table_size;i++) quad_table[i]=-1;
    collisions=0;
    for(int i = 0; i < num_keys; i++)
        insert_quadratic(quad_table, table_size, keys[i], &collisions);
    print_quadratic(quad_table, table_size);
    printf("Quadratic Collisions: %d\n", collisions);

    int double_table[table_size];
    for(int i=0;i<table_size;i++) double_table[i]=-1;
    collisions=0;
    for(int i = 0; i < num_keys; i++)
        insert_double(double_table, table_size, keys[i], &collisions);
    print_double(double_table, table_size);
    printf("Double Hashing Collisions: %d\n", collisions);

    free(keys);
    return 0;
}
