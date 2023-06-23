#include <stdio.h>
#include <stdlib.h>
#include "chaining_hash_table.h"

#define MAX_HASH_TABLE_SIZE 10
// Dynamic sized: https://codereview.stackexchange.com/questions/254854/hashtable-with-separate-chaining-and-dynamic-resizing?newreg=539d2e7c60bf4823836bcb387be1088c
// Hash functions: https://en.wikipedia.org/wiki/List_of_hash_functions#Non-cryptographic_hash_functions
HashTable *cht_create()
{
    HashTable *ht = malloc(sizeof(HashTable));
    for (int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
    {
        ht->table[i] = NULL;
    }
    ht->count = 0;
    ht->_currentSize = 0;
    ht->_capacity = MAX_HASH_TABLE_SIZE;
    return ht;
}

void cht_put(HashTable *ht, void *key, void *item, int (*hashFn)(void *),
             int (*compareKeyFn)(void *, void *))
{
    if (ht->_currentSize == ht->_capacity)
    {
        printf("Hash overflow\n");
        return;
    }

    int h = hashFn(key);

    Element *current = ht->table[h];
    Element *prev = NULL;
    while (current != NULL)
    {
        if (compareKeyFn(current->key, key) == 0)
        {
            current->item = item;
            break;
        }
        prev = current;
        current = current->next;
    }

    if (current == NULL)
    {
        Element *newElement = malloc(sizeof(Element));
        newElement->item = item;
        newElement->key = key;
        newElement->next = NULL;
        if (prev == NULL)
        {
            ht->table[h] = newElement;
            ht->_currentSize++;
        }
        else
        {
            prev->next = newElement;
        }
        ht->count++;
    }
}

void *cht_get(HashTable *ht, void *key, int (*hashFn)(void *),
              int (*compareKeyFn)(void *, void *))
{
    int h = hashFn(key);
    Element *current = ht->table[h];
    while (current != NULL)
    {
        if (compareKeyFn(current->key, key) == 0)
        {
            return current->item;
        }
        current = current->next;
    }

    return NULL;
}

void *cht_pop(HashTable *ht, void *key, int (*hashFn)(void *),
              int (*compareKeyFn)(void *, void *))
{
    int h = hashFn(key);
    Element *current = ht->table[h];

    if (current == NULL)
    {
        return NULL;
    }

    if (compareKeyFn(current->key, key) == 0)
    {
        Element *DHead = current;
        void *item = DHead->item;
        ht->table[h] = current->next;
        free(DHead->key);
        free(DHead);
        ht->count--;
        if (ht->table[h] == NULL)
        {
            ht->_currentSize--;
        }
        return item;
    }
    else
    {
        while (current->next != NULL)
        {
            if (compareKeyFn(current->next->key, key) == 0)
            {
                Element *DHead = current->next;
                void *item = DHead->item;

                current->next = current->next->next;
                free(DHead->key);
                free(DHead);
                ht->count--;

                return item;
            }
            current = current->next;
        }
    }

    return NULL;
}

int cht_containsKey(HashTable *ht, void *key, int (*hashFn)(void *),
                    int (*compareKeyFn)(void *, void *))
{
    int h = hashFn(key);
    Element *current = ht->table[h];
    while (current != NULL)
    {
        if (compareKeyFn(current->key, key) == 0)
        {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

void cht_clear(HashTable *ht)
{
    for (int i = 0; i < ht->_capacity; i++)
    {
        Element *current = ht->table[i];
        while (current != NULL)
        {
            Element *DHead = current;
            current = current->next;
            free(DHead->key);
            free(DHead->item);
            free(DHead);
        }
        ht->table[i] = NULL;
    }
    ht->count = 0;
    ht->_currentSize = 0;
}

void *cht_erase(HashTable *ht)
{
    cht_clear(ht);
    free(ht);
    return NULL;
}

void cht_print(HashTable *ht, void (*printFn)(void *))
{
    printf("{");
    for (int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
    {
        if (ht->table[i] != NULL)
        {
            Element *current = ht->table[i];
            printf("[");
            while (current != NULL)
            {
                printFn(current->key);
                printf(": ");
                printFn(current->item);
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

        if (i != MAX_HASH_TABLE_SIZE - 1)
        {
            printf(", ");
        }
    }
    printf("}\n");
}