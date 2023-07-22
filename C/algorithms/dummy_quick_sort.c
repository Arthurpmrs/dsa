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
    int p = (start + end) / 2;

    while (start < end)
    {
        while (compareFn(a[start], a[p]) < 0)
            start++;
        while (compareFn(a[end], a[p]) > 0)
            end--;

        if (start < end)
        {
            if (end == p)
            {
                p = start;
            }
            else if (start == p)
            {
                p = end;
            }
            swap(&a[start], &a[end]);
        }
    }
    return p;
}

/**
 * @brief Divide and conquer sorting algorithm based on recursion and element
 * swapping around an pivot volue.
 *
 * @param an array of void pointers to be sorted
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

// Integer specific functions
int compareInt(void *a, void *b)
{
    return *(int *)a - *(int *)b;
}

int main(void)
{
    int aSize = 7;
    // int arr[7] = {2, 5, 1, 0, 7, 3, 8};
    // int arr[7] = {110, 18, 54, 11, 2, 17, 6};
    int arr[7] = {2, 5, 1, 0, 1, 3, 8};

    void *varr[aSize];
    for (int i = 0; i < aSize; i++)
    {
        varr[i] = (void *)&arr[i];
    }

    quickSort(varr, 0, aSize - 1, compareInt);

    for (int i = 0; i < aSize; i++)
    {
        printf("%d ", *(int *)varr[i]);
    }
    return 0;
}