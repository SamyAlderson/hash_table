#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 1000
#define MAX_KEY_LEN 1024

typedef struct {
    char *key;
    char *value;
} entry_t;

typedef struct {
    entry_t *entries;
    int size;
} table_t;

table_t *table_init(void) {
    table_t *table = malloc(sizeof(table_t));
    table->entries = malloc(TABLE_SIZE * sizeof(entry_t));
    table->size = 0;
    return table;
}

int hash_function(const char *key) {
    int hash = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        hash = (hash * 31 + key[i]) % TABLE_SIZE;
    }
    return hash;
}

int insert(table_t *table, const char *key, const char *value) {
    int index = hash_function(key);
    for (int i = 0; i < TABLE_SIZE; i++) {
        int j = (index + i) % TABLE_SIZE;
        if (table->entries[j].key == NULL) {
            table->entries[j].key = strdup(key);
            table->entries[j].value = strdup(value);
            table->size++;
            return 0;
        }
    }
    printf("Error: Table is full.\n");
    return -1;
}

void *lookup(table_t *table, const char *key) {
    int index = hash_function(key);
    for (int i = 0; i < TABLE_SIZE; i++) {
        int j = (index + i) % TABLE_SIZE;
        if (table->entries[j].key != NULL && strcmp(table->entries[j].key, key) == 0) {
            return strdup(table->entries[j].value);
        }
    }
    return NULL;
}

void remove(table_t *table, const char *key) {
    int index = hash_function(key);
    for (int i = 0; i < TABLE_SIZE; i++) {
        int j = (index + i) % TABLE_SIZE;
        if (table->entries[j].key != NULL && strcmp(table->entries[j].key, key) == 0) {
            free(table->entries[j].key);
            free(table->entries[j].value);
            table->entries[j].key = NULL;
            table->size--;
            break;
        }
    }
}

void table_free(table_t *table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        free(table->entries[i].key);
        free(table->entries[i].value);
    }
    free(table->entries);
    free(table);
}