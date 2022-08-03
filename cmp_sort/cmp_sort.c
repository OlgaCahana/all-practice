/*******************************************************************************
*	Written by:		Olga Danielle Cahana									   *
*	Date:			1/2/2022												   *
*	Reviewed by:	Gabriel						    					 	   *
*																			   *
*******************************************************************************/
#include <stddef.h>
#include <assert.h>

#include "cmp_sort.h"

enum bool_e{FALSE = 0, TRUE = 1};
/******************************Helpers*****************************************/
void Swap(int *x, int *y);
int *FindMin(int *start, int *end);

/**************************Implementation**************************************/
/*TODO: add static and IMP to helper functions */
/*TODO: add _ to function parameters */
/*TODO: replace #define with enums */
/*TODO:*/

void InsertionSort(int *arr, size_t size)
{
    int *unsorted_start = arr + 1;
    int *arr_last = arr + size - 1;

    assert(arr);

    /* while unsorted_start <= arr_last */
    for(unsorted_start = arr + 1; unsorted_start <= arr_last; ++unsorted_start)
    {
        int key_to_insert = *unsorted_start;
        int *curr = unsorted_start - 1;

        /* find the right place to insert the key_to_insert element */
        while (curr >= arr && *curr > key_to_insert)
        {
            /* shift right all elements bigger than the key 
             * to make place for inserting the key */
            *(curr + 1) = *curr;
            --curr;      
        }
        /* insert the key_to_insert to the right place */
        *(curr + 1) = key_to_insert;
    }
}



void SelectionSort(int *arr, size_t size)
{
    int *unsorted_start = arr;
    int *arr_last = arr + size - 1;

    assert(arr);

    /* foreach element in unsorted subarray */
    while(unsorted_start < arr_last)
    {
        /* find the min element in unsorted subarray */
        int *min = FindMin(unsorted_start, arr_last);
                        
        /* swap the found min with the unsorted_start */
        Swap(min, unsorted_start);
        ++unsorted_start;
    }

}


void BubbleSort(int *arr, size_t size)
{
    int *unsorted_last = arr + size - 1;
    int swapped = TRUE;

    assert(arr);
    assert(size > 0);

    /* while unsorted_last != start and swapped = true */
    for(; (unsorted_last != arr) && (swapped = TRUE); --unsorted_last)
    {
        int *curr = arr;
        swapped = FALSE;

        /* bubble current max value to the top */
        while(curr != unsorted_last)
        {
            if(*curr > *(curr + 1))
            {
                Swap(curr, curr + 1);
                swapped = TRUE;
            }
            ++curr;
        }        
    }
}

void BubbleSortOpt(int *arr, size_t size)
{
    int *unsorted_last = arr + size - 1;

    assert(arr);

    /* while unsorted_last != start */
    while(unsorted_last != arr)
    {
        int *curr = arr;
        int *new_unsorted_last = arr;

        /* bubble current max value to the top */
        while(curr != unsorted_last)
        {
            if(*curr > *(curr + 1))
            {
                Swap(curr, curr + 1);
                new_unsorted_last = curr;
            }
            ++curr;
        }
        /* Since all elements after the last swap are sorted,
         * set the unsorted_last to the last element swapped */
        unsorted_last = new_unsorted_last;        
    }
}

/*************************Helpers Implementation*******************************/
void Swap(int *x, int *y)
{
	int temp;

    assert(x);
    assert(y);

	temp = *x;
	*x = *y;
	*y = temp;
}

int *FindMin(int *start, int *end)
{
    int *min = start;
    int *curr = start + 1;

    assert(start);
    assert(end);

    while(curr <= end)
    {
        if(*curr < *min)
        {
            min = curr;
        }
        ++curr;
    }
    return min;
}