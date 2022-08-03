/*******************************************************************************
*	Written by:		Olga Danielle Cahana									   *
*	Date:			06/01/2022												   *
*	Reviewed by:	Yonatan						    					 	   *
*																			   *
*******************************************************************************/
#include <stdio.h> /* printf */ 
#include <stddef.h> /* size_t, sizeof */

#include "heap_pq.h"

#define UNUSED(param) ((void)param)
/****************Tests declarations********************************************/
static void Scenario_1_Tests(void);
static void Scenario_2_Tests(void);

/*********************Helpers declarations*************************************/
/* according to Find prototype */
static int CompareInt(const void *param1, const void *param2);

/* according to Find prototype: returns 0 if number is even */
static int IsEven(const void *param1, void *param2);

/* print all pqueue nodes data, integers only */
void PrintAndClear(pq_ty *pqueue);


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
	pq_ty *pqueue = NULL;

	int data1 = 10;
	int result = 0;

	pq_cmp_func_ty compare_func = CompareInt;


	printf("Starting scenario1 tests:\n");
	/* Create new priority queue */
	pqueue =  PQCreate(compare_func);	
	pqueue != NULL ?
			printf("New priority queue created. \t\tTest Passed\n\n") :
			printf("Failed to create new pqueue. \t\tTest Failed!!\n");

	/* Count elements */
	PQSize(pqueue) == 0 ?
			printf("Counted 0 nodes in priority queue. \tTest Passed\n") :
			printf("Wrong count. \t\tTest Failed!!\n");

	/* Check if empty */
	PQIsEmpty(pqueue) ?
			printf("The pqueue is empty. \t\t\tTest Passed\n") :
			printf("The pqueue is not empy. \tTest Failed!!\n");

	/* Equeue first element */
	result = PQEnqueue(pqueue, &data1);
	printf("\nFirst node inserted to priority queue.\n\n");
	result == SUCCESS ?
			printf("Enqueue success. \t\t\tTest Passed\n") :
			printf("Failed to enqueue \t\tTest Failed\n");

	/* Check if empty */
	!PQIsEmpty(pqueue) ?
			printf("The pqueue is not empty. \t\tTest Passed\n") :
			printf("The pqueue is empy. \t\tTest Failed!!\n");

	/* Count elements */
	PQSize(pqueue) == 1 ?
			printf("Counted 1 node in priority queue. \tTest Passed\n") :
			printf("Wrong count. \t\tTest Failed!!\n");



	/* Peek */
	*(int *)(PQPeek(pqueue)) == data1 ?
		printf("The data value is correct. \t\tTest Passed\n") :
		printf("Incorrect data value. \t\tTest Failed!!\n"); 

	/* Dequeue the last element */
	*(int *)PQDequeue(pqueue) == data1 ?
			printf("Node dequeued \t\t\t\tTest Passed\n") :
			printf("Dequeue failed \t\t\t\tTest Failed"); 

	/* Count elements */
	PQSize(pqueue) == 0 ?
			printf("Counted 0 nodes in priority queue. \tTest Passed\n") :
			printf("Wrong count. \t\tTest Failed!!\n");

	/* Check if empty */
	PQIsEmpty(pqueue) ?
			printf("The pqueue is empty. \t\t\tTest Passed\n") :
			printf("The pqueue is not empy. \tTest Failed!!\n");

	/* Destroy the pqueue */
	printf("Destroying pqueue.\n\n");
	PQDestroy(pqueue); 
}
 
static void Scenario_2_Tests(void)
{
	pq_ty *pqueue = NULL;

	int data1 = 10;
	int data2 = -5;
	int data3 = 7;
	int data4 = 2;
	int data5 = -6;
	int data6 = 20;

	pq_cmp_func_ty compare_func = CompareInt;
	pq_match_func_ty match_func = IsEven;

	printf("Starting scenario2 tests:\n");
	/* Create new priority queue */
	pqueue =  PQCreate(compare_func);	
	pqueue != NULL ?
			printf("New priority queue created. \t\tTest Passed\n\n") :
			printf("Failed to create new pqueue. \t\tTest Failed!!\n");

	/* Insert elements */
	PQEnqueue(pqueue, &data1);
	PQEnqueue(pqueue, &data2);
	PQEnqueue(pqueue, &data3);
	PQEnqueue(pqueue, &data4);
	/*expected order: data1 = 10, data3 = 7, data4 = 2, data2 = -5 */
	PrintAndClear(pqueue); 
	printf("Four nodes enqueued to priority queue.\n\n");

	/* Insert elements */
	PQEnqueue(pqueue, &data1);
	PQEnqueue(pqueue, &data2);
	PQEnqueue(pqueue, &data3);
	PQEnqueue(pqueue, &data4);


	*(int *)(PQPeek(pqueue)) == data1 ?
		printf("The top element data is correct: %d \tTest Passed\n",
										 *(int *)(PQPeek(pqueue))) :
		printf("Incorrect data value: %d. \t\tTest Failed!!\n", *(int *)(PQPeek(pqueue)));

	/* Count elements */
	PQSize(pqueue) == 4 ?
			printf("Counted 4 nodes in priority queue. \tTest Passed\n") :
			printf("Wrong count. \t\tTest Failed!!\n");

	printf("Erasing first even:\n");
	*(int *)PQErase(pqueue, match_func, NULL) == data1 ?
		printf("First node erased: %d \t\tTest Passed\n", data1) :
		printf("Wrong Erase \t\t\tTest Failed\n");
	

	/* Count elements */
	PQSize(pqueue) == 3 ?
			printf("Counted 3 nodes in priority queue. \tTest Passed\n") :
			printf("Wrong count. \t\tTest Failed!!\n");

	/* erasing node with even data */
	*(int *)PQErase(pqueue, match_func, NULL) == data4 ?
		printf("First node erased: %d \t\tTest Passed\n",data4) :
		printf("Wrong Erase \t\t\tTest Failed\n");

	PQErase(pqueue, match_func, NULL) == NULL ?
		printf("No node was erased \t\t\tTest Passed\n") :
		printf("Wrong Erase \t\t\tTest Failed\n");

	/* Count elements */
	PQSize(pqueue) == 2 ?
			printf("Counted 2 nodes in priority queue. \tTest Passed\n") :
			printf("Wrong count. \t\tTest Failed!!\n");

	printf("Clear the priority queue:\n");
	PQClear(pqueue);

	/* Check if empty */
	PQIsEmpty(pqueue) ?
			printf("The pqueue is empty. \t\t\tTest Passed\n") :
			printf("The pqueue is not empy. \tTest Failed!!\n");

	/* clear an empty queue */
	PQClear(pqueue);

	printf("Enqueue and Dequeue two elements :\n");
	PQEnqueue(pqueue, &data5);
	PQEnqueue(pqueue, &data6);

	/*PrintAndClear(pqueue); */

	/* Check if empty */
	PQIsEmpty(pqueue) ?
			printf("The pqueue is empty. \t\t\tTest Passed\n") :
			printf("The pqueue is not empy. \tTest Failed!!\n");

	/* Destroy the pqueue */
	printf("Destroying pqueue.\n\n");
	PQDestroy(pqueue); 
}
 

/****************************Helpers Implementation****************************/
/* print all pqueue nodes data, integers only */
void PrintAndClear(pq_ty *pqueue)
{
	while(!PQIsEmpty(pqueue))
	{
		printf("%d ",*(int *)PQDequeue(pqueue));
	}
	printf("\n");
}

/*0 if equal
 * if result < 0 , data1 will be placed before data2, 
 * else (result > 0) data1 will be placed after data2 */
static int CompareInt(const void *data1, const void *data2)
{
	return (*(int *)data2 - *(int *)data1);
}

/* return 0 if the integer is an even number, 1 otherwise */
static int IsEven(const void *param1, void *param2)
{
	UNUSED(param2);
	return (*(int *)param1 % 2 != 0);
}
