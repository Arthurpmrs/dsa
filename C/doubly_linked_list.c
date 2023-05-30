#include <stdio.h>
#include <stdlib.h>

typedef struct DNode DNode;
struct DNode
{
    void *item;
    DNode *next;
    DNode *prev;
};

typedef struct DLinkeList
{
    DNode *head;
    DNode *tail;
    int size;
} DLinkedList;

DLinkedList *createDLinkedList()
{
    DLinkedList *dll = malloc(sizeof(DLinkedList));
    dll->head = NULL;
    dll->tail = NULL;
    dll->size = 0;
    return dll;
}

int isEmpty(DLinkedList *dll)
{
    return dll->head == NULL;
}

void addToHead(DLinkedList *dll, void *item)
{
    DNode *newNode = malloc(sizeof(DNode));
    newNode->item = item;
    newNode->prev = NULL;

    if (isEmpty(dll))
    {
        dll->head = newNode;
        dll->tail = newNode;
        newNode->next = NULL;
    }
    else
    {
        newNode->next = dll->head;
        dll->head->prev = newNode;
        dll->head = newNode;
    }
    dll->size += 1;
}

void addToTail(DLinkedList *dll, void *item)
{
    DNode *newNode = malloc(sizeof(DNode));
    newNode->item = item;
    newNode->next = NULL;

    if (isEmpty(dll))
    {
        dll->head = newNode;
        dll->tail = newNode;
    }
    else
    {
        dll->tail->next = newNode;
        newNode->prev = dll->tail;
        dll->tail = newNode;
    }
    dll->size += 1;
}

void printDLinkedListForward(DLinkedList *dll, void (*printFun)(void *))
{
    if (isEmpty(dll))
    {
        printf("List is empty.\n");
        return;
    }
    DNode *current = dll->head;
    while (current != NULL)
    {
        printFun(current->item);
        if (current->next != NULL)
        {
            printf("<->");
        }
        current = current->next;
    }
    printf("\n");
}

void printDLinkedListBackward(DLinkedList *dll, void (*printFun)(void *))
{
    if (isEmpty(dll))
    {
        printf("List is empty.\n");
        return;
    }
    DNode *current = dll->tail;
    while (current != NULL)
    {
        printFun(current->item);
        if (current->prev != NULL)
        {
            printf("<->");
        }
        current = current->prev;
    }
    printf("\n");
}

void *deleteFromHead(DLinkedList *dll)
{
    if (isEmpty(dll))
    {
        printf("List is empty.\n");
        return NULL;
    }

    DNode *DHead = dll->head;
    void *item = dll->head->item;

    if (dll->head == dll->tail)
    {
        dll->head = NULL;
        dll->tail = NULL;
    }
    else
    {
        dll->head = dll->head->next;
        dll->head->prev = NULL;
    }

    free(DHead);
    dll->size -= 1;

    return item;
}

void *deleteFromTail(DLinkedList *dll)
{
    if (isEmpty(dll))
    {
        printf("List is empty.\n");
        return NULL;
    }

    DNode *DHead = dll->tail;
    void *item = dll->tail->item;

    if (dll->head == dll->tail)
    {
        dll->head = NULL;
        dll->tail = NULL;
    }
    else
    {
        // Does not require to loop over the list
        dll->tail = dll->tail->prev;
        dll->tail->next = NULL;
    }

    free(DHead);
    dll->size -= 1;

    return item;
}

void *deleteItem(DLinkedList *dll, void *item, int (*compareFun)(void *, void *))
{
    if (isEmpty(dll))
    {
        printf("List is empty.\n");
        return NULL;
    }

    if (compareFun(item, dll->head->item))
    {
        return deleteFromHead(dll);
    }
    else if (compareFun(item, dll->tail->item))
    {
        return deleteFromTail(dll);
    }
    else
    {
        DNode *current = dll->head;
        while (!compareFun(item, current->next->item))
        {
            current = current->next;
        }

        DNode *DHead = current->next;
        void *item = current->next->item;

        current->next = current->next->next;
        current->next->prev = current;

        free(DHead);
        dll->size -= 1;

        return item;
    }
}

void deleteList(DLinkedList *dll)
{
    while (dll->size != 0)
    {
        deleteFromHead(dll);
    }
}

void *search(DLinkedList *dll, void *target, int (*compareFun)(void *, void *))
{
    if (isEmpty(dll))
    {
        printf("List is empty.\n");
        return NULL;
    }

    DNode *current = dll->head;
    while (current != NULL)
    {
        if (compareFun(current->item, target))
        {
            return current->item;
        }
        current = current->next;
    }
    return NULL;
}

// Integer specific functions
void printInt(void *item)
{
    printf("%d", *(int *)item);
}

int compareInt(void *item1, void *item2)
{
    return *(int *)item1 == *(int *)item2;
}

int main(void)
{
    int arr[10] = {45, 87, 96, 78, 12, 1, 0, 47, 3, 5};
    DLinkedList *dll = createDLinkedList();

    for (int i = 0; i < 10; i++)
    {
        addToTail(dll, (void *)&arr[i]);
    }
    printDLinkedListForward(dll, printInt);
    printDLinkedListBackward(dll, printInt);
    printf("size: %d\n", dll->size);

    int target = 0;
    void *item = search(dll, (void *)&target, compareInt);
    if (item == NULL)
    {
        printf("did not find it!\n");
    }
    else
    {
        printf("found it: %d\n", *(int *)item);
    }

    printf("Deleted item: %d\n", *(int *)deleteFromHead(dll));
    printf("Deleted item: %d\n", *(int *)deleteFromTail(dll));
    printDLinkedListForward(dll, printInt);
    printDLinkedListBackward(dll, printInt);

    printf("Remove target:\n");
    int targets[3] = {96, 1, 3};
    for (int i = 0; i < 3; i++)
    {
        printf("Delete item: %d\n", *(int *)deleteItem(dll, (void *)&targets[i],
                                                       compareInt));
        printDLinkedListForward(dll, printInt);
    }

    deleteList(dll);
    printDLinkedListForward(dll, printInt);
    return 0;
}