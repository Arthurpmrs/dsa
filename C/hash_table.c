#include <stdio.h>
#include <stdlib.h>

#define MAX_HASH_TABLE_SIZE 10

typedef struct Element
{
    void *key;
    void *item;
} Element;

typedef struct HashTable
{
    Element *table[MAX_HASH_TABLE_SIZE];
    int size;
} HashTable;

HashTable *createHashTable()
{
    HashTable *ht = malloc(sizeof(HashTable));
    for (int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
    {
        ht->table[i] = NULL;
    }
    ht->size = 0;
    return ht;
}

void put(HashTable *ht, void *key, void *item, int (*hashFn)(void *),
         int (*compareKeyFn)(void *, void *))
{
    if (ht->size == MAX_HASH_TABLE_SIZE)
    {
        printf("Hash overflow\n");
        return;
    }

    int h = hashFn(key);

    while (ht->table[h] != NULL)
    {
        if (compareKeyFn(ht->table[h]->key, key) == 0)
        {
            ht->table[h]->item = item;
            break;
        }
        else if (ht->table[h]->key == NULL)
        {
            ht->table[h]->item = item;
            ht->table[h]->key = key;
            ht->size++;
        }

        h = (h + 1) % MAX_HASH_TABLE_SIZE;
    }

    if (ht->table[h] == NULL)
    {
        Element *newElement = malloc(sizeof(Element));
        newElement->item = item;
        newElement->key = key;
        ht->table[h] = newElement;
        ht->size++;
    }
}

void *get(HashTable *ht, void *key, int (*hashFn)(void *),
          int (*compareKeyFn)(void *, void *))
{
    int h = hashFn(key);
    while (ht->table[h] != NULL)
    {
        printf("h=%d\n", h);

        if (compareKeyFn(ht->table[h]->key, key) == 0)
        {
            return ht->table[h]->item;
        }
        h = (h + 1) % MAX_HASH_TABLE_SIZE;
    }

    return NULL;
}

void *delete(HashTable *ht, void *key, int (*hashFn)(void *),
             int (*compareKeyFn)(void *, void *))
{
    int h = hashFn(key);
    while (ht->table[h] != NULL)
    {
        if (compareKeyFn(ht->table[h]->key, key) == 0)
        {
            ht->table[h]->key = NULL;
            ht->size--;
            return ht->table[h]->item;
        }
        h = (h + 1) % MAX_HASH_TABLE_SIZE;
    }
    return NULL;
}

void printHashTable(HashTable *ht, void (*printFn)(void *))
{
    printf("{");
    for (int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
    {
        if (ht->table[i] != NULL)
        {
            printFn(ht->table[i]->key);
            printf(": ");
            printFn(ht->table[i]->item);
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

// Functions for int
int hashInt(void *key)
{
    return *(int *)key % MAX_HASH_TABLE_SIZE;
}

int compareInt(void *a, void *b)
{
    if (a != NULL && b != NULL)
    {
        int x = *(int *)a;
        int y = *(int *)b;
        if (x == y)
        {
            return 0;
        }
        else if (x > y)
        {
            return 1;
        }
        else
        {
            return -1;
        }
    }
    else
    {
        if (a == NULL && b == NULL)
        {
            return 0;
        }
        else
        {
            return -1;
        }
    }
}

void printInt(void *item)
{
    if (item == NULL)
    {
        printf("nil");
    }
    else
    {
        printf("%d", *(int *)item);
    }
}

int main(void)
{
    int keys[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int values[10] = {10, 1000, 2000, 3000, 4000, 6000, 7777, 8888, 999, 5000};

    HashTable *ht = createHashTable();
    for (int i = 0; i < 10; i++)
    {
        put(ht, (void *)&keys[i], (void *)&values[i], hashInt, compareInt);
    }
    printHashTable(ht, printInt);

    printf("delete->%d\n", *(int *)delete (ht, (void *)&keys[5], hashInt, compareInt));
    printHashTable(ht, printInt);

    int key = 45;
    int value = 7070;

    put(ht, (void *)&key, (void *)&value, hashInt, compareInt);
    printHashTable(ht, printInt);

    put(ht, (void *)&key, (void *)&value, hashInt, compareInt);
    printHashTable(ht, printInt);

    // int keys[5] = {3, 14, 15, 92, 4};
    // int values[5] = {1000, 2000, 3000, 4000, 6000};

    // HashTable *ht = createHashTable();
    // for (int i = 0; i < 4; i++)
    // {
    //     put(ht, (void *)&keys[i], (void *)&values[i], hashInt, compareInt);
    // }
    // printHashTable(ht, printInt);

    // printf("delete->%d\n", *(int *)delete (ht, (void *)&keys[2], hashInt, compareInt));

    // printf("get->%d\n", *(int *)get(ht, (void *)&keys[3], hashInt, compareInt));
    // printHashTable(ht, printInt);

    // put(ht, (void *)&keys[4], (void *)&values[4], hashInt, compareInt);
    // printHashTable(ht, printInt);

    return 0;
}