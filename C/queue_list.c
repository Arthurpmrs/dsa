#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
struct Node
{
    void *item;
    Node *next;
};

typedef struct QueueList
{
    Node *head;
    Node *tail;
    int size;
} QueueList;

QueueList *createQueueList()
{
    QueueList *newQueue = malloc(sizeof(QueueList));
    newQueue->head = NULL;
    newQueue->tail = NULL;
    newQueue->size = 0;
    return newQueue;
}

int isEmpty(QueueList *ql)
{
    return ql->head == NULL;
}

void enqueue(QueueList *ql, void *item)
{
    Node *newNode = malloc(sizeof(Node));
    newNode->item = item;
    newNode->next = NULL;

    if (isEmpty(ql))
    {
        ql->head = newNode;
        ql->tail = newNode;
    }
    else
    {
        ql->tail->next = newNode;
        ql->tail = newNode;
    }
    ql->size += 1;
}

void *dequeue(QueueList *ql)
{
    if (isEmpty(ql))
    {
        printf("The queue is empty.\n");
        return NULL;
    }

    Node *DHead = ql->head;
    void *item = ql->head->item;

    if (ql->head == ql->tail)
    {
        ql->head = NULL;
        ql->tail = NULL;
    }
    else
    {
        ql->head = ql->head->next;
    }

    free(DHead);
    ql->size -= 1;

    return item;
}

void printQueue(QueueList *ql, void (*printFun)(void *))
{
    if (isEmpty(ql))
    {
        printf("The queue is empty.\n");
        return;
    }

    printf("HEAD ");
    Node *current = ql->head;
    while (current != NULL)
    {

        printFun(current->item);
        if (current->next != NULL)
        {
            printf("->");
        }

        current = current->next;
    }
    printf(" LAST\n");
}

// Integer specific functions
void printInt(void *item)
{
    printf("%d", *(int *)item);
}

int main(void)
{
    int arr[10] = {45, 87, 96, 78, 12, 1, 0, 47, 3, 5};
    QueueList *ql = createQueueList();

    for (int i = 0; i < 10; i++)
    {
        enqueue(ql, (void *)&arr[i]);
    }
    printQueue(ql, printInt);
    dequeue(ql);
    dequeue(ql);
    printQueue(ql, printInt);
    printf("size: %d\n", ql->size);
    return 0;
}