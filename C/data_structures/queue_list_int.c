#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
struct Node
{
    int item;
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

void enqueue(QueueList *ql, int item)
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

int dequeue(QueueList *ql)
{
    if (isEmpty(ql))
    {
        printf("The queue is empty.\n");
        return -100;
    }

    Node *DHead = ql->head;
    int item = ql->head->item;

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

void printQueue(QueueList *ql)
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

        printf("%d ", current->item);
        if (current->next != NULL)
        {
            printf("->");
        }

        current = current->next;
    }
    printf(" LAST\n");
}