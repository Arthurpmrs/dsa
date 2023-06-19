#include <stdio.h>

void swap(void **a, void **b)
{
    void *tmp = *a;
    *a = *b;
    *b = tmp;
}

int partition(void *a[], int start, int end, int (*compareFn)(void *, void *))
{
    int p = (start + end) / 2;
    void *pivot = a[p];
    printf("opa, entrei aqui -> start=%d, p=%d, end=%d\n", start, p, end);
    int higher = end;
    int lower = start;
    int counter = 0;
    while (lower < higher)
    {
        printf("lower=%d, heigher=%d, p=%d\n", lower, higher, p);
        while (compareFn(a[lower], pivot) <= 0 && lower < p)
        {
            lower++;
            printf("       low=%d\n", lower);
        }
        while (compareFn(a[higher], pivot) >= 0 && higher > p)
        {
            higher--;
            printf("       high=%d\n", higher);
        }
        printf("swap?? lower=%d, heigher=%d, p=%d\n", lower, higher, p);

        if (lower < higher)
        {
            // Check if lower or higher reached the pivot. Then, update
            // the pivot index.
            if (higher == p)
            {
                p = lower;
            }
            else if (lower == p)
            {
                p = higher;
            }

            swap(&a[lower], &a[higher]);
        }
    }
    return higher;
}

void quickSort(void *a[], int start, int end, int (*compareFn)(void *, void *), int c)
{
    if (c > 4)
    {
        return;
    }
    if (start < end)
    {
        int p = partition(a, start, end, compareFn);
        printf(">>start=%d, p=%d, end=%d\n", start, p, end);
        for (int i = 0; i < 7; i++)
        {
            printf("%d ", *(int *)a[i]);
        }
        printf("\n");
        quickSort(a, start, p, compareFn, c + 1);
        quickSort(a, p + 1, end, compareFn, c + 1);
    }
}

// Integer specific functions
int compareInt(void *a, void *b)
{
    return *(int *)a - *(int *)b;
}

int main(void)
{
    int aSize = 7;
    int arr[7] = {2, 5, 1, 0, 1, 3, 8};
    // int arr[7] = {1, 10, 0, 1, 0, 1, 10};
    // int arr[7] = {0, 5, 2, 1, 6, 3, 0};
    // int arr[] = {45, 87, 1, 78, 12, 1, 0, 47, 45, 0};

    void *varr[aSize];
    for (int i = 0; i < aSize; i++)
    {
        varr[i] = (void *)&arr[i];
    }

    quickSort(varr, 0, aSize - 1, compareInt, 0);

    for (int i = 0; i < aSize; i++)
    {
        printf("%d ", *(int *)varr[i]);
    }
    return 0;
    return 0;
}