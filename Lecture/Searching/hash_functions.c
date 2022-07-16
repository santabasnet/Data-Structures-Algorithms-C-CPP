/**
 * Hash Functions.
 *
 * By: Santa Basnet
 * Everest Engineering College.
 *
 * Date: 2021-12-14
 */

/**
 * Header Utilities.
 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Constant and Macros.
 */
#define MAX_SIZE 10

/**
 * Table entry data structure representation.
 */
typedef struct HEntry {
    char *hashKey;
    char *hashValue;
    struct HEntry *next; /*Linked list for next entries to resolve the collision. */
} HashEntry;

/**
 * Definition of the hash entries.
 */
typedef struct {
    HashEntry **allEntries;
} HashEntries;

/**
 * Generates hash key for the given input string(it's a character pointer).
 * A simple hash function, for the string.
 *
 * hash(i) = hash(i - 1) * 33 ^ str[i]
 * Source: http://www.cse.yorku.ca/~oz/hash.html
 */
unsigned long hashedKey(const char *key) {
    unsigned long value = 5381;
    int c;
    while (c = *key++) value = ((value << 5) + value) + c; /* value * 33 + c */
    return value % MAX_SIZE;
}

/**
 * Creates a base table for the Hash Entries.
 */
HashEntries *createHashTable(void) {
    HashEntries *hashTable = (HashEntries *) malloc(sizeof(HashEntries) * 1);
    hashTable->allEntries = (HashEntry **) malloc(sizeof(HashEntry *) * MAX_SIZE);
    for (int index = 0; index < MAX_SIZE; index++) hashTable->allEntries[index] = NULL;
    return hashTable;
}

/**
 * Define the hash pair as an data entry.
 */
HashEntry *hashPair(const char *hashKey, const char *hashValue) {
    HashEntry *entry = (HashEntry *) malloc(sizeof(entry) + 1);
    entry->hashKey = (char *) malloc(strlen(hashKey) + 1);
    entry->hashValue = (char *) malloc(strlen(hashValue) + 1);
    strcpy(entry->hashKey, hashKey);
    strcpy(entry->hashValue, hashValue);
    entry->next = NULL;
    return entry;
}

/**
 * Set data to the hash table.
 */
void HashTableSet(HashEntries *hashTable, const char *key, const char *value) {
    unsigned int hashBucket = hashedKey(key);
    HashEntry *entry = hashTable->allEntries[hashBucket];
    /**
     * Check if no entries, in the beginning.
     */
    if (entry == NULL) {
        hashTable->allEntries[hashBucket] = hashPair(key, value);
        return;
    }
    HashEntry *previous;
    while (entry != NULL) {
        if (strcmp(entry->hashKey, key) == 0) {
            free(entry->hashKey);//Make free before replacing the value.
            entry->hashValue = (char *) malloc(strlen(value) + 1);
            strcpy(entry->hashValue, value);
            return;
        }
        previous = entry;
        entry = previous->next;
    }
    previous->next = hashPair(key, value);
}

/**
 * Retrieve data from the hash table.
 */
char *HashTableGet(HashEntries *hashTable, const char *key) {
    HashEntry *entry = hashTable->allEntries[hashedKey(key)];
    if (entry == NULL) return NULL;
    while (entry != NULL) {
        if (strcmp(entry->hashKey, key) == 0) return entry->hashValue;
        entry = entry->next;
    }
    return NULL;
}

/**
 * Format the key entry in 6 digits.
 */
char *formatHashKey(const char *key, int size) {
    int paddingSize = size - strlen(key);
    char *padding = (char *) malloc(sizeof(char) * paddingSize + 1);
    int i = 0;
    for (; i < paddingSize; i++) {
        padding[i] = '0';
    }
    padding[i] = '\0';
    strcat(padding, key);
    return padding;
}

/**
 * Display Hash Table.
 */
void DisplayHashTable(HashEntries *hashTable) {
    printf("\nAll hash entries :");
    printf("\n---------------------------------------------------------------\n");
    for (int index = 0; index < MAX_SIZE; index++) {
        HashEntry *entry = hashTable->allEntries[index];
        if (entry == NULL) continue;

        int length = snprintf(NULL, 0, "%d", index) + 1;
        char *indexEntry = (char *) malloc(sizeof(char) * length);
        snprintf(indexEntry, length, "%d", index);
        printf("Bucket[%s]: ", formatHashKey(indexEntry, 5));
        free(indexEntry);

        while (1) {
            printf("[%s = %s] ", formatHashKey(entry->hashKey, 5), entry->hashValue);
            if (entry->next == NULL) break;
            entry = entry->next;
        }
        printf("\n");
    }
    printf("---------------------------------------------------------------\n");
}

/**
 * Release hash table memory.
 */
void Clean(HashEntries *hashTable) {
    for (int index = 0; index < MAX_SIZE; index++) {
        HashEntry *entry = hashTable->allEntries[index];
        if (entry == NULL) continue;
        while (entry->next != NULL) {
            HashEntry *tEntry = entry;
            entry = entry->next;
            free(tEntry);
        }
    }
    free(hashTable->allEntries);
    free(hashTable);
}

/**
 * Main function starts here.
 * @return 0 for successful output.
 */
int main() {

    /**
     * Create a hash table for demonstration.
     */
    HashEntries *hashTable = createHashTable();

    HashTableSet(hashTable, "100", "Ram");
    HashTableSet(hashTable, "0", "Shyam");
    HashTableSet(hashTable, "50", "Ranjeet");
    HashTableSet(hashTable, "5984", "Kumari");
    HashTableSet(hashTable, "8755", "Sangeeta");
    HashTableSet(hashTable, "976", "Charan");
    HashTableSet(hashTable, "342", "Kristina");
    HashTableSet(hashTable, "789", "Shophia");
    HashTableSet(hashTable, "777", "Reena");
    HashTableSet(hashTable, "8997", "Jyoti");

    DisplayHashTable(hashTable);

    Clean(hashTable);

    return 0;
}