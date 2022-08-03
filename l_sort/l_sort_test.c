/*******************************************************************************
*	Written by:		Olga Danielle Cahana									   *
*	Date:			15/2/2022												   *
*	Reviewed by:							    					 	   *
*																			   *
*******************************************************************************/
#include <stdio.h> /* printf */ 
#include <stddef.h> /* size_t, sizeof */
#include <stdlib.h> /* rand, srand, qsort */
#include <time.h> /* time */
#include <string.h> /* memcpy, memcmp */

#include "l_sort.h"

#define TEST_SIZE 5000
#define RANGE_SET 1000
#define SHIFTL 1

/****************Tests declarations********************************************/
static void Scenario_1_Tests(void);


/*********************Helpers declarations*************************************/
void PrintArr(int *arr, size_t size);
static int Comparator(const void *first_, const void *second_);
/******************************Main********************************************/
int main(void)
{

	Scenario_1_Tests(); 


	return 0;
}

/***********************Tests Implementation***********************************/

static void Scenario_1_Tests(void)
{
	int i = 0;
	clock_t start_t = 0, end_t = 0;

	int test_arr1[TEST_SIZE] = {0}; /* to be sorted with count*/
	int test_arr2[TEST_SIZE] = {0}; /* to be sorted with radix*/
	int test_arr3[TEST_SIZE] = {0}; /*will be sorted with qsort*/

	int dest1[TEST_SIZE] = {0};
	int dest2[TEST_SIZE] = {0};

	size_t histogram[1024] = {0};


	/* fill test_arr1 with random numbers within the range of [0, RANGE_SET) */
	srand(time(NULL));

	for(i = 0; i < TEST_SIZE; ++i)
	{
		test_arr1[i] = rand() % RANGE_SET * SHIFTL;
	}

	/* duplicate the random array to be tested with each sorting algorithm */
	memcpy(test_arr2, test_arr1, TEST_SIZE * sizeof(int));
	memcpy(test_arr3, test_arr1, TEST_SIZE * sizeof(int));



	/* perform benchmmark analysis for each algorithm */
	printf("Running benchmark on array of size %d\n", TEST_SIZE );
	printf("Tested array values range is [%d, %d)\n", 0, RANGE_SET);

	PrintArr(test_arr1, TEST_SIZE); 
	printf("\n\n");

	start_t = clock();
	CountSort(test_arr1, dest1, TEST_SIZE, 0, 10, histogram);
	end_t = clock();
	printf("Time taken by Count Sort: %ld\n", end_t - start_t);
	PrintArr(dest1, TEST_SIZE); 

	start_t = clock();
	RadixSort(test_arr2, dest2, TEST_SIZE, 0, 3, 10, histogram);
	end_t = clock();
	printf("Time taken by Radix Sort: %ld\n", end_t - start_t);
	PrintArr(dest2, TEST_SIZE);


	start_t = clock();
	qsort(test_arr3, TEST_SIZE, sizeof(int), Comparator);
	end_t = clock();
	printf("Time taken by Quick Sort: %ld\n", end_t - start_t);
	PrintArr(test_arr3, TEST_SIZE); 
	printf("\n\n");

	/* compare each algorithm output with qsort output, for sorting validation */
	memcmp(dest1, test_arr3, TEST_SIZE) == 0 ?
		printf("Count sort \tTest Passed\n") :
		printf("Count sort \tTest Failed\n");

	/* compare each algorithm output with qsort output, for sorting validation */
	memcmp(dest2, test_arr3, TEST_SIZE) == 0 ?
		printf("Radix sort \tTest Passed\n") :
		printf("Radix sort \tTest Failed\n");

}

/****************************Helpers Implementation****************************/
void PrintArr(int *arr, size_t size)
{
	size_t i = 0;

	for(i=0; i < size; ++i)
	{
		printf("%d ", arr[i]);
	}
	printf("\n\n");
}

static int Comparator(const void *first_, const void *second_)
{
	return *(int *)first_ - *(int *)second_; /* <0: first goes before second */
}