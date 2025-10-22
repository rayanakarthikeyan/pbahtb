#include "utils.h"

int* generate_random_keys(int n, int max_val) {
    int *arr = (int*)malloc(sizeof(int) * n);
    for(int i = 0; i < n; i++)
        arr[i] = rand() % max_val;
    return arr;
}

void print_array(int arr[], int n) {
    for(int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}
