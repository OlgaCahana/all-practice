/*******************************************************************************
*	Written by:		Olga Danielle Cahana									   *
*	Date:			3/2/2022												   *
*	Reviewed by:	Daniel						    					 	   *
*																			   *
*******************************************************************************/

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>


/************************Helpers***********************************************/
static int *BinaryRecursiveIMP(int key, int * arr_start, int *end);

/* merge two sorted arr to one in dest */
void MergeIMP(int *src1_start, int *src1_end, int *src2_start, int *src2_end, int *dest);

/* recursive merge sort */
void MergeSortIMP(int *arr_to_sort, size_t size, int *work_arr);

void MergeIMP();

/* devides the array into two partitions, 
 * and finds the pivot position within the partitions */
int *PartitionIMP(int *start, int *end);

/************************Binary Search**************************************/

/*---- Iterative integers BS-----*/
int *BinarySearchIter(int arr[], size_t size, int key)
{
    /* set start, mid, end ptrs */
    int * start = arr;
    int * end = arr + size;
    int * mid = NULL;

    assert(arr);

    /* while start < end */
    while (start < end)
    {
        /* set mid to point to the midle element: start + (end - start)/2 */
        mid = start + (end - start)/2;

        /* compare to the key to mid element, if found, return mid */
        if(key == *mid)
        {
            return mid;
        }

        /* if the key is smaller than mid */
        if(key < *mid)
        {
            /* search the left half (end = mid)*/
            end = mid;
        }

        /* if the key is bigger than mid */
        else if(key > *mid)
        {
            /* search the right half (start = mid + 1)*/
            start = mid + 1;
        }
    }

    /* if not found, return NULL */
    return NULL;
}


/*----Recursive integers BS-----*/
int *BinarySearchRec(int arr[], size_t size, int key)
{
    return BinaryRecursiveIMP(key, arr, arr + size);
}

static int *BinaryRecursiveIMP(int key, int *arr_start, int *end)
{
    int *mid = NULL;

    /* if start >= end, the key not found, return NULL */
    if(arr_start >= end)
    {
        return NULL;
    }

    /* set mid pointer to the middle element of arr */
    mid = arr_start + (end - arr_start)/2;

    /* if key == mid, return mid */
    if (key == *mid)
    {
        return mid;
    }

    /* if key < mid, search the left array half */
    if(key < *mid)
    {
        return BinaryRecursiveIMP(key, arr_start, mid);
    }

    /* if key > mid, search the right array half */
    return BinaryRecursiveIMP(key, mid + 1, end);
}

/*----Recursive generic BS-----*/
void *GenericBS(void *arr, size_t nmemb, size_t elem_size,
                int (*compar)(const void *, const void *), void *key)
{
    size_t offset = nmemb * elem_size;
    void *end = (char *)arr + offset;
    /*note: using offset on mid calc caused a fail!! since flooring was on wrong value*/
    void *mid = (char *)arr + (nmemb/ 2) * elem_size; 
    int cmp = 0;

    if(arr >= end)
    {
        return NULL;
    }

    cmp = compar(key, mid);

    if(cmp == 0)
    {
        return mid;
    }

    if(cmp < 0)
    {
        printf("left %ld\n", ((char *)mid - (char *)arr)/elem_size);
        return GenericBS(arr, ((char *)mid - (char *)arr)/elem_size,
                     elem_size, compar, key);
    }
    printf("right %ld\n", ((char *)end - (char *)mid - elem_size)/elem_size);

    return GenericBS((char *)mid + elem_size, ((char *)end - (char *)mid - elem_size)/elem_size, 
                      elem_size, compar, key);

}

/************************Merge Sort******************************************/


void MergeSortIMP(int *arr_to_sort, size_t size, int *work_arr)
{
    /* if size <= 1 return arr_to_sort */

    /* mid = arr_to_sort + size/2 */

    /* MergeSort(arr_to_sort, size/2) */
    /* MergeSort(mid, size - size/2) */

    /*MergeIMP two arrays */

}

/************************Quick Sort******************************************/

void Qsort(int arr[], size_t size)
{
    /* set start and end(last valid) pointers */
    /* if start >= end, return */

    /* find pivot position and devide the array to 2 parts: 
     * less than pivot and grater than pivot */
    /* pivot is the number I want to find a position for */
    /* pivot = partition(start, end)*/

    /* sort the left partition (start to pivot)*/
    /* sort the right partitio (pivot +1 to end)*/

}



int *PartitionIMP(int *start, int *end)
{
    /* draw a random idx to choose a pivot */
    /* set pivot as pointer to that index */

    /* set last_smaller  ptr to start */
    /* set curr ptr to start*/

    /* while curr <= end */
        /* if curr < pivot */
            /* swap curr with last_smaller + 1 values */
            /* incr last_smaller*/
        /* incr current */

    /* swap the pivot with the element located after the last_smaller */
    /* return pointer to pivot */

}


