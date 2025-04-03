#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Austin Bangle
// Chpt6 PA

// Structure representing a key-value pair (Item)
typedef struct Item {
    char *key;              // Key string
    char *value;            // Value string
    struct Item *next;      // Pointer to next item in the bucket (for collision resolution)
} Item;

// Structure representing the hash table
typedef struct HashTable {
    Item **hashTable;       // Array of pointers to Items (buckets)
    int length;             // Number of buckets in the hash table
} HashTable;

// Function: createItem
// Purpose: Creates a new Item with the given key and value, and allocates the necessary memory.
Item* createItem(char *key, char *value) {
    Item *newItem = (Item*)malloc(sizeof(Item));
    newItem->key = strdup(key);
    newItem->value = strdup(value);
    newItem->next = NULL;
    return newItem;
}

// Function: createHashTable
// Purpose: Creates a new hash table with a specified number of buckets.
// Initializes each bucket pointer to NULL.
HashTable* createHashTable(int size) {
    HashTable *table = (HashTable*)malloc(sizeof(HashTable));
    table->length = size;
    table->hashTable = (Item**)malloc(sizeof(Item*) * size);
    for (int i = 0; i < size; i++) {
        table->hashTable[i] = NULL;
    }
    return table;
}

// Function: hash
// Purpose: Computes a hash value for a given key using the pseudocode from Figure 6.8.3.
// Modification: Do NOT mod (%) the result by the number of buckets.
// Uses an initial value of 0 and a multiplier of 13.
int hash(char *key) {
    int stringHash = 0;
    int multiplier = 13;
    while (*key) {
        // Multiply the current hash value by the multiplier and add the ASCII value of the character.
        stringHash = (stringHash * multiplier) + (int)(*key);
        key++;
    }
    return stringHash;
}

// Function: hashInsert
// Purpose: Inserts a key-value pair into the hash table.
// If the key already exists, updates its value; otherwise, a new item is appended to the bucket's list.
int hashInsert(HashTable *table, char *key, char *value) {
    // Compute the bucket index by modding the hash with the table length.
    int bucketIndex = hash(key) % table->length;
    Item *currentItem = table->hashTable[bucketIndex];
    Item *previousItem = NULL;

    // Traverse the bucket's linked list to check if the key already exists.
    while (currentItem != NULL) {
        if (strcmp(currentItem->key, key) == 0) {
            // Key exists: free the old value and update it with the new one.
            free(currentItem->value);
            currentItem->value = strdup(value);
            return 1;
        }
        previousItem = currentItem;
        currentItem = currentItem->next;
    }

    // Key does not exist: create a new item.
    Item *newItem = (Item*)malloc(sizeof(Item));
    newItem->key = strdup(key);
    newItem->value = strdup(value);
    newItem->next = NULL;

    // If bucket is empty, insert the new item; otherwise, add it at the end of the list.
    if (table->hashTable[bucketIndex] == NULL) {
        table->hashTable[bucketIndex] = newItem;
    } else {
        previousItem->next = newItem;
    }
    return 1;
}

// Function: hashGet
// Purpose: Retrieves the value associated with a given key in the hash table.
// Returns NULL if the key is not found.
char *hashGet(HashTable *table, char *key) {
    int bucketIndex = hash(key) % table->length;
    Item *item = table->hashTable[bucketIndex];
    while (item != NULL) {
        if (strcmp(item->key, key) == 0) {
            return item->value;
        }
        item = item->next;
    }
    return NULL;
}

// Function: hashRemove
// Purpose: Removes the key-value pair from the hash table.
// Frees the memory associated with the key and value and returns 1 if removal is successful,
// or 0 if the key is not found.
int hashRemove(HashTable *table, char *key) {
    int bucketIndex = hash(key) % table->length;
    Item *currentItem = table->hashTable[bucketIndex];
    Item *previousItem = NULL;

    // Traverse the bucket to find the item with the matching key.
    while (currentItem != NULL) {
        if (strcmp(currentItem->key, key) == 0) {
            // Remove the item from the list.
            if (previousItem == NULL) {
                table->hashTable[bucketIndex] = currentItem->next;
            } else {
                previousItem->next = currentItem->next;
            }
            free(currentItem->key);
            free(currentItem->value);
            free(currentItem);
            return 1;
        }
        previousItem = currentItem;
        currentItem = currentItem->next;
    }
    return 0;
}

// Function: printTable
// Purpose: Prints the contents of the hash table.
// For each key-value pair, the function displays the key, value, and the computed hash value.
void printTable(HashTable *table) {
    for (int i = 0; i < table->length; i++) {
        printf("Bucket %d: ", i);
        Item *currentItem = table->hashTable[i];
        if (currentItem == NULL) {
            printf("empty\n");
        } else {
            while (currentItem != NULL) {
                // Print key, value, and computed hash value.
                printf("[key: %s, value: %s, hash: %d] ", currentItem->key, currentItem->value, hash(currentItem->key));
                currentItem = currentItem->next;
            }
            printf("\n");
        }
    }
}

// Function: main
// Purpose: Demonstrates the functionality of the hash table by performing a series of operations:
// Inserting key-value pairs, displaying the table, removing a key, attempting to retrieve keys,
// and updating a key's value.
int main() {
    // Create a hash table with 5 buckets.
    HashTable *table = createHashTable(5);

    // 1. Insert the following key-value pairs.
    hashInsert(table, "keyA1", "value1");
    hashInsert(table, "keyB2", "value2");
    hashInsert(table, "keyC3", "value3");
    hashInsert(table, "keyD23", "value23");
    hashInsert(table, "keyE45", "value45");
    hashInsert(table, "keyF52", "value52");

    // 2. Display the hash table contents.
    printf("Hash Table Contents:\n");
    printTable(table);

    // 3. Remove keyF52 and display a message based on the result.
    if (hashRemove(table, "keyF52")) {
        printf("Removed keyF52 successfully.\n");
    } else {
        printf("Failed to remove keyF52.\n");
    }

    // 4. Attempt to get a non-existing key keyZ6.
    char *value = hashGet(table, "keyZ6");
    if (value == NULL) {
        printf("Key keyZ6 not found.\n");
    } else {
        printf("Found key keyZ6 with value: %s\n", value);
    }

    // 5. Get an existing key keyC3.
    value = hashGet(table, "keyC3");
    if (value == NULL) {
        printf("Key keyC3 not found.\n");
    } else {
        printf("Found key keyC3 with value: %s\n", value);
    }

    // 6. Insert additional key-value pairs.
    hashInsert(table, "keyG18", "value18");
    hashInsert(table, "keyH7", "value7");
    hashInsert(table, "keyI33", "value33");

    // 7. Update keyD23 with a new value.
    hashInsert(table, "keyD23", "newvalue23");

    // 8. Display the updated hash table contents.
    printf("Updated Hash Table Contents:\n");
    printTable(table);

    // Free all allocated memory.
    for (int i = 0; i < table->length; i++) {
        Item *currentItem = table->hashTable[i];
        while (currentItem != NULL) {
            Item *temp = currentItem;
            currentItem = currentItem->next;
            free(temp->key);
            free(temp->value);
            free(temp);
        }
    }
    free(table->hashTable);
    free(table);

    return 0;
}

