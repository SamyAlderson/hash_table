#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "table.h"

// Entry point for the program
int main(int argc, char *argv[]) {
    // Initialize a hash table with a size of 16
    HashTable *hash_table = new_hash_table(16);

    // Insert some key-value pairs into the table
    insert("apple", "fruit");
    insert("carrot", "vegetable");
    insert("banana", "fruit");
    insert("broccoli", "vegetable");

    // Lookup some keys in the table
    printf("Lookup of 'apple': %s\n", lookup("apple"));
    printf("Lookup of 'carrot': %s\n", lookup("carrot"));
    printf("Lookup of 'banana': %s\n", lookup("banana"));
    printf("Lookup of 'broccoli': %s\n", lookup("broccoli"));
    printf("Lookup of 'cherry': %s\n", lookup("cherry"));

    // Remove some keys from the table
    remove_key("carrot");
    remove_key("banana");
    remove_key("broccoli");

    // Lookup some keys after removal
    printf("Lookup of 'apple': %s\n", lookup("apple"));
    printf("Lookup of 'carrot': %s\n", lookup("carrot"));
    printf("Lookup of 'banana': %s\n", lookup("banana"));
    printf("Lookup of 'broccoli': %s\n", lookup("broccoli"));
    printf("Lookup of 'cherry': %s\n", lookup("cherry"));

    // Free the hash table
    free_hash_table(hash_table);

    return 0;
}