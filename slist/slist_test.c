/*******************************************************************************
*	Written by:		Olga Danielle Cahana									   *
*	Date:			19/12/221												   *
*	Reviewed by:	Maoz Mordehi Shechtman			    					   *
*																			   *
*******************************************************************************/
#include <stdio.h> /* printf */ 
#include <stddef.h> /* size_t, sizeof */

#include "../include/slist.h"


/****************Tests declarations********************************************/
static void Scenario_1_Tests(void);
static void Scenario_2_Tests(void);
static void Append_Scenario_Tests(void);

/*********************Helpers declarations*************************************/
/* according to Find prototype */
static int CompareInt(const void *param1, void *param2);

/******************************Main********************************************/
int main(void)
{
	Scenario_1_Tests();
	Scenario_2_Tests();
	Append_Scenario_Tests();

	return 0;
}

/***********************Tests Implementation***********************************/
static void Scenario_1_Tests(void)
{
	slist_ty *my_list = NULL;
	iterator_ty start_iter;
	iterator_ty end_iter;

	int data = 10;
	int data1 = -6;


	printf("Starting scenario1 tests:\n\n");
	/* Create new slist (new list contains just a dummy node)*/
	my_list =  SlistCreate();	
	my_list != NULL ?
			printf("New list created. \t\tTest Passed\n\n") :
			printf("Failed to create new list. \t\tTest Failed!!\n");

	/* Check if empty */
	SlistIsEmpty(my_list) ?
			printf("The list is empty. \t\tTest Passed\n") :
			printf("The list is not empy. \tTest Failed!!\n");

	/* Count elements */
	SlistCount(my_list) == 0 ?
			printf("Counted 0 nodes in my_list. \tTest Passed\n") :
			printf("Wrong count. \t\tTest Failed!!\n");

	/* Get an iterator to beginning (here, since empty list, dummy node ) */
	start_iter = SlistBegin(my_list);
	(slist_ty *)SlistGetData(start_iter) == my_list ?
			printf("Get iterator to beginning. \tTest Passed\n") : 
			printf("Wrong begin iterator data. \tTest Failed!!\n");

	/* Get iterator to next node.
	 * (here, since empty list, iterator holding null node ) */
	SlistNext(start_iter).slist_node == NULL ?
			printf("Get iterator to next (NULL).\tTest Passed\n") : 
			printf("Get iterator to next.\t\tTest Failed!!\n");

	/* Get an iterator to end (here, since empty list, dummy node ) */
	end_iter = SlistEnd(my_list);
	end_iter.slist_node == start_iter.slist_node ?
			printf("Get iterator to end.\t\tTest Passed\n") : 
			printf("Get iterator to end.\t\tTest Failed!!\n");

	/* Check if end iterator is equal to beginning iterator */
	SlistIsEqual(start_iter, end_iter) ?
			printf("End iter is equal to start. \tTest Passed\n") :
			printf("Not equal. \t\t\tTest Failed!\n");

	/* Insert first non dummy node */
	SlistInsertBefore(start_iter, &data);
	printf("\nFirst node inserted.\n\n");

	/* Check if empty */
	!SlistIsEmpty(my_list) ?
			printf("The list is not empty. \t\tTest Passed\n") :
			printf("The list is empy. \t\tTest Failed!!\n");

	/* Count elements */
	SlistCount(my_list) == 1 ?
			printf("Counted 1 node in my_list. \tTest Passed\n") :
			printf("Wrong count. \t\tTest Failed!!\n");

	/* Get data */
	*(int *)(SlistGetData(start_iter)) == data ?
		printf("The data value is correct. \tTest Passed\n") :
		printf("Incorrect data value. \t\tTest Failed!!\n");

	/* Set data */
	printf("Setting data of first node\n");
	SlistSetData(start_iter, &data1);

	/* Get data */
	*(int *)(SlistGetData(start_iter)) == data1 ?
		printf("The data value is correct. \tTest Passed\n") :
		printf("Incorrect data value. \t\tTest Failed!!\n");

	/* Remove the last and only node from my_list */
	printf("\nRemoving the last node in the list.\n\n");
	SlistRemove(start_iter);

	/* Check if empty */
	SlistIsEmpty(my_list) ?
			printf("The list is empty. \t\tTest Passed\n") :
			printf("The list is not empy. \tTest Failed!!\n");

	/* Count elements */
	SlistCount(my_list) == 0 ?
			printf("Counted 0 nodes in my_list. \tTest Passed\n") :
			printf("Wrong count. \t\tTest Failed!!\n");

	/* Check if end iterator is equal to beginning iterator */
	SlistIsEqual(start_iter, end_iter) ?
			printf("End iter is equal to start. \tTest Passed\n") :
			printf("Not equal. \t\t\tTest Failed!\n");

	/* Destroy the empty my_list */
	printf("\nDestroying empty list.\n");
	SlistDestroy(my_list);

}
 
static void Scenario_2_Tests(void)
{
	slist_ty *my_list = NULL;
	iterator_ty current_iter;
	iterator_ty start_iter;
	iterator_ty end_iter;

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
	/* Create new slist (new list contains just a dummy node)*/
	my_list =  SlistCreate();	
	my_list != NULL ?
			printf("New list created. \t\tTest Passed\n") :
			printf("Failed to create new list. \t\tTest Failed!!\n");

	start_iter = SlistBegin(my_list);

	printf("Inserting 7 nodes.\n");
	SlistInsertBefore(start_iter, &data_int1);
	SlistInsertBefore(start_iter, &data_int2);  
	SlistInsertBefore(start_iter, &data_int3); 

	/* Get data of first 3 elements */
	*(int *)(SlistGetData(start_iter)) == data_int3 ?
		printf("The data value is correct. \tTest Passed\n") :
		printf("Incorrect data value. \t\tTest Failed!!\n");

	start_iter = SlistNext(start_iter);
	*(int *)(SlistGetData(start_iter)) == data_int2 ?
		printf("The data value is correct. \tTest Passed\n") :
		printf("Incorrect data value. \t\tTest Failed!!\n");

	start_iter = SlistNext(start_iter);
	*(int *)(SlistGetData(start_iter)) == data_int1 ?
		printf("The data value is correct. \tTest Passed\n") :
		printf("Incorrect data value. \t\tTest Failed!!\n");

	/* Insert the rest */
	SlistInsertBefore(start_iter, &data_str1);  
	SlistInsertBefore(start_iter, &data_str2);  
	SlistInsertBefore(start_iter, &data_double);  
	SlistInsertBefore(start_iter, &data_struct); 

	/* Check if empty */
	!SlistIsEmpty(my_list) ?
			printf("The list is not empty. \t\tTest Passed\n") :
			printf("The list is empy. \t\tTest Failed!!\n");

	/* Count elements */
	SlistCount(my_list) == 7 ?
			printf("Counted 7 nodes in my_list. \tTest Passed\n") :
			printf("Wrong count. \t\tTest Failed!!\n");

	
	/* Range for SlistFind */
	start_iter = SlistBegin(my_list);
	end_iter = SlistEnd(my_list);
	/* SlistFind Test */
	current_iter = SlistFind(start_iter, end_iter, func_ptr, &data_int1);
	*(int *)(SlistGetData(current_iter)) == data_int1 ?  
			printf("SlistFind found Test \t\tTest Passed\n") :
			printf("SlistFind found Test \t\tTest Failed!!\n");
		
	current_iter = SlistFind(start_iter, end_iter, func_ptr, &def_data);
	SlistIsEqual(current_iter, end_iter) ?  
			printf("SlistFind not found Test \tTest Passed\n") :
			printf("SlistFind not found Test \tTest Failed!!\n");

	/* Destroy the empty my_list */
	printf("\nDestroying the list.\n");
	SlistDestroy(my_list);

}

static void Append_Scenario_Tests(void)
{
	slist_ty *list1 = NULL;
	slist_ty *list2 = NULL;
	iterator_ty start_iter1;
	iterator_ty start_iter2;

	int i = 0;

	int data1 = 1;
	int data2 = 2;


	printf("Starting Append lists tests:\n\n");
	/* Create new slist (new list contains just a dummy node)*/
	list1 =  SlistCreate();	
	list2 =  SlistCreate();
	
	start_iter1 = SlistBegin(list1);
	start_iter2 = SlistBegin(list2);
	for(i = 0; i < 5; ++i)
	{
		SlistInsertBefore(start_iter1, &data1);
		SlistInsertBefore(start_iter2, &data2);		
	}
	
	SlistCount(list1) == 5 ?
			printf("Counted 5 nodes in list1. \tTest Passed\n") :
			printf("Wrong count. \t\tTest Failed!!\n");	
			
	SlistCount(list2) == 5 ?
			printf("Counted 5 nodes in list2. \tTest Passed\n") :
			printf("Wrong count. \t\tTest Failed!!\n");
			
	SlistAppend(list1, list2);
	SlistCount(list1) == 10 ?
			printf("Counted 10 nodes in list1. \tTest Passed\n") :
			printf("Wrong count. \t\tTest Failed!!\n");

	PrintListOfInts(list1);
			
	SlistDestroy(list1);
	


}

/****************************Helpers Implementation****************************/
static int CompareInt(const void *param1, void *param2)
{
	return !(*(int *)param1 == *(int *)param2);
}

