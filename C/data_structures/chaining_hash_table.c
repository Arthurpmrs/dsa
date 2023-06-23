#include "chaining_hash_table.h"

// Dynamic sized: https://codereview.stackexchange.com/questions/254854/hashtable-with-separate-chaining-and-dynamic-resizing?newreg=539d2e7c60bf4823836bcb387be1088c
// Hash functions: https://en.wikipedia.org/wiki/List_of_hash_functions#Non-cryptographic_hash_functions
HashTable *cht_create(size_t size, unsigned int (*hashFn)(char *, size_t),
                      void (*printFn)(void *))
{
    HashTable *ht = malloc(sizeof(HashTable));

    if (ht == NULL)
    {
        exit(EXIT_FAILURE);
    }

    KVPair **table = calloc(sizeof(KVPair), size);

    if (table == NULL)
    {
        free(ht);
        exit(EXIT_FAILURE);
    }

    ht->_table = table;
    ht->_currentSize = 0;
    ht->_capacity = size;
    ht->_hashFn = hashFn;
    ht->_printFn = printFn;
    ht->count = 0;
    return ht;
}

bool cht_put(HashTable *ht, char *key, void *value)
{
    if (ht == NULL)
    {
        exit(EXIT_FAILURE);
    }

    if (ht->_currentSize == ht->_capacity)
    {
        printf("Hash overflow\n");
        return false;
    }

    if (key == NULL || value == NULL)
    {
        return false;
    }

    unsigned h = ht->_hashFn(key, ht->_capacity);

    KVPair *current = ht->_table[h];
    KVPair *prev = NULL;
    while (current != NULL)
    {
        // Updates the value on a existing key
        if (strcmp(current->key, key) == 0)
        {
            current->value = value;
            break;
        }
        prev = current;
        current = current->next;
    }

    if (current == NULL)
    {
        KVPair *newPair = malloc(sizeof(KVPair));

        // Taking ownership of the key memory
        newPair->key = malloc(strlen(key) + 1);
        strcpy(newPair->key, key);

        // Note: THe ownership of the value belongs to the caller
        newPair->value = value;
        newPair->next = NULL;

        if (prev == NULL)
        {
            ht->_table[h] = newPair;
            ht->_currentSize++;
        }
        else
        {
            prev->next = newPair;
        }
        ht->count++;
    }

    return true;
}

void *cht_get(HashTable *ht, char *key)
{
    if (ht == NULL)
    {
        exit(EXIT_FAILURE);
    }

    if (key == NULL)
    {
        return NULL;
    }

    unsigned int h = ht->_hashFn(key, ht->_capacity);

    KVPair *current = ht->_table[h];
    while (current != NULL)
    {
        if (strcmp(current->key, key) == 0)
        {
            return current->value;
        }
        current = current->next;
    }

    return NULL;
}

void *cht_pop(HashTable *ht, char *key)
{
    if (ht == NULL)
    {
        exit(EXIT_FAILURE);
    }

    if (key == NULL)
    {
        return NULL;
    }

    unsigned int h = ht->_hashFn(key, ht->_capacity);

    KVPair *current = ht->_table[h];
    KVPair *prev = NULL;

    while (current != NULL)
    {
        if (strcmp(current->key, key) == 0)
        {
            break;
        }
        prev = current;
        current = current->next;
    }
    // If the key is not found
    if (current == NULL)
    {
        return NULL;
    }

    void *value = current->value;
    ht->count--;

    // The found key if the first
    if (prev == NULL)
    {
        ht->_table[h] = current->next;

        // The spot if now empty
        if (ht->_table[h] == NULL)
        {
            ht->_currentSize--;
        }
    }
    else
    {
        prev->next = current->next;
    }

    free(current->key);
    free(current);

    return value;
}

bool cht_containsKey(HashTable *ht, char *key)
{
    if (ht == NULL)
    {
        exit(EXIT_FAILURE);
    }

    if (key == NULL)
    {
        return false;
    }

    unsigned int h = ht->_hashFn(key, ht->_capacity);

    KVPair *current = ht->_table[h];
    while (current != NULL)
    {
        if (strcmp(current->key, key) == 0)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

bool cht_clear(HashTable *ht)
{
    if (ht == NULL)
    {
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < ht->_capacity; i++)
    {
        KVPair *current = ht->_table[i];
        while (current != NULL)
        {
            KVPair *tmp = current;
            current = current->next;

            free(tmp->key);
            free(tmp->value);
            free(tmp);
        }
        ht->_table[i] = NULL;
    }

    ht->count = 0;
    ht->_currentSize = 0;

    return true;
}

void *cht_erase(HashTable *ht)
{
    if (ht == NULL)
    {
        exit(EXIT_FAILURE);
    }

    cht_clear(ht);

    free(ht->_table);
    free(ht);

    return NULL;
}

void cht_print(HashTable *ht)
{
    printf("{");
    for (int i = 0; i < ht->_capacity; i++)
    {
        if (ht->_table[i] != NULL)
        {
            KVPair *current = ht->_table[i];
            printf("[");
            while (current != NULL)
            {
                printf("\"%s\"", current->key);
                printf(": ");
                ht->_printFn(current->value);
                if (current->next != NULL)
                {
                    printf(", ");
                }
                current = current->next;
            }
            printf("]");
        }
        else
        {
            printf("nil: nil");
        }

        if (i != ht->_capacity - 1)
        {
            printf(", ");
        }
    }
    printf("}\n");
}