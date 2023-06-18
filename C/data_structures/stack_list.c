#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
struct Node
{
    void *item;
    Node *next;
};

typedef struct StackList
{
    Node *top;
    int size;
} StackList;

StackList *creatStackList()
{
    StackList *newStack = malloc(sizeof(StackList));
    newStack->top = NULL;
    newStack->size = 0;
    return newStack;
}

int isEmpty(StackList *sl)
{
    return sl->top == NULL;
}

void push(StackList *sl, void *item)
{
    Node *newNode = malloc(sizeof(Node));
    newNode->item = item;

    if (isEmpty(sl))
    {
        sl->top = newNode;
        newNode->next = NULL;
    }
    else
    {
        newNode->next = sl->top;
        sl->top = newNode;
    }

    sl->size += 1;
}

void *pop(StackList *sl)
{
    if (isEmpty(sl))
    {
        printf("List is empty.\n");
        return NULL;
    }

    Node *DHead = sl->top;
    void *item = sl->top->item;

    sl->top = sl->top->next;

    free(DHead);
    sl->size -= 1;

    return item;
}

void *peek(StackList *sl)
{
    return sl->top->item;
}

void printStackList(StackList *sl, void (*printFun)(void *))
{
    printf("Stack top\n--------\n");
    Node *current = sl->top;
    while (current != NULL)
    {
        printFun(current->item);
        if (current->next != NULL)
        {
            printf("\nv\n");
        }
        current = current->next;
    }
}

// Integer specific functions
void printInt(void *item)
{
    printf("%d", *(int *)item);
}

int main(void)
{
    StackList *sl = creatStackList();
    int arr[10] = {45, 87, 96, 78, 12, 1, 0, 47, 3, 5};

    push(sl, (void *)&arr[0]);
    push(sl, (void *)&arr[1]);
    pop(sl);
    push(sl, (void *)&arr[2]);
    push(sl, (void *)&arr[3]);
    push(sl, (void *)&arr[4]);
    push(sl, (void *)&arr[5]);
    pop(sl);
    push(sl, (void *)&arr[6]);
    pop(sl);
    push(sl, (void *)&arr[7]);
    push(sl, (void *)&arr[8]);
    push(sl, (void *)&arr[9]);
    pop(sl);
    pop(sl);

    printf("top->%d\n", *(int *)peek(sl));
    printStackList(sl, printInt);
    return 0;
}