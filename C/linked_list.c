#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
struct Node
{
    void *item;
    Node *next;
};

typedef struct LinkeList
{
    Node *head;
    Node *tail;
    int size;
} LinkedList;

LinkedList *createLinkedList()
{
    LinkedList *newLL = malloc(sizeof(LinkedList));
    newLL->head = NULL;
    newLL->tail = NULL;
    newLL->size = 0;
    return newLL;
}

int isEmpty(LinkedList *ll)
{
    return ll->head == NULL;
}

void addToHead(LinkedList *ll, void *item)
{
    Node *newNode = malloc(sizeof(Node));
    newNode->item = item;

    if (isEmpty(ll))
    {
        ll->head = newNode;
        ll->tail = newNode;
        newNode->next = NULL;
    }
    else
    {
        newNode->next = ll->head;
        ll->head = newNode;
    }
    ll->size += 1;
}

void addToTail(LinkedList *ll, void *item)
{
    Node *newNode = malloc(sizeof(Node));
    newNode->item = item;
    newNode->next = NULL;

    if (isEmpty(ll))
    {
        ll->head = newNode;
        ll->tail = newNode;
    }
    else
    {
        ll->tail->next = newNode;
        ll->tail = newNode;
    }
    ll->size += 1;
}

void *deleteFromHead(LinkedList *ll)
{
    if (isEmpty(ll))
    {
        printf("List is empty.\n");
        return NULL;
    }

    Node *DHead = ll->head;
    void *item = ll->head->item;

    if (ll->head == ll->tail)
    {
        ll->head = NULL;
        ll->tail = NULL;
    }
    else
    {
        ll->head = ll->head->next;
    }

    free(DHead);
    ll->size -= 1;

    return item;
}

void *deleteFromTail(LinkedList *ll)
{
    if (isEmpty(ll))
    {
        printf("List is empty.\n");
        return NULL;
    }

    Node *DHead = ll->tail;
    void *item = ll->tail->item;

    if (ll->head == ll->tail)
    {
        ll->head = NULL;
        ll->tail = NULL;
    }
    else
    {
        Node *current = ll->head;
        while (current->next != ll->tail)
        {
            current = current->next;
        }

        current->next = NULL;
        ll->tail = current;
    }

    free(DHead);
    ll->size -= 1;

    return item;
}

void *deleteItem(LinkedList *ll, void *item, int (*compareFun)(void *, void *))
{
    if (isEmpty(ll))
    {
        printf("List is empty.\n");
        return NULL;
    }

    if (compareFun(item, ll->head->item))
    {
        return deleteFromHead(ll);
    }
    else if (compareFun(item, ll->tail->item))
    {
        return deleteFromTail(ll);
    }
    else
    {
        Node *current = ll->head;
        while (!compareFun(item, current->next->item))
        {
            current = current->next;
        }

        Node *DHead = current->next;
        void *item = current->next->item;

        current->next = current->next->next;

        free(DHead);
        ll->size -= 1;

        return item;
    }
}

void deleteList(LinkedList *ll)
{
    while (ll->size != 0)
    {
        deleteFromHead(ll);
    }
}

void *search(LinkedList *ll, void *target, int (*compareFun)(void *, void *))
{
    Node *current = ll->head;
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

void printLinkedList(LinkedList *ll, void (*printFun)(void *))
{
    if (isEmpty(ll))
    {
        printf("List is empty.\n");
        return;
    }
    Node *current = ll->head;
    while (current != NULL)
    {
        printFun(current->item);
        if (current->next != NULL)
        {
            printf("->");
        }
        current = current->next;
    }
    printf("\n");
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
    LinkedList *ll = createLinkedList();

    for (int i = 0; i < 10; i++)
    {
        addToTail(ll, (void *)&arr[i]);
    }
    printLinkedList(ll, printInt);
    printf("size: %d\n", ll->size);

    int target = 99;
    void *item = search(ll, (void *)&target, compareInt);
    if (item == NULL)
    {
        printf("did not find it!\n");
    }
    else
    {
        printf("found it: %d\n", *(int *)item);
    }

    printf("Deleted item: %d\n", *(int *)deleteFromHead(ll));
    printf("Deleted item: %d\n", *(int *)deleteFromTail(ll));
    printLinkedList(ll, printInt);

    int targets[3] = {96, 1, 3};
    for (int i = 0; i < 3; i++)
    {
        printf("Delete item: %d\n", *(int *)deleteItem(ll, (void *)&targets[i],
                                                       compareInt));
        printLinkedList(ll, printInt);
    }

    deleteList(ll);
    printLinkedList(ll, printInt);

    return 0;
}