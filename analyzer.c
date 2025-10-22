#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define TABLE_SIZE 100
#define MAX_KEY_LEN 50

// Node structure for Separate Chaining
typedef struct Node {
    char key[MAX_KEY_LEN];
    struct Node *next;
} Node;

// Hash function
unsigned int hashFunction(const char *key) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash * 31 + *key++) % TABLE_SIZE;
    }
    return hash;
}

// ------------------- LINEAR PROBING -------------------
int linearProbingInsert(char keys[][MAX_KEY_LEN], int n, double loadFactor) {
    int size = (int)(n / loadFactor);
    if (size <= 0) size = 1;

    char **table = (char **)calloc(size, sizeof(char *));
    if (!table) {
        printf("Memory allocation failed!\n");
        return -1;
    }

    int collisions = 0;

    for (int i = 0; i < n; i++) {
        unsigned int index = hashFunction(keys[i]) % size;
        while (table[index] != NULL) {
            collisions++;
            index = (index + 1) % size;
        }
        table[index] = strdup(keys[i]);
    }

    for (int i = 0; i < size; i++) {
        free(table[i]);
    }
    free(table);

    return collisions;
}

// ------------------- QUADRATIC PROBING -------------------
int quadraticProbingInsert(char keys[][MAX_KEY_LEN], int n, double loadFactor) {
    int size = (int)(n / loadFactor);
    if (size <= 0) size = 1;

    char **table = (char **)calloc(size, sizeof(char *));
    if (!table) {
        printf("Memory allocation failed!\n");
        return -1;
    }

    int collisions = 0;

    for (int i = 0; i < n; i++) {
        unsigned int index = hashFunction(keys[i]) % size;
        int j = 0;
        while (table[(index + j * j) % size] != NULL) {
            collisions++;
            j++;
            if (j >= size) break;
        }
        table[(index + j * j) % size] = strdup(keys[i]);
    }

    for (int i = 0; i < size; i++) {
        free(table[i]);
    }
    free(table);

    return collisions;
}

// ------------------- SEPARATE CHAINING -------------------
int separateChainingInsert(char keys[][MAX_KEY_LEN], int n, double loadFactor) {
    int size = (int)(n / loadFactor);
    if (size <= 0) size = 1;

    Node **table = (Node **)calloc(size, sizeof(Node *));
    if (!table) {
        printf("Memory allocation failed!\n");
        return -1;
    }

    int collisions = 0;

    for (int i = 0; i < n; i++) {
        unsigned int index = hashFunction(keys[i]) % size;
        if (table[index] != NULL)
            collisions++;

        Node *newNode = (Node *)malloc(sizeof(Node));
        if (!newNode) {
            printf("Memory allocation failed!\n");
            return -1;
        }
        strcpy(newNode->key, keys[i]);
        newNode->next = table[index];
        table[index] = newNode;
    }

    // Free memory
    for (int i = 0; i < size; i++) {
        Node *temp = table[i];
        while (temp) {
            Node *del = temp;
            temp = temp->next;
            free(del);
        }
    }
    free(table);
    return collisions;
}

// ------------------- MAIN ANALYZER -------------------
int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("Usage: %s <Technique> <InputFile> <LoadFactor>\n", argv[0]);
        printf("Techniques: Linear_Probing | Quadratic_Probing | Separate_Chaining\n");
        return 1;
    }

    char *technique = argv[1];
    char *filePath = argv[2];
    double loadFactor = atof(argv[3]);

    FILE *file = fopen(filePath, "r");
    if (!file) {
        printf("Error: Cannot open input file %s\n", filePath);
        return 1;
    }

    char keys[1000][MAX_KEY_LEN];
    int count = 0;

    while (fscanf(file, "%s", keys[count]) != EOF && count < 1000) {
        count++;
    }
    fclose(file);

    if (count == 0) {
        printf("Error: Input file is empty.\n");
        return 1;
    }

    int collisions = 0;

    if (strcmp(technique, "Linear_Probing") == 0) {
        collisions = linearProbingInsert(keys, count, loadFactor);
    } else if (strcmp(technique, "Quadratic_Probing") == 0) {
        collisions = quadraticProbingInsert(keys, count, loadFactor);
    } else if (strcmp(technique, "Separate_Chaining") == 0) {
        collisions = separateChainingInsert(keys, count, loadFactor);
    } else {
        printf("Invalid Technique: %s\n", technique);
        return 1;
    }

    if (collisions >= 0) {
        printf("Technique: %s\n", technique);
        printf("Load Factor: %.2f\n", loadFactor);
        printf("Total Inserts: %d\n", count);
        printf("Collisions: %d\n", collisions);
    }

    return 0;
}
