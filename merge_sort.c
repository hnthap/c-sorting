/**
 * @file merge_sort.c
 * @author HN Thap
 * @brief Simple implementation of buffer-based merge sort algorithm.
 * 
 * The core function is merge_sort(), which depends on
 * merge_sort_recursive() and merge_sort_merge().
 * 
 * The main function not just serves as a usage example, it also support
 * command line arguments. Just run:
 * 
 * merge_sort 4 3 10 2 1
 * 
 * in which merge_sort is the executable, 4 is the array size, and 3, 10,
 * 2, 1 is the 4-element array that need to be sorted.
 * 
 * @version 0.1
 * @date 2025-08-08
 * @copyright See LICENSE
 */

#include <stdio.h>
#include <stdlib.h>

void merge_sort(int arr_count, int *arr);
void merge_sort_recursive(int *arr, int left, int right, int *buffer);
void merge_sort_merge(int *arr, int left, int middle, int right, int *buffer);

int main(int argc, char *argv[])
{
    int i, n;
    int *a;
    if (argc == 1)
    {
        fprintf(stderr, "Invalid arguments: Array size must be specified.\n");
        return 1;
    }
    n = atoi(argv[1]);
    if (n <= 0)
    {
        /* An empty array is sorted by nature. */
        return 0;
    }
    if (argc != n + 2)
    {
        fprintf(stderr, "Invalid arguments: Array elements must be listed in full.\n");
        return 1;
    }
    a = malloc(n * sizeof(int));
    if (a == NULL)
    {
        fprintf(stderr, "Failed to allocate array. Exiting.\n");
        return 1;
    }
    for (i = 0; i < n; i += 1)
    {
        a[i] = atoi(argv[i + 2]);
    }
    merge_sort(n, a);
    for (i = 0; i < n; i += 1)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
    free(a);
    return 0;
}

void merge_sort(int arr_count, int *arr)
{
    int *buffer;
    if (arr == NULL)
    {
        fprintf(stderr, "Invalid parameter: arr cannot be NULL.\n");
    }
    buffer = malloc(arr_count * sizeof(int));
    if (buffer == NULL)
    {
        fprintf(stderr, "Failed to allocate buffer. Exiting.\n");
        exit(1);
    }
    if (arr_count < 2)
    {
        return;
    }
    merge_sort_recursive(arr, 0, arr_count, buffer);
    free(buffer);
}

void merge_sort_recursive(int *arr, int left, int right, int *buffer)
{
    int middle;
    if (right - left <= 1)
    {
        return;
    }
    middle = (left + right) / 2;
    merge_sort_recursive(arr, left, middle, buffer);
    merge_sort_recursive(arr, middle, right, buffer);
    merge_sort_merge(arr, left, middle, right, buffer);
}

void merge_sort_merge(int *arr, int left, int middle, int right, int *buffer)
{
    int i = left;
    int j = middle;
    int k = left;
    while (i < middle && j < right)
    {
        if (arr[i] < arr[j])
        {
            buffer[k++] = arr[i++];
        }
        else
        {
            buffer[k++] = arr[j++];
        }
    }
    while (i < middle)
    {
        buffer[k++] = arr[i++];
    }
    while (j < right)
    {
        buffer[k++] = arr[j++];
    }
    for (i = left; i < right; i++)
    {
        arr[i] = buffer[i];
    }
}