#include <stdio.h>
#include <stdlib.h>
#include "chaining_hash_table.h"

// Functions for int
int hashInt(void *key)
{
    return *(int *)key % MAX_HASH_TABLE_SIZE;
}

int compareInt(void *a, void *b)
{
    if (a != NULL && b != NULL)
    {
        return *(int *)a - *(int *)b;
    }
    else if (a == NULL && b == NULL)
    {
        return 0;
    }
    else
    {
        return -1;
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

// Wrappers
void put(HashTable *ht, int key, int value)
{
    int *pkey = malloc(sizeof(int));
    *pkey = key;
    int *pvalue = malloc(sizeof(int));
    *pvalue = value;
    cht_put(ht, (void *)pkey, (void *)pvalue, hashInt, compareInt);
}

int get(HashTable *ht, int key)
{
    int *pkey = malloc(sizeof(int));
    *pkey = key;
    void *result = cht_get(ht, (void *)pkey, hashInt, compareInt);
    free(pkey);
    if (result == NULL)
    {
        return -1;
    }
    else
    {
        return *(int *)result;
    }
}

int pop(HashTable *ht, int key)
{
    int *pkey = malloc(sizeof(int));
    *pkey = key;
    void *presult = cht_pop(ht, (void *)pkey, hashInt, compareInt);
    free(pkey);
    if (presult == NULL)
    {
        return -1;
    }
    else
    {
        int result = *(int *)presult;
        free(presult);
        return result;
    }
}

int containsKey(HashTable *ht, int key)
{
    int *pkey = malloc(sizeof(int));
    *pkey = key;
    int result = cht_containsKey(ht, (void *)pkey, hashInt, compareInt);
    free(pkey);
    return result;
}

void print(HashTable *ht)
{
    cht_print(ht, printInt);
    printf("Count=>%d, size=>%d, capacity=>%d\n",
           ht->count, ht->_currentSize, ht->_capacity);
}

int main(void)
{
    HashTable *ht = cht_create();
    put(ht, 1, 6000);
    put(ht, 15, 4000);
    put(ht, 7, 4000);
    put(ht, 8, 250);
    put(ht, 20, 500);
    put(ht, 10, 1000);
    put(ht, 11, 7888);
    put(ht, 28, 788);
    put(ht, 21, 78);
    put(ht, 31, 2000);
    print(ht);

    printf("----- Gets ----\n");
    printf("get(%d)=%d\n", 3, get(ht, 3));
    printf("get(%d)=%d\n", 20, get(ht, 20));
    printf("get(%d)=%d\n", 99, get(ht, 99));

    printf("----- Pops ----\n");
    printf("pop(%d)=%d\n", 15, pop(ht, 15));
    print(ht);
    printf("pop(%d)=%d\n", 99, pop(ht, 99));
    print(ht);
    printf("pop(%d)=%d\n", 1, pop(ht, 1));
    print(ht);
    printf("pop(%d)=%d\n", 11, pop(ht, 11));
    print(ht);
    printf("pop(%d)=%d\n", 31, pop(ht, 31));
    print(ht);
    printf("pop(%d)=%d\n", 21, pop(ht, 21));
    print(ht);

    printf("contains key=%d? %s\n", 31, (containsKey(ht, 31) ? "Yes" : "No"));
    printf("contains key=%d? %s\n", 99, (containsKey(ht, 99) ? "Yes" : "No"));

    cht_clear(ht);

    print(ht);
}