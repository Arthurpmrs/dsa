#include <stdio.h>

/**
 * @brief Swaps two void pointers.
 *
 * @param a Pointer to a void pointer.
 * @param b Pointer to another void pointer.
 */
void swap(void **a, void **b)
{
    void *tmp = *a;
    *a = *b;
    *b = tmp;
}

/**
 * @brief Partitions an subarray around a pivot.
 *
 * The pivot is calculated as the center value of [start, end] for convenience.
 *
 * @param a the array being sorted
 * @param start the subarray's first element index
 * @param end the subarray's last element index
 * @param compareFn a function that compares the target types. Must return a
 * negative number when a < b, 0 when a == b and a positive value when a > b
 * @return int the final pivot index.
 */
int partition(void *a[], int start, int end, int (*compareFn)(void *, void *))
{
    int pIndex = (start + end) / 2;
    void *pivot = a[pIndex];
    int higher = end;
    int lower = start;

    while (lower < higher)
    {
        // Adapted to deal with duplicate values
        while (compareFn(a[lower], pivot) <= 0 && lower < pIndex)
            lower++;
        while (compareFn(a[higher], pivot) >= 0 && higher > pIndex)
            higher--;

        if (lower < higher)
        {
            // Check if lower or higher reached the pivot. If so, update
            // the pivot index.
            if (higher == pIndex)
            {
                pIndex = lower;
            }
            else if (lower == pIndex)
            {
                pIndex = higher;
            }

            swap(&a[lower], &a[higher]);
        }
    }
    return higher;
}

/**
 * @brief Divide and conquer sorting algorithm based on recursion and element
 * swapping around an pivot volue.
 *
 * @param a an array of void pointers to be sorted
 * @param start the subarray's first element index
 * @param end the subarray's last element index
 * @param compareFn a function that compares the target types. Must return a
 * negative number when a < b, 0 when a == b and a positive value when a > b
 */
void quickSort(void *a[], int start, int end, int (*compareFn)(void *, void *))
{
    if (start < end)
    {
        int p = partition(a, start, end, compareFn);
        quickSort(a, start, p, compareFn);
        quickSort(a, p + 1, end, compareFn);
    }
}

/**
 * @brief Divide and conquer sorting algorithm based on recursion and element
 * swapping around an pivot volue.
 *
 * @param a an array of void pointers to be sorted
 * @param size the subarray's size
 * @param compareFn a function that compares the target types. Must return a
 * negative number when a < b, 0 when a == b and a positive value when a > b
 */
void quickSort2(void *a[], int size, int (*compareFn)(void *, void *))
{
    if (size <= 1)
    {
        return;
    }
    else
    {
        int start = 0;
        int end = size - 1;
        int pIndex = size / 2;
        void *pivot = a[pIndex];

        while (start < end)
        {
            while (compareFn(a[start], pivot) <= 0 && start < pIndex)
            {
                start++;
            }
            while (compareFn(a[end], pivot) >= 0 && end > pIndex)
            {
                end--;
            }

            if (start < end)
            {
                if (end == pIndex)
                {
                    pIndex = start;
                }
                else if (start == pIndex)
                {
                    pIndex = end;
                }
                swap(&a[start], &a[end]);
            }
        }
        quickSort2(a, end, compareFn);
        quickSort2(a + start, size - start, compareFn);
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
    int arr[7] = {12, 15, 11, 10, 11, 13, 18};
    // int arr[7] = {1, 10, 0, 1, 0, 1, 10};
    // int arr[10] = {42, 87, 2, 78, 12, 1, 0, 47, 45, 3};
    // int arr[10] = {45, 87, 1, 78, 12, 1, 0, 47, 45, 0};

    void *varr[aSize];
    for (int i = 0; i < aSize; i++)
    {
        varr[i] = (void *)&arr[i];
    }

    // quickSort(varr, 0, aSize - 1, compareInt);
    quickSort2(varr, aSize, compareInt);

    for (int i = 0; i < aSize; i++)
    {
        printf("%d ", *(int *)varr[i]);
    }
    return 0;
}