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

void merge(void *a[], int start, int middle, int end,
           int (*compareFn)(void *, void *))
{
    QueueList *ql1 = createQueueList();
    QueueList *ql2 = createQueueList();

    for (int i = start; i < middle + 1; i++)
    {
        enqueue(ql1, a[i]);
    }
    for (int i = middle + 1; i < end + 1; i++)
    {
        enqueue(ql2, a[i]);
    }

    int j = start;
    while (!isEmpty(ql1) && !isEmpty(ql2))
    {
        if (compareFn(ql1->head->item, ql2->head->item) < 0)
        {
            a[j++] = dequeue(ql1);
        }
        else
        {
            a[j++] = dequeue(ql2);
        }
    }

    while (!isEmpty(ql1))
    {
        a[j++] = dequeue(ql1);
    }
    while (!isEmpty(ql2))
    {
        a[j++] = dequeue(ql2);
    }

    free(ql1);
    free(ql2);
}

// Integer specific functions
int compareInt(void *a, void *b)
{
    return *(int *)a - *(int *)b;
}

void mergeSort(void *a[], int start, int end, int (*compareFn)(void *, void *))
{
    if (start < end)
    {
        int middle = (start + end) / 2;
        mergeSort(a, start, middle, compareFn);
        mergeSort(a, middle + 1, end, compareFn);

        merge(a, start, middle, end, compareFn);
    }
}

int main(void)
{
    int aSize = 10;
    int arr[10] = {45, 87, 1, 78, 12, 1, 0, 47, 45, 0};

    void *varr[aSize];
    for (int i = 0; i < aSize; i++)
    {
        varr[i] = (void *)&arr[i];
    }

    mergeSort(varr, 0, aSize - 1, compareInt);

    for (int i = 0; i < aSize; i++)
    {
        printf("%d ", *(int *)varr[i]);
    }
    return 0;
}