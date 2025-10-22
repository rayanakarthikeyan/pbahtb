#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 50  // default table size
#define MAX_KEY_COUNT 200

typedef struct Node {
    int key;
    struct Node* next;
} Node;

// Hash Functions
int hash1(int key) {
    return key % TABLE_SIZE;
}

int hash2(int key) {
    return 7 - (key % 7);
}

// Global counters
int collisionCount = 0;
int totalInserts = 0;

// Create new node
Node* createNode(int key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->next = NULL;
    return newNode;
}

// -------------------- SEPARATE CHAINING --------------------
void insertChaining(Node* table[], int key) {
    int index = hash1(key);
    Node* newNode = createNode(key);

    if (table[index] == NULL)
        table[index] = newNode;
    else {
        collisionCount++;
        newNode->next = table[index];
        table[index] = newNode;
    }
}

// -------------------- LINEAR PROBING --------------------
void insertLinear(int table[], int key) {
    int index = hash1(key);
    int i = 0;

    while (table[(index + i) % TABLE_SIZE] != -1) {
        collisionCount++;
        i++;
        if (i == TABLE_SIZE) return;
    }
    table[(index + i) % TABLE_SIZE] = key;
}

// -------------------- QUADRATIC PROBING --------------------
void insertQuadratic(int table[], int key) {
    int index = hash1(key);
    int i = 0;

    while (table[(index + i * i) % TABLE_SIZE] != -1) {
        collisionCount++;
        i++;
        if (i == TABLE_SIZE) return;
    }
    table[(index + i * i) % TABLE_SIZE] = key;
}

// -------------------- DOUBLE HASHING --------------------
void insertDoubleHash(int table[], int key) {
    int index = hash1(key);
    int step = hash2(key);
    int i = 0;

    while (table[(index + i * step) % TABLE_SIZE] != -1) {
        collisionCount++;
        i++;
        if (i == TABLE_SIZE) return;
    }
    table[(index + i * step) % TABLE_SIZE] = key;
}

// -------------------- DRIVER --------------------
int main(int argc, char* argv[]) {
    if (argc < 4) {
        printf("Usage: %s <Technique> <InputFile> <LoadFactor>\n", argv[0]);
        return 1;
    }

    char* technique = argv[1];
    char* fileName = argv[2];
    double loadFactor = atof(argv[3]);

    FILE* file = fopen(fileName, "r");
    if (!file) {
        printf("Error: Cannot open input file.\n");
        return 1;
    }

    int keys[MAX_KEY_COUNT];
    int keyCount = 0;

    while (fscanf(file, "%d", &keys[keyCount]) != EOF && keyCount < MAX_KEY_COUNT)
        keyCount++;
    fclose(file);

    int insertCount = (int)(TABLE_SIZE * loadFactor);
    if (insertCount > keyCount) insertCount = keyCount;

    if (strcmp(technique, "Separate_Chaining") == 0) {
        Node* table[TABLE_SIZE] = {NULL};
        for (int i = 0; i < insertCount; i++) {
            insertChaining(table, keys[i]);
            totalInserts++;
        }
    } 
    else {
        int table[TABLE_SIZE];
        for (int i = 0; i < TABLE_SIZE; i++) table[i] = -1;

        for (int i = 0; i < insertCount; i++) {
            if (strcmp(technique, "Linear_Probing") == 0)
                insertLinear(table, keys[i]);
            else if (strcmp(technique, "Quadratic_Probing") == 0)
                insertQuadratic(table, keys[i]);
            else if (strcmp(technique, "Double_Hashing") == 0)
                insertDoubleHash(table, keys[i]);
            totalInserts++;
        }
    }

    printf("Technique: %s\n", technique);
    printf("Load Factor: %.2f\n", loadFactor);
    printf("Total Inserts: %d\n", totalInserts);
    printf("Collisions: %d\n", collisionCount);
    return 0;
}
