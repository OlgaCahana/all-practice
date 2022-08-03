/*******************************************************************************
*	Written by:		Olga Danielle Cahana									   *
*	Date:			02/01/2022												   *
*	Reviewed by:	Shulamit						    				 	   *
*																			   *
*******************************************************************************/
#include <stdio.h> /* printf */ 
#include <stddef.h> /* size_t, sizeof */

#include "sorted_list.h"

#define UNUSED(param) ((void)param)
/****************Tests declarations********************************************/
static void Scenario_1_Tests(void);
static void Scenario_2_Tests(void);
static void FindIfFind_Tests(void);
static void Merge_Test(void);


/*********************Helpers declarations*************************************/
/* according to Find prototype */
static int CompareInt(const void *param1, const void *param2);

/* according to Find prototype: returns 0 if number is even */
static int IsEven(const void *param1, void *param2);

/* print all list nodes data, integers only */
void PrintListOfInts(sortlist_ty *list);

/* print int list (to be used with foreach) */
static int PrintInt(void *data, void *param);


/******************************Main********************************************/
int main(void)
{
	Scenario_1_Tests();
	Scenario_2_Tests();
	FindIfFind_Tests();
	Merge_Test();

	return 0;
}

/***********************Tests Implementation***********************************/
static void Scenario_1_Tests(void)
{
	sortlist_ty *list = NULL;
	srt_iter_ty start_iter;
	srt_iter_ty end_iter;
	srt_iter_ty inserted;


	int data1 = 10;

	cmp_func_ty compare_func = CompareInt;

	printf("Starting scenario1 tests:\n");
	/* Create new sorted list */
	list =  SortedListCreate(compare_func);	
	list != NULL ?
			printf("New sorted list created. \t\tTest Passed\n\n") :
			printf("Failed to create new list. \t\tTest Failed!!\n");

	/* Count elements */
	SortedListSize(list) == 0 ?
			printf("Counted 0 nodes in sorted list. \tTest Passed\n") :
			printf("Wrong count. \t\tTest Failed!!\n");

	/* Check if empty */
	SortedListIsEmpty(list) ?
			printf("The list is empty. \t\t\tTest Passed\n") :
			printf("The list is not empy. \tTest Failed!!\n");


	/* Get an iterators to beginning and end */
	start_iter = SortedListBegin(list);
	end_iter = SortedListEnd(list);

	SortedListGetData(end_iter) == SortedListGetData(start_iter) ?
			printf("Get iterator to end.\t\t\tTest Passed\n") : 
			printf("Get iterator to end.\t\t\tTest Failed!!\n");

	/* Check if end iterator is equal to beginning iterator */
	SortedListIsSameIter(start_iter, end_iter) ?
			printf("End iter is equal to start. \t\tTest Passed\n") :
			printf("Not equal. \t\t\tTest Failed!\n");

	/* Insert first element */
	inserted = SortedListInsert(list, &data1);
	printf("\nFirst node inserted to sorted list.\n\n");

	/* update start/end iterators after insert */
	start_iter = SortedListBegin(list);
	end_iter = SortedListEnd(list);

	/* Check if empty */
	!SortedListIsEmpty(list) ?
			printf("The list is not empty. \t\t\tTest Passed\n") :
			printf("The list is empy. \t\tTest Failed!!\n");

	/* Count elements */
	SortedListSize(list) == 1 ?
			printf("Counted 1 node in sorted list. \t\tTest Passed\n") :
			printf("Wrong count. \t\tTest Failed!!\n");

	/* Get data */
	*(int *)(SortedListGetData(inserted)) == data1 ?
		printf("The data value is correct. \t\tTest Passed\n") :
		printf("Incorrect data value. \t\tTest Failed!!\n");

	/* Get iterator to next node.*/
	SortedListIsSameIter(SortedListNext(start_iter), end_iter) ?
			printf("Get iterator to next \t\t\tTest Passed\n") : 
			printf("Get iterator to next.\t\tTest Failed!!\n");

	/* Get iterator to prev node.*/
	SortedListIsSameIter(SortedListPrev(end_iter), inserted) ?
			printf("Get iterator to prev \t\t\tTest Passed\n") : 
			printf("Get iterator to prev.\t\tTest Failed!!\n");

	/* Remove the last element */
	SortedListIsSameIter(SortedListRemove(start_iter), end_iter) ?
			printf("Node removed \t\t\t\tTest Passed\n") :
			printf("Remove failed \t\t\t\tTest Failed");

	/* Count elements */
	SortedListSize(list) == 0 ?
			printf("Counted 0 nodes in sorted list. \tTest Passed\n") :
			printf("Wrong count. \t\tTest Failed!!\n");

	/* Check if empty */
	SortedListIsEmpty(list) ?
			printf("The list is empty. \t\t\tTest Passed\n") :
			printf("The list is not empy. \tTest Failed!!\n");

	/* Destroy the list */
	printf("Destroying list.\n\n");
	SortedListDestroy(list); 
}
 
static void Scenario_2_Tests(void)
{
	sortlist_ty *list = NULL;
	srt_iter_ty start_iter;

	int data1 = 10;
	int data2 = -6;
	int data3 = 7;
	int data4 = 2;

	cmp_func_ty compare_func = CompareInt;

	printf("Starting scenario2 tests:\n");
	/* Create new sorted list */
	list =  SortedListCreate(compare_func);	
	list != NULL ?
			printf("New sorted list created. \t\tTest Passed\n\n") :
			printf("Failed to create new list. \t\tTest Failed!!\n");

	/* Insert elements */
	SortedListInsert(list, &data1);
	SortedListInsert(list, &data2);
	SortedListInsert(list, &data3);
	SortedListInsert(list, &data4);
	printf("Four nodes inserted to sorted list.\n\n");

	/* update start/end iterators after insert */
	start_iter = SortedListBegin(list);

	/*expected order: data2 = -6, data4 = 2, data3 = 7, data1 = 10 */
	*(int *)(SortedListGetData(start_iter)) == data2 ?
		printf("The data value is correct: %d \t\tTest Passed\n",
										 *(int *)(SortedListGetData(start_iter))) :
		printf("Incorrect data value. \t\tTest Failed!!\n");
	start_iter = SortedListNext(start_iter);

	*(int *)(SortedListGetData(start_iter)) == data4 ?
		printf("The data value is correct: %d \t\tTest Passed\n",
										 *(int *)(SortedListGetData(start_iter))) :
		printf("Incorrect data value. \t\tTest Failed!!\n");
	start_iter = SortedListNext(start_iter);

	*(int *)(SortedListGetData(start_iter)) == data3 ?
		printf("The data value is correct: %d \t\tTest Passed\n",
										 *(int *)(SortedListGetData(start_iter))) :
		printf("Incorrect data value. \t\tTest Failed!!\n");
	start_iter = SortedListNext(start_iter);

	*(int *)(SortedListGetData(start_iter)) == data1 ?
		printf("The data value is correct: %d \t\tTest Passed\n",
										 *(int *)(SortedListGetData(start_iter))) :
		printf("Incorrect data value. \t\tTest Failed!!\n");
	start_iter = SortedListNext(start_iter);

	/* Count elements */
	SortedListSize(list) == 4 ?
			printf("Counted 4 nodes in sorted list. \tTest Passed\n") :
			printf("Wrong count. \t\tTest Failed!!\n");

	/* Print the list with foreach */
	printf("Print the sorted list with ForEach:\n");
	PrintListOfInts(list);

	/* Remove the last element */
	*(int *)SortedListPopBack(list) == data1 ?
			printf("Last node popped \t\t\tTest Passed\n") :
			printf("Pop last incorrect value \t\tTest Failed\n"); 

	/* Count elements */
	SortedListSize(list) == 3 ?
			printf("Counted 3 nodes in sorted list. \tTest Passed\n") :
			printf("Wrong count. \t\tTest Failed!!\n");

	/* Remove the last element */
	*(int *)SortedListPopFront(list) == data2 ?
			printf("First node popped \t\t\tTest Passed\n") :
			printf("Pop first incorrect value \t\tTest Failed\n"); 

	/* Count elements */
	SortedListSize(list) == 2 ?
			printf("Counted 2 nodes in sorted list. \tTest Passed\n") :
			printf("Wrong count. \t\tTest Failed!!\n");

	/* update start/end iterators after insert */
	start_iter = SortedListBegin(list);

	/* Print the list with foreach */
	printf("Print the sorted list with ForEach:\n");
	PrintListOfInts(list);

	/* Destroy the list */
	printf("Destroying list.\n\n");
	SortedListDestroy(list); 
}
 
static void FindIfFind_Tests(void)
{
	sortlist_ty *list = NULL;
	srt_iter_ty start_iter;
	srt_iter_ty end_iter;
	srt_iter_ty result;


	int data1 = 10;
	int data2 = -5;
	int data3 = 7;
	int data4 = 2;
	int data5 = 20;
	int data6 = -20;

	cmp_func_ty compare_func = CompareInt;
	match_func_ty match_func = IsEven;

	printf("Starting FindIf & Find tests:\n");
	/* Create new sorted list */
	list =  SortedListCreate(compare_func);	
	list != NULL ?
			printf("New sorted list created. \t\tTest Passed\n\n") :
			printf("Failed to create new list. \t\tTest Failed!!\n");

	/* Insert elements */
	SortedListInsert(list, &data1);
	SortedListInsert(list, &data2);
	SortedListInsert(list, &data3);
	SortedListInsert(list, &data4);
	printf("Four nodes inserted to sorted list.\n\n");

	/* update start/end iterators after insert */
	start_iter = SortedListBegin(list);
	end_iter = SortedListEnd(list);

	/*find first even number using FindIf */
	printf("Find first even number in the list:\n");
	result = SortedListFindIf(start_iter, end_iter, match_func, NULL);
	*(int *)(SortedListGetData(result)) == data4 ?
		printf("Found data value is correct: %d \t\tTest Passed\n",
										 *(int *)(SortedListGetData(result))) :
		printf("Incorrect data value. \t\tTest Failed!!\n");

	/* find 7 ising Find (located in the middle of sorted list) */
	result = SortedListFind(list, start_iter, end_iter, &data3);
	*(int *)(SortedListGetData(result)) == data3 ?
		printf("Found data value is correct: %d \t\tTest Passed\n",
										 *(int *)(SortedListGetData(result))) :
		printf("Found Incorrect data value. \t\tTest Failed!!\n");

	/* find 20 using Find (not in the list) */
	result = SortedListFind(list, start_iter, end_iter, &data5);
	SortedListIsSameIter(result, end_iter) ?
		printf("The value is not in the list \t\tTest Passed\n") :								
		printf("Found Incorrect data value. \t\tTest Failed!!\n");

	/* find -5 using Find (first element in the list) */
	result = SortedListFind(list, start_iter, end_iter, &data2);
	*(int *)(SortedListGetData(result)) == data2 ?
		printf("Found data value is correct: %d \tTest Passed\n",
										 *(int *)(SortedListGetData(result))) :
		printf("Found Incorrect data value. \t\tTest Failed!!\n"); 

	/* find -20 using Find (not in the list) */
	result = SortedListFind(list, start_iter, end_iter, &data6);
	SortedListIsSameIter(result, end_iter) ?
		printf("The value is not in the list \t\tTest Passed\n") :								
		printf("Found Incorrect data value. \t\tTest Failed!!\n");
	
	SortedListDestroy(list);
}

static void Merge_Test(void)
{
	sortlist_ty *list1 = NULL;
	sortlist_ty *list2 = NULL;

	int data1 = 10;
	int data2 = -5;
	int data3 = 7;
	int data4 = 2;
	int data5 = -6;
	int data6 = 20;
	int data7 = 9;

	cmp_func_ty compare_func = CompareInt;

	printf("\nStarting Merge tests:\n");
	/* Create new sorted list1 */
	list1 =  SortedListCreate(compare_func);	
	list1 != NULL ?
			printf("New sorted list1 created. \t\tTest Passed\n") :
			printf("Failed to create new list. \t\tTest Failed!!\n");

	/* Create new sorted list2 */
	list2 =  SortedListCreate(compare_func);	
	list2 != NULL ?
			printf("New sorted list2 created. \t\tTest Passed\n\n") :
			printf("Failed to create new list. \t\tTest Failed!!\n");

	/* Insert elements to list1 */
	SortedListInsert(list1, &data1);
	SortedListInsert(list1, &data2);
	SortedListInsert(list1, &data3);
	SortedListInsert(list1, &data4); 
	printf("Four nodes inserted to sorted list1:\n");
	PrintListOfInts(list1);

	/* Insert elements to list2 */
	SortedListInsert(list2, &data5);
	SortedListInsert(list2, &data3);
	SortedListInsert(list2, &data6);
	SortedListInsert(list2, &data7);
	printf("Four nodes inserted to sorted list2:\n");
	PrintListOfInts(list2);
	
	/* Print the merged list with foreach */
	printf("Print the merged sorted list:\n");
	PrintListOfInts(SortedListMerge(list1, list2));
	
	/* Check if list2 is empty */
	SortedListIsEmpty(list2) ?
			printf("The list2 is empty. \t\t\tTest Passed\n") :
			printf("The list2 is not empy. \tTest Failed!!\n"); 

	/* Merge an empty list */
	printf("Merge an empty list to nonempty:\n");
	PrintListOfInts(SortedListMerge(list1, list2));

	/* Merge nonempty list to empty */
	printf("Merge nonempty list to empty:\n");
	PrintListOfInts(SortedListMerge(list2, list1));

	SortedListDestroy(list1);
	SortedListDestroy(list2);
}
/****************************Helpers Implementation****************************/
/* print all list nodes data, integers only */
void PrintListOfInts(sortlist_ty *list)
{
	srt_iter_ty begin = SortedListBegin(list);
	srt_iter_ty end = SortedListEnd(list);

	op_func_ty print = PrintInt;

	SortedListForEach(begin, end, print, NULL);
	printf("\n");
}

/* print int list (to be used with foreach) */
static int PrintInt(void *data, void *param)
{
	UNUSED(param);

	printf("%d ",*(int *)data);
	return 0;
}

/*0 if equal, 0> if data1 lower then data2, 0< if data1 higher then data2*/
static int CompareInt(const void *data1, const void *data2)
{
	return (*(int *)data1 - *(int *)data2);
}

/* return 0 if the integer is an even number, 1 otherwise */
static int IsEven(const void *param1, void *param2)
{
	UNUSED(param2);
	return (*(int *)param1 % 2 != 0);
}
