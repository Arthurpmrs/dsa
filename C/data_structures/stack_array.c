#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 15

typedef struct StackArray
{
    void *items[MAX_STACK_SIZE];
    int currentSize;
} StackArray;

StackArray *createStackArray()
{
    StackArray *newStack = malloc(sizeof(StackArray));
    newStack->currentSize = 0;
    return newStack;
}

void push(StackArray *sa, void *item)
{
    if (sa->currentSize == MAX_STACK_SIZE)
    {
        printf("Error: Stack overflow.\n");
        return;
    }

    sa->items[sa->currentSize++] = item;
}

void *pop(StackArray *sa)
{
    if (sa->currentSize == 0)
    {
        printf("Error: Stack underflow.\n");
        return NULL;
    }

    return sa->items[--sa->currentSize];
}

void *peek(StackArray *sa)
{
    if (sa->currentSize == 0)
    {
        printf("Stack is empty.\n");
        return NULL;
    }

    return sa->items[sa->currentSize - 1];
}

void printStackArray(StackArray *sa, void (*printFun)(void *))
{
    if (sa->currentSize == 0)
    {
        printf("Stack is empty.\n");
        return;
    }

    printf("TOP\n");
    for (int i = sa->currentSize - 1; i >= 0; i--)
    {
        printFun(sa->items[i]);
        printf("\n");
    }
}

// Integer specific functions
void printInt(void *item)
{
    printf("%d", *(int *)item);
}

int main(void)
{
    StackArray *sa = createStackArray();
    int arr[10] = {45, 87, 96, 78, 12, 1, 0, 47, 3, 5};
    push(sa, (void *)&arr[0]);
    push(sa, (void *)&arr[1]);
    pop(sa);
    push(sa, (void *)&arr[2]);
    push(sa, (void *)&arr[3]);
    push(sa, (void *)&arr[4]);
    push(sa, (void *)&arr[5]);
    pop(sa);
    push(sa, (void *)&arr[6]);
    pop(sa);
    push(sa, (void *)&arr[7]);
    push(sa, (void *)&arr[8]);
    push(sa, (void *)&arr[9]);
    pop(sa);
    pop(sa);

    printf("top=%d\n", *(int *)peek(sa));
    printStackArray(sa, printInt);

    return 0;
}