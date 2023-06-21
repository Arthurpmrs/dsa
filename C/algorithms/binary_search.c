#include <stdio.h>

/**
 * @brief Binary search implementation.
 *
 * @param size an integer representing the size of the array
 * @param a an array of void pointers to be searched
 * @param target a void pointer to the value to be found
 * @param comparingFn a function that compares the target types. Must return a
 * negative number when a < b, 0 when a == b and a positive value when a > b
 * @return int the index of the found target. Returns -1 if not found.
 */
int binarySearch(int size, void *a[], void *target,
                 int (*comparingFn)(void *, void *))
{
    int start = 0;
    int end = size - 1;
    int middle;
    while (start <= end)
    {
        middle = (start + end) / 2;
        if (comparingFn(target, a[middle]) < 0)
        {
            end = middle - 1;
        }
        else if (comparingFn(target, a[middle]) > 0)
        {
            start = middle + 1;
        }
        else
        {
            return middle;
        }
    }
    return -1;
}

/**
 * @brief Recursive binary search implementation.
 *
 * @param start an integer representing the starting index of the subarray
 * @param end an integer representing the ending index of the subarray
 * @param a an array of void pointers to be searched
 * @param target a void pointer to the value to be found
 * @param comparingFn a function that compares the target types. Must return a
 * negative number when a < b, 0 when a == b and a positive value when a > b
 * @return int the index of the found target. Returns -1 if not found.
 */
int binarySearchRec(int start, int end, void *a[], void *target,
                    int (*comparingFn)(void *, void *))
{
    if (start > end)
    {
        return -1;
    }

    int middle = (start + end) / 2;

    if (comparingFn(target, a[middle]) < 0)
    {
        binarySearchRec(start, middle - 1, a, target, comparingFn);
    }
    else if (comparingFn(target, a[middle]) > 0)
    {
        binarySearchRec(middle + 1, end, a, target, comparingFn);
    }
    else
    {
        return middle;
    }
}

// Integer specific functions
int compareInt(void *a, void *b)
{
    return *(int *)a - *(int *)b;
}

int main(void)
{
    int aSize = 10;
    int arr[10] = {0, 1, 1, 12, 13, 45, 45, 78, 99, 101};

    void *varr[aSize];
    for (int i = 0; i < aSize; i++)
    {
        varr[i] = (void *)&arr[i];
    }

    int target = 101;
    // int targetIndex = binarySearch(aSize, varr, (void *)&target, compareInt);
    int targetIndex = binarySearchRec(0, aSize - 1, varr, (void *)&target, compareInt);
    printf("index of %d: %d\n", target, targetIndex);
    return 0;
}