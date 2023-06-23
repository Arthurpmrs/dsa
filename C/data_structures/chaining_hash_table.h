#ifndef CHAINING_HASH_TABLE_H_
#define CHAINING_HASH_TABLE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct KVPair KVPair;
struct KVPair
{
    char *key;
    void *value;
    KVPair *next;
};

typedef struct HashTable
{
    KVPair **_table;
    size_t _currentSize;
    size_t _capacity;
    void (*_printFn)(void *);
    unsigned int (*_hashFn)(char *, size_t);
    unsigned int count;
} HashTable;

/**
 * @brief Creates a new HashTable
 *
 * @param size a size_t integer representing the capacity of the HashTable
 * @param hashFn a hash function that takes a string and the table size
 * @param printFn a function the prints to the console the desired type
 * @return HashTable* a pointer to the created hashtable
 */
HashTable *cht_create(size_t size, unsigned int (*hashFn)(char *, size_t),
                      void (*printFn)(void *));

/**
 * @brief Adds new [key, value] pair to the HashTable
 *
 * @param ht the pointer to the HashTable
 * @param key a string representing the key
 * @param value a void pointer to a value
 */
bool cht_put(HashTable *ht, char *key, void *value);

/**
 * @brief Retrieves a value given a key
 *
 * @param ht the pointer to the HashTable
 * @param key a string representing the key
 * @return void* a void pointer to the desired value
 */
void *cht_get(HashTable *ht, char *key);

/**
 * @brief Removes a [key, value] pair and retrives the value given a key.
 *
 * The key is freed together with the Element struct
 *
 * @param ht the pointer to the HashTable
 * @param key a string representing the key
 * @return void* a void pointer to the value.
 */
void *cht_pop(HashTable *ht, char *key);

/**
 * @brief Checks if a key is in the HashTable
 *
 * @param ht the pointer to the HashTable
 * @param key a void pointer to the key to be checked
 * @return bool
 */
bool cht_containsKey(HashTable *ht, char *key);

/**
 * @brief Remove all [key, value] pairs from the HashTable
 *
 * @param ht the pointer to the HashTable
 */
bool cht_clear(HashTable *ht);

/**
 * @brief Completely dealocate the HashTable.
 *
 * Returns NULL so the pointer to the HashTable is cleared
 *
 * @param ht the pointer to the HashTable
 * @return void* NULL
 */
void *cht_erase(HashTable *ht);

/**
 * @brief Pretty prints the HashTable
 *
 * @param ht the pointer to the HashTable
 */
void cht_print(HashTable *ht);

#endif
