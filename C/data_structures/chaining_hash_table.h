#ifndef CHAINING_HASH_TABLE_H_
#define CHAINING_HASH_TABLE_H_

#define MAX_HASH_TABLE_SIZE 10

typedef struct Element Element;
struct Element
{
    void *key;
    void *item;
    Element *next;
};

typedef struct HashTable
{
    Element *table[MAX_HASH_TABLE_SIZE];
    int count;
    int _currentSize;
    int _capacity;
} HashTable;

/**
 * @brief Creates a new HashTable
 *
 * @return HashTable* a pointer to the HashTable
 */
HashTable *cht_create();

/**
 * @brief Adds new [key, value] pair to the HashTable
 *
 * @param ht the pointer to the HashTable
 * @param key a void pointer to a key. Must be dynamically allocated
 * @param item a void pointer to a value.  Must be dynamically allocated
 * @param hashFn a hash function
 * @param compareKeyFn a function that compares the target types. Must return a
 * negative number when a < b, 0 when a == b and a positive value when a > b. If
 * both values are NULL, must return 0, if only one is NULL, must return -1
 */
void cht_put(HashTable *ht, void *key, void *item, int (*hashFn)(void *),
             int (*compareKeyFn)(void *, void *));

/**
 * @brief Retrieves a value given a key
 *
 * @param ht the pointer to the HashTable
 * @param key a void pointer to the desired key
 * @param hashFn a hash function
 * @param compareKeyFn a function that compares the target types. Must return a
 * negative number when a < b, 0 when a == b and a positive value when a > b. If
 * both values are NULL, must return 0, if only one is NULL, must return -1
 * @return void* a void pointer to the desired value
 */
void *cht_get(HashTable *ht, void *key, int (*hashFn)(void *),
              int (*compareKeyFn)(void *, void *));

/**
 * @brief Removes a [key, value] pair and retrives the value given a key.
 *
 * The key is freed together with the Element struct
 *
 * @param ht the pointer to the HashTable
 * @param key a void pointer to the key to be removed
 * @param hashFn a hash function
 * @param compareKeyFn a function that compares the target types. Must return a
 * negative number when a < b, 0 when a == b and a positive value when a > b. If
 * both values are NULL, must return 0, if only one is NULL, must return -1
 * @return void* a void pointer to the value.
 */
void *cht_pop(HashTable *ht, void *key, int (*hashFn)(void *),
              int (*compareKeyFn)(void *, void *));

/**
 * @brief Checks if a key is in the HashTable
 *
 * @param ht the pointer to the HashTable
 * @param key a void pointer to the key to be checked
 * @param hashFn a hash function
 * @param compareKeyFn a function that compares the target types. Must return a
 * negative number when a < b, 0 when a == b and a positive value when a > b. If
 * both values are NULL, must return 0, if only one is NULL, must return -1
 * @return int
 */
int cht_containsKey(HashTable *ht, void *key, int (*hashFn)(void *),
                    int (*compareKeyFn)(void *, void *));

/**
 * @brief Remove all [key, value] pairs from the HashTable
 *
 * @param ht the pointer to the HashTable
 */
void cht_clear(HashTable *ht);

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
 * @param printFn a function the prints to the console the desired type
 */
void cht_print(HashTable *ht, void (*printFn)(void *));

#endif
