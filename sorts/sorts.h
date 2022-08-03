#ifndef __SORTS__
#define __SORTS__

#include <stddef.h>

int *BinarySearchIter(int arr[], size_t size, int key);

int *BinarySearchRec(int arr[], size_t size, int key);

void *GenericBS(void *arr, size_t nmemb, size_t elem_size,
                int (*compar)(const void *, const void *), void *key);



int MergeSort(int *arr_to_sort, size_t size);

void Qsort(int arr[], size_t size);


#endif