/*******************************************************************************
*	Written by:		Olga Danielle Cahana									   *
*	Date:			31/12/221												   *
*	Reviewed by:	Shiran							    					   *
*																			   *
*******************************************************************************/
#include <stdio.h> /* printf */ 
#include <stddef.h> /* size_t, sizeof */

#include "dlist.h"

#define UNUSED(param) ((void)param)
/****************Tests declarations********************************************/
static void Scenario_1_Tests(void);
static void Scenario_2_Tests(void);
static void PushPop_Test(void);
static void Append_Scenario_Tests(void);
static void MultiFindSplice_Test(void);

/*********************Helpers declarations*************************************/
/* according to Find prototype */
static int CompareInt(const void *param1, void *param2);

/* according to Find prototype: returns 0 if number is even */
static int IsEven(const void *param1, void *param2);

/* print all list nodes data, integers only */
void PrintListOfInts(dlist_ty * list);

/* print int list (to be used with foreach) */
static int PrintInt(void *data, void *param);


/******************************Main********************************************/
int main(void)
{
	Scenario_1_Tests();
	Scenario_2_Tests();
	PushPop_Test();
	MultiFindSplice_Test();
	Append_Scenario_Tests();

	return 0;
}

/***********************Tests Implementation***********************************/
static void Scenario_1_Tests(void)
{
	dlist_ty *my_list = NULL;
	iterator_ty start_iter;
	iterator_ty end_iter;
	iterator_ty inserted;


	int data = 10;
	int data1 = -6;
	int data2 = 2;


	printf("Starting scenario1 tests:\n\n");
	/* Create new dlist (new list contains just a dummy node)*/
	my_list =  DlistCreate();	
	my_list != NULL ?
			printf("New list created. \t\tTest Passed\n\n") :
			printf("Failed to create new list. \t\tTest Failed!!\n");

	/* Check if empty */
	DlistIsEmpty(my_list) ?
			printf("The list is empty. \t\tTest Passed\n") :
			printf("The list is not empy. \tTest Failed!!\n");

	/* Count elements */
	DlistSize(my_list) == 0 ?
			printf("Counted 0 nodes in my_list. \tTest Passed\n") :
			printf("Wrong count. \t\tTest Failed!!\n");

	/* Get an iterator to beginning (here, since empty list, dummy node ) */
	start_iter = DlistBegin(my_list);
	(dlist_ty *)DlistGetData(start_iter) == my_list ?
			printf("Get iterator to beginning. \tTest Passed\n") : 
			printf("Wrong begin iterator data. \tTest Failed!!\n");

	/* Get iterator to next node.
	 * (here, since empty list, iterator holding null node ) */
	DlistNext(start_iter).dlist_node == NULL ?
			printf("Get iterator to next (NULL).\tTest Passed\n") : 
			printf("Get iterator to next.\t\tTest Failed!!\n");

	/* Get an iterator to end (here, since empty list, dummy node ) */
	end_iter = DlistEnd(my_list);
	end_iter.dlist_node == start_iter.dlist_node ?
			printf("Get iterator to end.\t\tTest Passed\n") : 
			printf("Get iterator to end.\t\tTest Failed!!\n");

	/* Check if end iterator is equal to beginning iterator */
	DlistIsSameIter(start_iter, end_iter) ?
			printf("End iter is equal to start. \tTest Passed\n") :
			printf("Not equal. \t\t\tTest Failed!\n");

	/* Insert first non dummy node */
	inserted = DlistInsertBefore(start_iter, &data);
	printf("\nFirst node inserted.\n\n");

	/* Check if empty */
	!DlistIsEmpty(my_list) ?
			printf("The list is not empty. \t\tTest Passed\n") :
			printf("The list is empy. \t\tTest Failed!!\n");

	/* Count elements */
	DlistSize(my_list) == 1 ?
			printf("Counted 1 node in my_list. \tTest Passed\n") :
			printf("Wrong count. \t\tTest Failed!!\n");

	/* Get data */
	*(int *)(DlistGetData(inserted)) == data ?
		printf("The data value is correct. \tTest Passed\n") :
		printf("Incorrect data value. \t\tTest Failed!!\n");

	/* Set data */
	printf("Setting data of first node\n");
	DlistSetData(inserted, &data1);

	/* Get data */
	*(int *)(DlistGetData(inserted)) == data1 ?
		printf("The data value is correct. \tTest Passed\n") :
		printf("Incorrect data value. \t\tTest Failed!!\n");

	PrintListOfInts(my_list);

	/* Insert another node */
	inserted = DlistInsertBefore(inserted, &data);
	printf("\nAnother node inserted.\n");

	/* Insert first non dummy node */
	inserted = DlistInsertBefore(inserted, &data2);
	printf("\nAnother node inserted.\n");

	PrintListOfInts(my_list);

	/* Remove  node from my_list */
	printf("\nRemoving node from the list.\n\n");
	DlistRemove(DlistNext(inserted));

	/* Count elements */
	DlistSize(my_list) == 2 ?
			printf("Counted 2 nodes in my_list. \tTest Passed\n") :
			printf("Wrong count. \t\tTest Failed!!\n");

	PrintListOfInts(my_list);

	start_iter = DlistBegin(my_list);
	/* Remove  node from my_list */
	printf("\nRemoving node from the list.\n");
	DlistRemove(start_iter);

	/* Count elements */
	DlistSize(my_list) == 1 ?
			printf("Counted 1 nodes in my_list. \tTest Passed\n") :
			printf("Wrong count. \t\tTest Failed!!\n");
	PrintListOfInts(my_list);

	start_iter = DlistBegin(my_list);
	/* Remove  node from my_list */
	printf("\nRemoving node from the list.\n");
	DlistRemove(start_iter);
	PrintListOfInts(my_list);

	/* Count elements */
	DlistSize(my_list) == 0 ?
			printf("Counted 0 nodes in my_list. \tTest Passed\n") :
			printf("Wrong count. \t\tTest Failed!!\n");

	/* Destroy the empty my_list */
	printf("\nDestroying empty list.\n");
	DlistDestroy(my_list);

}
 
static void Scenario_2_Tests(void)
{
	dlist_ty *my_list = NULL;
	iterator_ty current_iter;
	iterator_ty start_iter;
	iterator_ty end_iter;
	iterator_ty inserted;

	int def_data = 100;
	int data_int1 = -777;
	int data_int2 = 77;
	int data_int3 = 3;
	char *data_str1 = "blabla";
	char *data_str2 = "bla";
	double data_double = 3.14;
	struct data
	{
		int x;
		char y;
	}data_struct = {1, 'y'};
	
	/* pointer to helper function */
	match_func_ty func_ptr = CompareInt;

	printf("\nStarting scenario2 tests:\n");
	/* Create new dlist (new list contains just a dummy node)*/
	my_list =  DlistCreate();	
	my_list != NULL ?
			printf("New list created. \t\tTest Passed\n") :
			printf("Failed to create new list. \t\tTest Failed!!\n");

	start_iter = DlistBegin(my_list);

	printf("Inserting 6 nodes.\n");
	inserted = DlistInsertBefore(start_iter, &data_int1);
	inserted = DlistInsertBefore(inserted, &data_int2);  
	inserted = DlistInsertBefore(inserted, &data_int3); 

	PrintListOfInts(my_list);
	start_iter = DlistBegin(my_list);
	/* Get data of first 3 elements */
	*(int *)(DlistGetData(start_iter)) == data_int3 ?
		printf("The data value is correct. \tTest Passed\n") :
		printf("Incorrect data value. \t\tTest Failed!!\n");

	start_iter = DlistNext(start_iter);
	*(int *)(DlistGetData(start_iter)) == data_int2 ?
		printf("The data value is correct. \tTest Passed\n") :
		printf("Incorrect data value. \t\tTest Failed!!\n");

	start_iter = DlistNext(start_iter);
	*(int *)(DlistGetData(start_iter)) == data_int1 ?
		printf("The data value is correct. \tTest Passed\n") :
		printf("Incorrect data value. \t\tTest Failed!!\n");

	/* Insert the rest */
	DlistInsertBefore(start_iter, &data_str1);  
	DlistInsertBefore(start_iter, &data_str2);  
	DlistInsertBefore(start_iter, &data_double);  
	DlistInsertBefore(start_iter, &data_struct); 

	/* Check if empty */
	!DlistIsEmpty(my_list) ?
			printf("The list is not empty. \t\tTest Passed\n") :
			printf("The list is empy. \t\tTest Failed!!\n");

	/* Count elements */
	DlistSize(my_list) == 7 ?
			printf("Counted 7 nodes in my_list. \tTest Passed\n") :
			printf("Wrong count. \t\tTest Failed!!\n");

	
	/* Range for DlistFind */
	start_iter = DlistBegin(my_list);
	end_iter = DlistEnd(my_list);
	/* DlistFind Test */
	current_iter = DlistFind(start_iter, end_iter, func_ptr, &data_int1);
	*(int *)(DlistGetData(current_iter)) == data_int1 ?  
			printf("DlistFind found Test \t\tTest Passed\n") :
			printf("DlistFind found Test \t\tTest Failed!!\n");
		
	current_iter = DlistFind(start_iter, end_iter, func_ptr, &def_data);
	DlistIsSameIter(current_iter, end_iter) ?  
			printf("DlistFind not found Test \tTest Passed\n") :
			printf("DlistFind not found Test \tTest Failed!!\n");

	/* Destroy the empty my_list */
	printf("\nDestroying the list.\n");
	DlistDestroy(my_list);

}

static void PushPop_Test(void)
{
	int data1 = 1;

	dlist_ty *list1 = NULL;

	printf("\nTesting Push & Pop:\n");
	list1 = DlistCreate();

	DlistPushFront(list1, &data1);

	/* Count elements */
	DlistSize(list1) == 1 ?
			printf("Counted 1 nodes in my_list. \tTest Passed\n") :
			printf("Wrong count. \t\tTest Failed!!\n");

	/* Pop Front */
	*((int *)DlistPopFront(list1)) == data1 ? 
			printf("Popped data value is correct. \tTest passed\n") :
			printf("Incorrect data value \t\t\tTest Failed\n");

	/* Count elements */
	DlistSize(list1) == 0 ?
			printf("Counted 0 nodes in my_list. \tTest Passed\n") :
			printf("Wrong count. \t\tTest Failed!!\n");

	DlistPushBack(list1, &data1);

	/* Count elements */
	DlistSize(list1) == 1 ?
			printf("Counted 1 nodes in my_list. \tTest Passed\n") :
			printf("Wrong count. \t\tTest Failed!!\n");

	/* Pop Back */
	*((int *)DlistPopBack(list1)) == data1 ? 
			printf("Popped data value is correct. \tTest passed\n") :
			printf("Incorrect data value \t\t\tTest Failed\n");

	/* Count elements */
	DlistSize(list1) == 0 ?
			printf("Counted 0 nodes in my_list. \tTest Passed\n") :
			printf("Wrong count. \t\tTest Failed!!\n");

	DlistDestroy(list1);

}

static void MultiFindSplice_Test(void)
{
	
	int data[12] = {1,2,3,4,5,6,7,8,9,10,11,12};
	int i = 0;
	dlist_ty *list1 = NULL, *list2 = NULL;
	iterator_ty start_splice, end_splice;
	iterator_ty start_list1, end_list1;
	match_func_ty func_ptr_isEven = IsEven;
	match_func_ty func_ptr_compare = CompareInt;

	
	printf("\nMulti Find & Splice:\n");
	list1 = DlistCreate();
	list2 = DlistCreate();

	/* Initializing list1 with [1,12] values */
	for(i = 0; i < 12; ++i)
	{
		DlistPushBack(list1, &data[i]);
	}

	/* get updated iterators */
	start_list1 = DlistBegin(list1);
	end_list1 = DlistEnd(list1);

	printf("list1:\n");
	PrintListOfInts(list1);

	printf("Find all even numbers in list1\n");
	DlistMultiFind(start_list1, end_list1,
								list2, func_ptr_isEven, NULL) == 6 ?
			printf("All matches found \t\tTest Passed\n") :
			printf("Wrong amount matched \t\tTest Failed\n");
	
	
	/* print list2 - should contain values: 2,4,6,8,10,12 */
	printf("list2 of found evens:\n");
	PrintListOfInts(list2);

	/* get updated iterators */
	start_list1 = DlistBegin(list1);
	end_list1 = DlistEnd(list1);

	start_splice = DlistFind(start_list1,end_list1, func_ptr_compare, &data[3]);
	end_splice = DlistFind(start_list1,end_list1, func_ptr_compare, &data[7]);

	/* splice 4-8 to the end of list 2 */
	printf("Splice [4,8) from list1 to the end of list 2:\n");
	DlistSplice(start_splice, end_splice, DlistEnd(list2));

	printf("list1 after splice:\n");
	PrintListOfInts(list1);
	printf("list2 after splice:\n");
	PrintListOfInts(list2);

	DlistDestroy(list1);
	DlistDestroy(list2);
}

static void Append_Scenario_Tests(void)
{
	dlist_ty *list1 = NULL;
	dlist_ty *list2 = NULL;
	iterator_ty inserted1, inserted2;
	

	int i = 0;

	int data1 = 1;
	int data2 = 2;


	printf("Starting Append lists tests:\n\n");
	/* Create new dlist (new list contains just a dummy node)*/
	list1 =  DlistCreate();	
	list2 =  DlistCreate();
	
	inserted1 = DlistBegin(list1);
	inserted2 = DlistBegin(list2);
	for(i = 0; i < 5; ++i)
	{
		inserted1 = DlistInsertBefore(inserted1, &data1);
		inserted2 = DlistInsertBefore(inserted2, &data2);		
	}
	
	DlistSize(list1) == 5 ?
			printf("Counted 5 nodes in list1. \tTest Passed\n") :
			printf("Wrong count. \t\tTest Failed!!\n");	
	PrintListOfInts(list1);
			
	DlistSize(list2) == 5 ?
			printf("Counted 5 nodes in list2. \tTest Passed\n") :
			printf("Wrong count. \t\tTest Failed!!\n");
	PrintListOfInts(list2);

	printf("Appending list2 to the end of list1:\n");		
	DlistAppend(list1, list2);
	DlistSize(list1) == 10 ?
			printf("Counted 10 nodes in new list1. \tTest Passed\n") :
			printf("Wrong count. \t\tTest Failed!!\n");

	PrintListOfInts(list1);
			
	DlistDestroy(list1);
}

/****************************Helpers Implementation****************************/
/* print all list nodes data, integers only */
void PrintListOfInts(dlist_ty * list)
{
	iterator_ty begin = DlistBegin(list);
	iterator_ty end = DlistEnd(list);
	op_func_ty print = PrintInt;

	DlistForEach(begin, end, print, NULL);
	printf("\n");
}

/* print int list (to be used with foreach) */
static int PrintInt(void *data, void *param)
{
	UNUSED(param);

	printf("%d ",*(int *)data);
	return 0;
}


static int CompareInt(const void *param1, void *param2)
{
	return !(*(int *)param1 == *(int *)param2);
}

static int IsEven(const void *param1, void *param2)
{
	UNUSED(param2);
	return (*(int *)param1 % 2 != 0);
}
