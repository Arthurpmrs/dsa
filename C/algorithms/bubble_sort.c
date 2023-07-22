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
 * @brief Bubble sort sorting algorithm implementation.
 *
 * @param size an integer representing the size of the array
 * @param a an array of void pointers to be sorted
 * @param comparingFn a function that compares the target types. Must return a
 * negative number when a < b, 0 when a == b and a positive value when a > b
 */
void bubbleSort(int size, void *a[size], int (*comparingFn)(void *, void *))
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (comparingFn(a[j], a[j + 1]) > 0)
            {
                swap(&a[j], &a[j + 1]);
            }
        }
    }
}

/**
 * @brief Bubble sort sorting algorithm implementation, but with O(n) complexity
 * for already sorted arrays.
 *
 * @param size an integer representing the size of the array
 * @param a an array of void pointers to be sorted
 * @param comparingFn a function that compares the target types. Must return a
 * negative number when a < b, 0 when a == b and a positive value when a > b
 */
void bubbleSort2(int size, void *a[size], int (*comparingFn)(void *, void *))
{

    for (int j = size - 1; j >= 0; j--)
    {
        int switches = 0;
        for (int i = 0; i < j; i++)
        {
            printf("(j, i)=(%d, %d)\n", j, i);
            if (comparingFn(a[i], a[i + 1]) > 0)
            {
                switches++;
                swap(&a[i], &a[i + 1]);
            }
        }
        if (switches == 0)
        {
            return;
        }
    }
}

// Integer specific functions
int compareInt(void *a, void *b)
{
    return *(int *)a - *(int *)b;
}

int main(void)
{
    // int aSize = 7;
    // int arr[7] = {2, 5, 1, 0, 1, 3, 8};
    // int arr[7] = {1, 10, 0, 1, 0, 1, 10};
    // int arr[7] = {0, 5, 2, 1, 6, 3, 0};
    int aSize = 10;
    // int arr[10] = {45, 87, 1, 78, 12, 1, 0, 47, 45, 0};
    int arr[10] = {20, 11, 12, 13, 14, 15, 16, 17, 18, 19};

    void *varr[aSize];
    for (int i = 0; i < aSize; i++)
    {
        varr[i] = (void *)&arr[i];
    }

    bubbleSort2(aSize, varr, compareInt);

    for (int i = 0; i < aSize; i++)
    {
        printf("%d ", *(int *)varr[i]);
    }
    return 0;
}