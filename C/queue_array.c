#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 7

typedef struct QueueArray
{
    void *items[MAX_QUEUE_SIZE];
    int currentSize;
    int head;
    int tail;
} QueueArray;

QueueArray *createQueueArray()
{
    QueueArray *newQueue = malloc(sizeof(QueueArray));
    newQueue->currentSize = 0;
    newQueue->head = 0;
    newQueue->tail = MAX_QUEUE_SIZE - 1;
    return newQueue;
}

void enqueue(QueueArray *qa, void *item)
{
    if (qa->currentSize >= MAX_QUEUE_SIZE)
    {
        printf("Queue overflow.\n");
        return;
    }

    qa->tail = (qa->tail + 1) % MAX_QUEUE_SIZE;
    qa->items[qa->tail] = item;
    qa->currentSize++;
}

void *dequeue(QueueArray *qa)
{
    if (qa->currentSize == 0)
    {
        printf("Queue is empty.\n");
        return NULL;
    }

    void *item = qa->items[qa->head];
    qa->head = (qa->head + 1) % MAX_QUEUE_SIZE;
    qa->currentSize--;
    return item;
}

void printQueue(QueueArray *qa, void (*printFun)(void *))
{
    if (qa->currentSize == 0)
    {
        printf("Queue is empty.\n");
        return;
    }

    printf("HEAD ");
    for (int i = qa->head; i % MAX_QUEUE_SIZE != qa->tail; i++)
    {
        printFun(qa->items[i % MAX_QUEUE_SIZE]);
        printf(" ");
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
    QueueArray *qa = createQueueArray();

    for (int i = 0; i < 6; i++)
    {
        enqueue(qa, (void *)&arr[i]);
    }
    printQueue(qa, printInt);
    dequeue(qa);
    dequeue(qa);
    dequeue(qa);
    printQueue(qa, printInt);
    enqueue(qa, (void *)&arr[6]);
    enqueue(qa, (void *)&arr[7]);
    enqueue(qa, (void *)&arr[8]);
    enqueue(qa, (void *)&arr[9]);
    printQueue(qa, printInt);
    printf("size: %d\n", qa->currentSize);
    enqueue(qa, (void *)&arr[9]);
    return 0;
}