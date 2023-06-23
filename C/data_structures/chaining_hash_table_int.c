#include <stdio.h>
#include <stdlib.h>
#include "chaining_hash_table.h"

// Fowler-Noll-Vo hash function
// https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function
unsigned int hashFn(char *key, size_t size)
{
    unsigned int hash = 0x811c9dc5;
    unsigned int prime = 0x01000193;
    for (int i = 0; i < strlen(key); i++)
    {
        hash = hash * prime;
        hash = hash ^ key[i];
    }
    return hash % size;
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
void put(HashTable *ht, char *key, int value)
{
    int *pvalue = malloc(sizeof(int));
    *pvalue = value;
    cht_put(ht, key, (void *)pvalue);
}

int get(HashTable *ht, char *key)
{
    void *result = cht_get(ht, key);
    if (result == NULL)
    {
        return -1;
    }
    else
    {
        return *(int *)result;
    }
}

int pop(HashTable *ht, char *key)
{
    void *presult = cht_pop(ht, key);
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

void print(HashTable *ht)
{
    cht_print(ht);
    printf("Count=>%d, size=>%ld, capacity=>%ld\n",
           ht->count, ht->_currentSize, ht->_capacity);
}

int main(void)
{
    HashTable *ht = cht_create(12, hashFn, printInt);

    put(ht, "1", 6000);
    put(ht, "15", 4000);
    put(ht, "7", 4000);
    put(ht, "8", 250);
    put(ht, "20", 500);
    put(ht, "10", 1000);
    put(ht, "11", 7888);
    put(ht, "28", 788);
    put(ht, "21", 78);
    put(ht, "31", 2000);
    put(ht, "99", 99999);
    print(ht);

    printf("----- Gets ----\n");
    printf("get(%s)=%d\n", "3", get(ht, "3"));
    printf("get(%s)=%d\n", "20", get(ht, "20"));
    printf("get(%s)=%d\n", "99", get(ht, "99"));

    printf("----- Pops ----\n");
    printf("pop(%s)=%d\n", "99", pop(ht, "11"));
    printf("pop(%s)=%d\n", "99", pop(ht, "8"));
    printf("pop(%s)=%d\n", "99", pop(ht, "99"));
    printf("pop(%s)=%d\n", "7", pop(ht, "7"));
    printf("pop(%s)=%d\n", "32", pop(ht, "32"));
    print(ht);

    printf("contains key=%s? %s\n", "32", (cht_containsKey(ht, "32") ? "Yes" : "No"));
    printf("contains key=%s? %s\n", "99", (cht_containsKey(ht, "99") ? "Yes" : "No"));

    ht = cht_erase(ht);
    // print(ht);
}