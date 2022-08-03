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

#include "btset.h"

enum {ARR_SIZE = 10};
/****************Tests declarations********************************************/
static void Scenario_1_Tests_Insert_Find(void);
static void Scenario_2_Tests_Iterators(); 



/*********************Helpers declarations*************************************/

static int CompareInt(const void *elem1, const void *elem2, const void *param);
static void PrintArrIMP(int *arr, size_t size);
static void PrintSetSortedIMP(btset_ty *set);
static void PrintBackwardsIMP(btset_ty *set_);
/******************************Main********************************************/
int main(void)
{
	Scenario_1_Tests_Insert_Find();
	Scenario_2_Tests_Iterators(); 


	return 0;
}

/***********************Tests Implementation***********************************/
static void Scenario_1_Tests_Insert_Find(void)
{
	btset_ty *my_set = NULL;
	btset_iter_ty inserted_iter;
	btset_iter_ty next2removed_iter;
	btset_iter_ty find_iter;

	int data_arr1[4] = {6,2,23,7};
	bts_cmp_fnc_ty cmp_func = CompareInt;

	printf("Starting scenarion 1:\n");

	/* create new set */
	my_set = BTSetCreate(cmp_func, NULL);
	my_set != NULL ?
		printf("New sorted set created. \t\tTest Passed\n\n") :
		printf("Failed to create new set. \t\tTest Failed!!\n");

	/* Check if empty */
	BTSetIsEmpty(my_set) == 1 ?
			printf("The set is empty. \t\t\tTest Passed\n") :
			printf("The set is not empy. \tTest Failed!!\n");

	/* Count elements */
	BTSetSize(my_set) == 0 ?
			printf("Counted 0 nodes in my_set. \t\tTest Passed\n") :
			printf("Wrong count. \t\tTest Failed!!\n");

/*-------------------     Inserting Elements     --------------------------------*/
	/* Insert first element */
	inserted_iter = BTSetInsert(my_set, &data_arr1[0]);

	/* Check if empty */
	BTSetIsEmpty(my_set) == 0 ?
			printf("The set is not empty. \t\t\tTest Passed\n") :
			printf("The set is empy. \tTest Failed!!\n");

	/* Check if the inserted data is correct */
	*(int *)BTSetGetData(inserted_iter) == data_arr1[0] ? 
			printf("Correct value inserted. \t\tTest Passed\n") :
			printf("Wrong inserted value. \tTest Failed!!\n");

	/* Count elements */
	BTSetSize(my_set) == 1 ?
			printf("Counted 1 nodes in my_set. \t\tTest Passed\n") :
			printf("Wrong count. \t\tTest Failed!!\n");

	/* Insert second element - left son to the root*/
	inserted_iter = BTSetInsert(my_set, &data_arr1[1]);

	/* Check if the inserted data is correct */
	*(int *)BTSetGetData(inserted_iter) == data_arr1[1] ? 
			printf("Correct value inserted. \t\tTest Passed\n") :
			printf("Wrong inserted value. \tTest Failed!!\n");

	/* Insert third element - right son to the root*/
	inserted_iter = BTSetInsert(my_set, &data_arr1[2]);

	/* Check if the inserted data is correct */
	*(int *)BTSetGetData(inserted_iter) == data_arr1[2] ? 
			printf("Correct value inserted. \t\tTest Passed\n") :
			printf("Wrong inserted value. \tTest Failed!!\n");

	/* Insert existind value - bad iterator expected */
	BTSetIsIterBad(BTSetInsert(my_set, &data_arr1[0])) ?
			printf("Bad iter for inserting dup value. \tTest Passed\n") :
			printf("Not a Bad iter. \t\t\tTest Failed\n");


/*-------------------        Find Elements     --------------------------------*/
	/* Find data from the root */
	find_iter = BTSetFind(my_set, &data_arr1[0]);

	/* Check if the found data is correct */
	*(int *)BTSetGetData(find_iter) == data_arr1[0] ? 
			printf("Correct value found. \t\t\tTest Passed\n") :
			printf("Value not found. \tTest Failed!!\n");

	/* Find data from root's left son */
	find_iter = BTSetFind(my_set, &data_arr1[1]);

	/* Check if the found data is correct */
	*(int *)BTSetGetData(find_iter) == data_arr1[1] ? 
			printf("Correct value found. \t\t\tTest Passed\n") :
			printf("Value not found. \t\tTest Failed!!\n");

	/* Find data from root's right son */
	find_iter = BTSetFind(my_set, &data_arr1[2]);

	/* Check if the found data is correct */
	*(int *)BTSetGetData(find_iter) == data_arr1[2] ? 
			printf("Correct value found. \t\t\tTest Passed\n") :
			printf("Value not found. \t\tTest Failed!!\n");


	/* Find nonexisting value - bad iterator expected */
	BTSetIsIterBad(BTSetFind(my_set, &data_arr1[3])) ?
			printf("Bad iter returned for not found value. \tTest Passed\n") :
			printf("Not a Bad iter. \t\t\tTest Failed\n");

	/* Count elements */
	BTSetSize(my_set) == 3 ?
			printf("Counted 3 nodes in my_set. \t\tTest Passed\n") :
			printf("Wrong count. \t\tTest Failed!!\n");	

	/*-------------------      Remove Elements   --------------------------------*/
	/* remove last(leaf) */
	next2removed_iter = BTSetRemove(my_set, inserted_iter);

	BTSetIsIterBad(next2removed_iter) ?
			printf("Bad iter for removing last node. \tTest Passed\n") :
			printf("Not a Bad iter. \t\t\tTest Failed\n");

	/* Count elements */
	BTSetSize(my_set) == 2 ?
			printf("Counted 2 nodes in my_set. \t\tTest Passed\n") :
			printf("Wrong count. \t\tTest Failed!!\n");	

	/* remove first (leaf) */
	next2removed_iter = BTSetRemove(my_set, BTSetBegin(my_set));
	
	/* Check if the next data is correct */
	*(int *)BTSetGetData(next2removed_iter) == data_arr1[0] ? 
			printf("Correct next value. \t\t\tTest Passed\n") :
			printf("Value not found. \t\tTest Failed!!\n");

	BTSetSize(my_set) == 1 ?
			printf("Counted 1 nodes in my_set. \t\tTest Passed\n") :
			printf("Wrong count. \t\tTest Failed!!\n");	

	/* remove root (leaf and last node in the set) */
	next2removed_iter = BTSetRemove(my_set, BTSetBegin(my_set));
	
	BTSetIsIterBad(next2removed_iter) ?
			printf("Bad iter for removing last node. \tTest Passed\n") :
			printf("Not a Bad iter. \t\t\tTest Failed\n");

	BTSetSize(my_set) == 0 ?
			printf("Counted 0 nodes in my_set. \t\tTest Passed\n") :
			printf("Wrong count. \t\tTest Failed!!\n");	

	/*----------------------------------------------------------------------------*/			
	BTSetDestroy(my_set);
}

 static void Scenario_2_Tests_Iterators(void)
{
	btset_ty *my_set = NULL;
	btset_iter_ty start_iter;
	btset_iter_ty end_iter;
	btset_iter_ty last_iter;
	btset_iter_ty inserted_iter;
	btset_iter_ty next2removed_iter;
	int i = 0;

	int data_arr1[ARR_SIZE] = {6,2,23,7,8,1,0,20,12,1};
	bts_cmp_fnc_ty cmp_func = CompareInt;

	printf("\nStarting scenarion 2:\n");

	/* create new set */
	my_set = BTSetCreate(cmp_func, NULL);
	my_set != NULL ?
		printf("New sorted set created. \t\tTest Passed\n\n") :
		printf("Failed to create new set. \t\tTest Failed!!\n");

	/* insert all the elements */
	for (i = 0; i < ARR_SIZE; ++i)
	{		
		BTSetInsert(my_set, &data_arr1[i]);
	}
	
	printf("inserting:\n");
	PrintArrIMP(data_arr1, ARR_SIZE);

	start_iter = BTSetBegin(my_set);
	end_iter = BTSetEnd(my_set);
	last_iter = BTSetPrev(end_iter);

	printf("start: %d\n", *(int *)BTSetGetData(start_iter));
	printf("last: %d\n", *(int *)BTSetGetData(last_iter));

	/* Check if the start.next data is correct */
	*(int *)BTSetGetData(BTSetNext(start_iter)) == 1 ? 
			printf("Correct start_iter.next value. \t\tTest Passed\n") :
			printf("Wrong start.next value. \t\tTest Failed!!\n");

	/* Check if the last.prev data is correct */
	*(int *)BTSetGetData(BTSetPrev(last_iter)) == 20 ? 
			printf("Correct last_iter.prev value. \t\tTest Passed\n") :
			printf("Wrong last_iter.prev value. \t\tTest Failed!!\n");

	BTSetIsSameIter(start_iter, start_iter) ?
			printf("is same start_iter \t\t\tTest Passed\n") :
			printf("is same start_iter \t\t\tTest Failed\n");

	BTSetIsSameIter(end_iter, end_iter) ?
			printf("is same end_iter \t\t\tTest Passed\n") :
			printf("is same end_iter \t\t\tTest Failed\n");

	BTSetIsSameIter(end_iter, BTSetNext(last_iter)) ?
			printf("prev on end_iter \t\t\tTest Passed\n") :
			printf("prev on end_iter \t\t\tTest Failed\n");

	printf("printing set elements:\n");
	PrintSetSortedIMP(my_set);

	printf("printing set elements backwards:\n");
	PrintBackwardsIMP(my_set);

	/* Count elements */
	BTSetSize(my_set) == 9 ?
			printf("Counted 9 nodes in my_set. \t\tTest Passed\n") :
			printf("Wrong count %ld. \t\tTest Failed!!\n", BTSetSize(my_set));	

	/* remove root (node with 2 sons) */
	next2removed_iter = BTSetRemove(my_set ,BTSetFind(my_set, &data_arr1[0]));

	printf("Removing the root node \n");

	/* Check if the next data is correct */
	*(int *)BTSetGetData(next2removed_iter) == 7 ? 
			printf("Correct next value. \t\t\tTest Passed\n") :
			printf("Value not found. \t\tTest Failed!!\n");

	BTSetSize(my_set) == 8 ?
			printf("Counted 8 nodes in my_set. \t\tTest Passed\n") :
			printf("Wrong count. \t\tTest Failed!!\n");

	/* remove node with one son  */
	next2removed_iter = BTSetRemove(my_set ,BTSetFind(my_set, &data_arr1[1]));

	printf("Removing npde with one son \n");

	/* Check if the next data is correct */
	*(int *)BTSetGetData(next2removed_iter) == 7 ? 
			printf("Correct next value. \t\t\tTest Passed\n") :
			printf("Value not found. \t\tTest Failed!!\n");

	BTSetSize(my_set) == 7 ?
			printf("Counted 7 nodes in my_set. \t\tTest Passed\n") :
			printf("Wrong count. \t\tTest Failed!!\n");

	BTSetDestroy(my_set);
}

/****************************Helpers Implementation****************************/

/*0 if equal, 0> if data1 lower then data2, 0< if data1 higher then data2*/
static int CompareInt(const void *data1, const void *data2, const void *param)
{
	UNUSED(param);
	return (*(int *)data1 - *(int *)data2);
}

static void PrintArrIMP(int *arr_, size_t size_)
{
	size_t i = 0;
	for(i = 0; i < size_; ++i)
	{
		printf("%d ", arr_[i]);
	}
	printf("\n");
}

static void PrintSetSortedIMP(btset_ty *set_)
{
	btset_iter_ty curr = {NULL};
	btset_iter_ty end = {NULL};

	assert(set_);

	curr = BTSetBegin(set_);
	end = BTSetEnd(set_);

	while(!BTSetIsSameIter(curr, end))
	{
		printf("%d ", *(int *)BTSetGetData(curr));
		curr = BTSetNext(curr);
	}
	
	printf("\n");
}

static void PrintBackwardsIMP(btset_ty *set_)
{
	btset_iter_ty curr = {NULL};
	btset_iter_ty start = {NULL};

	assert(set_);

	curr = BTSetPrev(BTSetEnd(set_));
	start = BTSetBegin(set_);

	while(!BTSetIsSameIter(curr, start))
	{
		printf("%d ", *(int *)BTSetGetData(curr));
		curr = BTSetPrev(curr);
	}
	printf("%d ", *(int *)BTSetGetData(curr));
	printf("\n");
}