/*******************************************************************************
*	Written by:		Olga Danielle Cahana									   *
*	Date:			27/12/221												   *
*	Reviewed by:	Alex						    						   *
*																			   *
*******************************************************************************/
#include <stdio.h> /* printf */ 
#include <stddef.h> /* size_t, sizeof */

#include "../include/queue.h"
#include "../include/slist.h"


/****************Tests declarations********************************************/
static void Scenario_1_Tests(void);
static void Scenario_2_Tests(void);

/*********************Helpers declarations*************************************/
/* TODO: Implement */
/* print queue elements (ints only) */
int PrintIntsQueue(void *data, void *param);

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
	queue_ty *queue1 = NULL;

	int data1 = 10;
	int data2 = 20;
	int data3 = 30;


	printf("Starting scenario1 tests:\n\n");
	/* Create new queue */
	queue1 = QueueCreate();
	queue1 != NULL ?
			printf("New queue created. \t\tTest Passed\n") :
			printf("Failed to create new queue. \t\tTest Failed!!\n");

	/* Check if empty */
	QueueIsEmpty(queue1) ?
			printf("The queue is empty. \t\tTest Passed\n") :
			printf("The queue is not empy. \tTest Failed!!\n");

	/* Check queue size */
	QueueSize(queue1) == 0 ?
			printf("Queue1 has 0 elements. \t\tTest Passed\n") :
			printf("Wrong count. \t\tTest Failed!!\n");


	/* Enqueue first element */
	QueueEnqueue(queue1, &data1);
	printf("\nEnqueue first element %d.\n\n", data1);

	/* Check if empty */
	!QueueIsEmpty(queue1) ?
			printf("The queue is not empty. \tTest Passed\n") :
			printf("The queue is empy. \t\tTest Failed!!\n");

	/* Check queue size */
	QueueSize(queue1) == 1 ?
			printf("Queue1 has 1 elements. \t\tTest Passed\n") :
			printf("Wrong count. \t\tTest Failed!!\n");

	/* Peek */
	*(int *)(QueuePeek(queue1)) == data1 ?
		printf("The data value is correct. \tTest Passed\n") :
		printf("Incorrect data value. \t\tTest Failed!!\n");

	/* Remove the last and only node from queue1 */
	printf("\nDequeue the last element.\n\n");
	QueueDequeue(queue1);

	/* Check if empty */
	QueueIsEmpty(queue1) ?
			printf("The queue is empty. \t\tTest Passed\n") :
			printf("The queue is not empy. \tTest Failed!!\n");

	/* Check queue size */
	QueueSize(queue1) == 0 ?
			printf("Queue1 has 0 elements. \t\tTest Passed\n") :
			printf("Wrong count. \t\tTest Failed!!\n");

	
	/* Enqueue elements */
	QueueEnqueue(queue1, &data1);
	printf("\nEnqueue element %d.\n", data1);
	QueueEnqueue(queue1, &data2);
	printf("\nEnqueue element %d.\n", data2);
	QueueEnqueue(queue1, &data3);
	printf("\nEnqueue element %d.\n\n", data3);

	/* Check queue size */
	QueueSize(queue1) == 3 ?
			printf("Queue1 has 3 elements. \t\tTest Passed\n") :
			printf("Wrong count. \t\tTest Failed!!\n");

	/* Peek */
	*(int *)(QueuePeek(queue1)) == data1 ?
		printf("The data value is correct. \tTest Passed\n") :
		printf("Incorrect data value. \t\tTest Failed!!\n");

	/* Remove an element */
	printf("\nDequeue an element.\n\n");
	QueueDequeue(queue1);

	/* Check queue size */
	QueueSize(queue1) == 2 ?
			printf("Queue1 has 2 elements. \t\tTest Passed\n") :
			printf("Wrong count. \t\tTest Failed!!\n");

	/* Peek */
	*(int *)(QueuePeek(queue1)) == data2 ?
		printf("The data value is correct. \tTest Passed\n") :
		printf("Incorrect data value. \t\tTest Failed!!\n");

	/* Remove an element */
	printf("\nDequeue an element.\n\n");
	QueueDequeue(queue1);

	/* Peek */
	*(int *)(QueuePeek(queue1)) == data3 ?
		printf("The data value is correct. \tTest Passed\n") :
		printf("Incorrect data value. \t\tTest Failed!!\n");

	/* Destroy  queue1 */
	printf("\nDestroying non empty queue.\n\n\n");
	QueueDestroy(queue1);

}
 
static void Scenario_2_Tests(void)
{
	queue_ty *queue1 = NULL;
	queue_ty *queue2 = NULL;

	int data1 = 10;
	int data2 = 20;
	int i = 0;


	printf("Starting scenario2 tests:\n\n");
	/* Create new queue */
	queue1 = QueueCreate();
	queue1 != NULL ?
			printf("New queue created. \t\tTest Passed\n") :
			printf("Failed to create new queue. \t\t\tTest Failed!!\n");

	queue2 = QueueCreate();
	queue2 != NULL ?
			printf("New queue created. \t\tTest Passed\n") :
			printf("Failed to create new queue. \t\tTest Failed!!\n");

	/* Enqueue 5 elements to queue1 */
	for(i = 0; i < 5; ++i)
	{
		QueueEnqueue(queue1, &data1);
	}

	/* Enqueue 7 elements to queue2 */
	for(i = 0; i < 7; ++i)
	{
		QueueEnqueue(queue2, &data2);
	}

	/* Check queue1 size */
	QueueSize(queue1) == 5 ?
			printf("Queue1 has 5 elements. \t\tTest Passed\n") :
			printf("Wrong count. \t\tTest Failed!!\n");

	/* Check queue2 size */
	QueueSize(queue2) == 7 ?
			printf("Queue2 has 7 elements. \t\tTest Passed\n") :
			printf("Wrong count. \t\tTest Failed!!\n");

	/* Append queue2 to queue1 */
	QueueAppend(queue1, queue2);

	/* Check queue1 size */
	QueueSize(queue1) == 12 ?
			printf("Queue1 has 12 elements.\t\tTest Passed\n") :
			printf("Wrong count. \t\tTest Failed!!\n");

	
	/* Peek and remove first 5 elements, queue1 original */
	for(i = 0; i < 5; ++i)
	{	
		printf("element %d:\n", i);
		*(int *)(QueuePeek(queue1)) == data1 ?
			printf("The data value is correct. \tTest Passed\n") :
			printf("Incorrect data value. \t\tTest Failed!!\n");
		QueueDequeue(queue1);
	}

	/* Peek and remove next 7 elemnts, origined in queue2 */
	for(i = 0; i < 7; ++i)
	{	
		printf("element %d:\n", i + 5);
		*(int *)(QueuePeek(queue1)) == data2 ?
			printf("The data value is correct. \tTest Passed\n") :
			printf("Incorrect data value. \t\tTest Failed!!\n");
		QueueDequeue(queue1);
	}

	/* Check if empty */
	QueueIsEmpty(queue1) ?
			printf("The queue is empty. \t\tTest Passed\n") :
			printf("The queue is not empy. \tTest Failed!!\n");

	/* Destroy  queue1 */
	printf("\nDestroying an empty queue.\n\n\n");
	QueueDestroy(queue1);

}




