/*******************************************************************************
*	Written by:		Olga Danielle Cahana									   *
*	Date:			1/2/2022												   *
*	Reviewed by:	Gabriel						    					 	   *
*																			   *
*******************************************************************************/
#include <stdio.h> /* printf */ 
#include <stddef.h> /* size_t, sizeof */
#include <stdlib.h> /* rand, srand, qsort */
#include <time.h> /* time */
#include <string.h> /* memcpy, memcmp */

#include "cmp_sort.h"

#define TEST_SIZE 5000
#define RANGE_SET 50

/****************Tests declarations********************************************/
static void Scenario_1_Tests(void);
static void Scenario_2_Tests(void);


/*********************Helpers declarations*************************************/
void PrintArr(int *arr, size_t size);
static int Comparator(const void *first_, const void *second_);
/******************************Main********************************************/
int main(void)
{
	Scenario_1_Tests();
	Scenario_2_Tests();


	return 0;
}

/***********************Tests Implementation***********************************/
static void Scenario_1_Tests(void)
{
	int arr1[10] = {6,2,23,7,8,1,1,0,6,12};
	int arr2[10] = {6,2,23,7,8,1,1,0,6,12};
	int arr3[10] = {6,2,23,7,8,1,1,0,6,12};
	int arr4[10] = {6,2,23,7,8,1,1,0,6,12};

	PrintArr(arr1, 10);

	InsertionSort(arr1, 10);
	PrintArr(arr1, 10);
	
	SelectionSort(arr2, 10);
	PrintArr(arr2, 10);

	BubbleSort(arr3, 10);
	PrintArr(arr3, 10);

	BubbleSortOpt(arr4, 10);
	PrintArr(arr4, 10);

}
 
static void Scenario_2_Tests(void)
{
	int i = 0;
	clock_t start_t = 0, end_t = 0;

	int *test_arr1 = (int *)malloc(TEST_SIZE * sizeof(int));
	int *test_arr2 = (int *)malloc(TEST_SIZE * sizeof(int));
	int *test_arr3 = (int *)malloc(TEST_SIZE * sizeof(int));
	int *test_arr4 = (int *)malloc(TEST_SIZE * sizeof(int));
	int *test_arr5 = (int *)malloc(TEST_SIZE * sizeof(int));

	/* fill test_arr1 with random numbers within the range of [0, RANGE_SET) */
	srand(time(NULL));

	for(i = 0; i < TEST_SIZE; ++i)
	{
		test_arr1[i] = rand() % RANGE_SET;
	}

	/* duplicate the random array to be tested with each sorting algorithm */
	test_arr2 = memcpy(test_arr2, test_arr1, TEST_SIZE * sizeof(int));
	test_arr3 = memcpy(test_arr3, test_arr1, TEST_SIZE * sizeof(int));
	test_arr4 = memcpy(test_arr4, test_arr1, TEST_SIZE * sizeof(int));
	test_arr5 = memcpy(test_arr5, test_arr1, TEST_SIZE * sizeof(int));



	/* perform benchmmark analysis for each algorithm */
	printf("Running benchmark on array of size %d\n", TEST_SIZE );
	printf("Tested array values range is [%d, %d)\n", 0, RANGE_SET);

	printf("\n\n");

	start_t = clock();
	InsertionSort(test_arr1, TEST_SIZE);
	end_t = clock();
	printf("Time taken by Insertion Sort: %ld\n", end_t - start_t);
	PrintArr(test_arr1, TEST_SIZE);

	start_t = clock();
	SelectionSort(test_arr2, TEST_SIZE);
	end_t = clock();
	printf("Time taken by Selection Sort: %ld\n", end_t - start_t);


	start_t = clock();
	BubbleSort(test_arr3, TEST_SIZE);
	end_t = clock();
	printf("Time taken by Bubble Sort: %ld\n", end_t - start_t);

	start_t = clock();
	BubbleSortOpt(test_arr4, TEST_SIZE);
	end_t = clock();
	printf("Time taken by BubbleOpt Sort: %ld\n", end_t - start_t);

	start_t = clock();
	qsort(test_arr5, TEST_SIZE, sizeof(int), Comparator);
	end_t = clock();
	printf("Time taken by Quick Sort: %ld\n", end_t - start_t);

	printf("\n\n");

	/* compare each algorithm output with qsort output, for sorting validation */
	memcmp(test_arr1, test_arr5, TEST_SIZE) == 0 ?
		printf("Insertion sort \tTest Passed\n") :
		printf("Insertion sort Test Failed\n");

	memcmp(test_arr1, test_arr5, TEST_SIZE) == 0 ?
		printf("Selection sort \tTest Passed\n") :
		printf("Selection sort Test Failed\n");

	memcmp(test_arr1, test_arr5, TEST_SIZE) == 0 ?
		printf("Bubble sort \tTest Passed\n") :
		printf("Bubble sort \tTest Failed\n");

	memcmp(test_arr1, test_arr5, TEST_SIZE) == 0 ?
		printf("BubbleOpt sort \tTest Passed\n") :
		printf("BubbleOpt sort \tTest Failed\n");
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