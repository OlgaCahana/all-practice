/*******************************************************************************
*	Written by:		Olga Danielle Cahana									   *
*	Date:			3/2/2022												   *
*	Reviewed by:	Daniel						    					 	   *
*																			   *
*******************************************************************************/
#include <stdio.h> /* printf */ 
#include <stddef.h> /* size_t, sizeof */
#include <stdlib.h> /* */
#include <assert.h>

#include "sorts.h"


/****************Tests declarations********************************************/
static void BinarySearch_Tests(void);
void BinarySearchRecGenericTest();

static void Sorts_Tests(void); 


typedef struct cat
{
    int m_stupidity_level;
    int m_weight;
    char *m_name;
} cat_ty;

enum arr_size {ARR_SIZE = 10, CATS_NUM = 19};
/*********************Helpers declarations*************************************/
static cat_ty CreateCat(int stupidity_level_, int weight_, char *name_);
static int CmpStupider(const void *cat1_, const void *cat2_);
static void PrintCatsArr(cat_ty *cats_arr_, size_t size_);

static void PrintArr(int *arr_, size_t size_);

/******************************Main********************************************/
int main(void)
{
	BinarySearch_Tests();
    BinarySearchRecGenericTest();




	return 0;
}

/***********************Tests Implementation***********************************/
static void BinarySearch_Tests(void)
{
	int arr[] = {1, 4, 7, 34, 58, 64, 99};
    size_t size_arr = sizeof(arr)/sizeof(int);
    
    printf("given - %d, answer %d\n", 7, *(BinarySearchIter(arr, size_arr, 7)));


    printf("Binary Search Iterative: %s\n", 
    (BinarySearchIter(arr, size_arr, 34) == &arr[3]) &&
    (BinarySearchIter(arr, size_arr, 1) == &arr[0]) &&
    (BinarySearchIter(arr, size_arr, 99) == &arr[6]) &&
    (BinarySearchIter(arr, size_arr, 55) == NULL) ? "SUCCESS" : "FAIL");


	printf("given - %d, answer %d\n", 7, *(BinarySearchRec(arr, size_arr, 7)));

    printf("Binary Search Recursive: %s\n", 
    (BinarySearchRec(arr, size_arr, 34) == &arr[3]) &&
    (BinarySearchRec(arr, size_arr, 1) == &arr[0]) &&
    (BinarySearchRec(arr, size_arr, 99) == &arr[6]) &&
    (BinarySearchRec(arr, size_arr, 55) == NULL) ? "SUCCESS" : "FAIL");
}

void BinarySearchRecGenericTest()
{
	cat_ty arr[6];
    cat_ty cat = CreateCat(65, 20, "ru");

    arr[0] = CreateCat(8, 12, "Chicko");
    arr[1] = CreateCat(10, 7, "Josh");
    arr[2] = CreateCat(20, 5, "Charlie");
    arr[3] = CreateCat(26, 11, "Lilo");
    arr[4] = CreateCat(40, 8, "Raul");
    arr[5] = CreateCat(74, 15, "Balu");

    puts("\n **BinarySearchRecTest **");
    puts("Original array:");
    PrintCatsArr(arr, 6);

    printf("Binary Search Recursive: %s\n", 
    (GenericBS(arr, 6, sizeof(cat_ty),
                  CmpStupider, &arr[0]) == &arr[0]) ? "SUCCESS" : "FAIL");
	printf("Binary Search Recursive: %s\n",
    (GenericBS(arr, 6, sizeof(cat_ty),
                  CmpStupider, &arr[1]) == &arr[1]) ? "SUCCESS" : "FAIL");
	printf("Binary Search Recursive: %s\n",
    (GenericBS(arr, 6, sizeof(cat_ty),
                  CmpStupider, &arr[4]) == &arr[4]) ? "SUCCESS" : "FAIL");
	printf("Binary Search Recursive: %s\n",
    (GenericBS(arr, 6, sizeof(cat_ty),
                  CmpStupider, &cat) == NULL) ? "SUCCESS" : "FAIL");

}

/****************************Helpers Implementation****************************/
static int Comparator(const void *first_, const void *second_)
{
	return *(int *)first_ - *(int *)second_; /* <0: first goes before second */
}

static cat_ty CreateCat(int stupidity_level_, int weight_, char *name_)
{
    cat_ty cat ={0};

    cat.m_stupidity_level = stupidity_level_;
    cat.m_weight = weight_;
    cat.m_name = name_;

    return cat;
}


static int CmpStupider(const void *cat1_, const void *cat2_)
{
    return ((cat_ty *)cat1_)->m_stupidity_level
             - ((cat_ty *)cat2_)->m_stupidity_level;
}


static void PrintCatsArr(cat_ty *cats_arr_, size_t size_)
{
    cat_ty *curr = cats_arr_;

    printf("[");
    for(     ; curr != cats_arr_ + size_ ; ++curr  )
    {
        printf("%d, ", curr->m_stupidity_level);
    }
    printf("end]\n");       
}


static void PrintArr(int *arr_, size_t size_)
{
    int *curr = arr_;

    printf("[");
    for(     ; curr != arr_ + size_ ; ++curr  )
    {
        printf(" %d", *curr);
    }
    printf(" ]\n");
}
