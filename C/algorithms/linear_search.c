#include <stdio.h>

/**
 * @brief Linear search implementation.
 *
 * @param size an integer representing the size of the array
 * @param a an array of void pointers to be searched
 * @param target a void pointer to the value to be found
 * @param comparingFn a function that compares the target types. Must return a
 * negative number when a < b, 0 when a == b and a positive value when a > b
 * @return int the index of the found target. Returns -1 if not found.
 */
int linearSearch(int size, void *a[], void *target,
                 int (*comparingFn)(void *, void *))
{
    for (int i = 0; i < size; i++)
    {
        if (comparingFn(a[i], target) == 0)
        {
            return i;
        }
    }
    return -1;
}

// Integer specific functions
int compareInt(void *a, void *b)
{
    return *(int *)a - *(int *)b;
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

    int target = 1;
    int targetIndex = linearSearch(aSize, varr, (void *)&target, compareInt);
    printf("index of %d: %d\n", target, targetIndex);
    return 0;
}