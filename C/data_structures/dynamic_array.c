#include <stdio.h>
#include <stdlib.h>
#define INITIAL_CAPACITY 10

typedef struct DynamicArray
{
    void **elements;
    int size;
    int capacity;
} DynamicArray;

DynamicArray *createDynamicArray()
{
    void **elements = malloc(INITIAL_CAPACITY * sizeof(void *));
    if (elements == NULL)
    {
        return 0;
    }

    DynamicArray *da = malloc(sizeof(DynamicArray));
    if (da == NULL)
    {
        free(elements);
        return 0;
    }

    da->elements = elements;
    da->size = 0;
    da->capacity = INITIAL_CAPACITY;

    return da;
}

int _needSizeIncrease(DynamicArray *da)
{
    return 2 * (da->size + 1) > da->capacity;
}

int _increase(DynamicArray *da)
{
    int newCapacity = 2 * da->capacity;
    da->elements = realloc(da->elements, newCapacity * sizeof(void *));
    if (da->elements == NULL)
    {
        return 0;
    }
    da->capacity = newCapacity;
    return 1;
}

int _needSizeDecrease(DynamicArray *da)
{
    if (da->capacity <= INITIAL_CAPACITY)
    {
        return 0;
    }
    return (da->size + 1) < da->capacity / 4;
}

int _decrease(DynamicArray *da)
{
    int newCapacity = da->capacity / 2;
    da->elements = realloc(da->elements, newCapacity * sizeof(void *));
    if (da->elements == NULL)
    {
        return 0;
    }
    da->capacity = newCapacity;
    return 1;
}

void append(DynamicArray *da, void *item)
{
    if (_needSizeIncrease(da))
    {
        _increase(da);
    }

    da->elements[da->size++] = item;
}

void *pop(DynamicArray *da)
{
    if (_needSizeDecrease(da))
    {
        _decrease(da);
    }

    return da->elements[--da->size];
}

void insertOnIndex(DynamicArray *da, int i, void *item)
{
    if (_needSizeIncrease(da))
    {
        _increase(da);
    }

    int j = da->size++;
    printf("j=%d\n", j);
    while (j > i)
    {
        da->elements[j] = da->elements[j - 1];
        j--;
    }
    da->elements[i] = item;
}

void deleteFromIndex(DynamicArray *da, int i)
{
    if (_needSizeDecrease(da))
    {
        _decrease(da);
    }

    da->size--;
    while (i < da->size)
    {
        da->elements[i] = da->elements[i + 1];
        i++;
    }
}

void print(DynamicArray *da, void(printFn)(void *))
{
    for (int i = 0; i < da->size; i++)
    {
        printf("arr[%d]=", i);
        printFn(da->elements[i]);
        printf("\n");
    }
    printf("\n");
}

// Integer functions
void printInt(void *item)
{
    printf("%d ", *(int *)item);
}

int main(void)
{
    DynamicArray *da = createDynamicArray();

    // Create dummie array
    for (int i = 0; i < 22; i++)
    {
        int *item = malloc(sizeof(int));
        *item = i * (i / 3);
        append(da, (void *)item);
        printf("size=%d, (s2=>%d), capacity=%d last=%d\n",
               da->size, 2 * (da->size + 1), da->capacity,
               *(int *)da->elements[da->size - 1]);
    }

    // Insert items on an index
    for (int i = 1; i < 15; i++)
    {
        int *item = malloc(sizeof(int));
        *item = 9997;
        insertOnIndex(da, da->size, (void *)item);
    }
    print(da, printInt);
    printf("size=%d\n", da->size);

    // Delete item from an index
    deleteFromIndex(da, 9);
    print(da, printInt);
    printf("size=%d\n", da->size);

    return 0;
}