/*******************************************************************************
*	Written by:		Olga Danielle Cahana									   *
*	Date:			3/2/2022												   *
*	Reviewed by:	Daniel						    					 	   *
*																			   *
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "avl_tree.h"
#include "utils.h"

enum {ARR_SIZE = 10};
/****************Tests declarations********************************************/
static void Scenario_1_Tests_Insert_Find(void);
static void Scenario_2_Tests_Iterators(); 



/*********************Helpers declarations*************************************/

static int CompareInt(const void *elem1, const void *elem2, const void *param);
static void PrintArrIMP(int *arr, size_t size);
static int PrintIntIMP(void *data, void *param);
static int BadOperationIMP(void *data, void *param);

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
    avl_tree_ty *my_tree = NULL;
    int data_arr[] = {6,2,23,7,8,1,0,20,12,4};
	avl_cmp_func_ty cmp_func = CompareInt;
	int found = 0;
	int not_in_tree = 100;
    int i = 0;

	printf("Starting scenarion 1:\n");
	/* create new set */
    my_tree = AVLCreate(CompareInt, NULL);
    my_tree != NULL ?
		printf("New avl tree created. \t\tTest Passed\n\n") :
		printf("Failed to create new avl tree. \t\tTest Failed!!\n");

	/* Check if empty */
    AVLIsEmpty(my_tree) ?
        printf("The tree is empty. \t\t\tTest Passed\n") :
		printf("The tree is not empy. \tTest Failed!!\n");

	/* Count elements */
    AVLSize(my_tree) == 0 ?
        printf("Counted 0 nodes in my_tree. \t\tTest Passed\n") :
        printf("Wrong count. \t\tTest Failed!!\n");
    
/*-------------------     Inserting Elements     --------------------------------*/
	/* Insert first element */
    printf("insert first element\n");
    AVLInsert(my_tree, &data_arr[0]);

	/* Check if empty */
    AVLIsEmpty(my_tree) == 0 ?
        printf("The tree is not empty. \t\t\tTest Passed\n") :
		printf("The tree is not empy. \tTest Failed!!\n");

	/* Count elements */
    AVLSize(my_tree) == 1 ?
        printf("Counted 1 nodes in my_tree. \t\tTest Passed\n") :
        printf("Wrong count. \t\tTest Failed!!\n");

	/* Insert second element - left son to the root*/
    AVLInsert(my_tree, &data_arr[1]);

    /* Count elements */
    AVLSize(my_tree) == 2 ?
        printf("Counted 2 nodes in my_tree. \t\tTest Passed\n") :
        printf("Wrong count. \t\tTest Failed!!\n");

    /* insert all the elements */
	for (i = 2; i < ARR_SIZE; ++i)
	{		
		AVLInsert(my_tree, &data_arr[i]);
	}

     /* Count elements */
    AVLSize(my_tree) == 10 ?
        printf("Counted 10 nodes in my_tree. \t\tTest Passed\n") :
        printf("Wrong count. \t\tTest Failed!!\n");

    AVLForEach(my_tree, PrintIntIMP, NULL, PREORDER) == 0 ?
		printf("\nPrint preorder \t\t\tTest Passed\n") :
		printf("\nPrint preorder  \t\t\tTest Failed\n"); 

	AVLForEach(my_tree, PrintIntIMP, NULL, INORDER) == 0 ?
		printf("\nPrint inorder \t\t\tTest Passed\n") :
		printf("\nPrint inorder  \t\t\tTest Failed\n");
	
	AVLForEach(my_tree, PrintIntIMP, NULL, POSTORDER) == 0 ?
		printf("\nPrint postorder \t\tTest Passed\n") :
		printf("\nPrint postorder  \t\t\tTest Failed\n");

	AVLForEach(my_tree, BadOperationIMP, NULL, PREORDER) == 1 ?
		printf("Foreach bad \t\t\tTest Passed\n") :
		printf("Foreach bad \t\t\tTest Failed\n"); 


/*-------------------        Find Elements     --------------------------------*/
	/* Find data from the root */
	found = *(int *)AVLFind(my_tree, &data_arr[0]);

	/* Check if the found data is correct */
	found == data_arr[0] ?
		printf("Element found \t\t\tTest Passed\n") :
		printf("element not found \t\tTest Failed\n");

	/* Find data from root's left son */
	found = *(int *)AVLFind(my_tree, &data_arr[1]);

	/* Check if the found data is correct */
	found == data_arr[1] ?
		printf("Element found \t\t\tTest Passed\n") :
		printf("element not found \t\tTest Failed\n");

	/* Find data from root's right son */
	found = *(int *)AVLFind(my_tree, &data_arr[2]);

	/* Check if the found data is correct */
	found == data_arr[2] ?
		printf("Element found \t\t\tTest Passed\n") :
		printf("element not found \t\tTest Failed\n");


	/* Find nonexisting value - bad iterator expected */
	found = (int)AVLFind(my_tree, &not_in_tree);
	found ==  0 ?
		printf("Element not found \t\tTest Passed\n") :
		printf("element found \t\tTest Failed\n");


	/*-------------------      Remove Elements   --------------------------------*/
	/* remove last(leaf) */


	/* Count elements */


	/* remove first (leaf) */


	/* remove root (leaf and last node in the set) */


	/*----------------------------------------------------------------------------*/			
	/* destroy */
	AVLDestroy(my_tree);
}

 static void Scenario_2_Tests_Iterators(void)
{
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

/* print int list (to be used with foreach) */
static int PrintIntIMP(void *data, void *param)
{
	UNUSED(param);

	printf("%d ",*(int *)data);
	return 0;
}

/* print int list (to be used with foreach) */
static int BadOperationIMP(void *data, void *param)
{
	UNUSED(param);

	/*check bad scenarion - op_func fails if 100 is found */
	if(*(int *)data == 23)
	{
		return 1;
	}
	return 0;
}

