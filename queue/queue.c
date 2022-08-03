/*******************************************************************************
*	Written by:		Olga Danielle Cahana									   *
*	Date:			27/12/221												   *
*	Reviewed by:	Alex						    					 	   *
*																			   *
*******************************************************************************/
#include <assert.h> /* assert */
#include <stdio.h> /* fprintf */ 
#include <stdlib.h> /* size_t, malloc, free*/

#include "queue.h"
#include "slist.h"

/*************************** Defines ******************************************/
#define UNUSED(param) ((void)param)
#define RETURN_IF_NULL(result)\
			if(result == NULL)\
			{\
				fprintf(stderr, "Failed, NULL result\n");\
				return NULL; \
			}		
/**************************** Types *******************************************/
struct queue
{
	slist_ty *list;
};

/***************************Helpers declarations*******************************/




/******************************************************************************/
/*							Implementaion			     				      */
/******************************************************************************/
/******************************************************************************
* Function Description:  creates new queue data structure
* Arguments: - none	
* Return value: pointer to new queue
* Notes: returns NULL if memory allocation fails

* Time Complexity: O(1)
*******************************************************************************/
queue_ty *QueueCreate(void)
{
	queue_ty *queue = (queue_ty *)malloc(sizeof(queue_ty));
	RETURN_IF_NULL(queue);

	queue -> list = SlistCreate();
	if(queue == NULL)
	{
		free(queue);
		return NULL;
	}

	return queue;
}

/******************************************************************************
* Function Description:  destroys given queue by freeing the memory allocated by it
* Arguments: - pointer to a queue
* Return value: none
* Notes: if receives null - undefined behaviour.

* Time Complexity: O(n)
*******************************************************************************/
void QueueDestroy(queue_ty *queue)
{
	assert(queue);

	SlistDestroy(queue -> list);
	free(queue);
}

/******************************************************************************
* Function Description:  insert element to the tail of the queue
* Arguments: - pointer to the queue, pointer to an element
* Return value: GOOD
* Notes: returns FAIL Status if memory allocation failed

* Time Complexity: O(1)
*******************************************************************************/
int QueueEnqueue(queue_ty *queue, void *data)
{
	iterator_ty end;
	iterator_ty result;

	assert(queue);

	end = SlistEnd(queue -> list);
	result = SlistInsertBefore(end, data);
	end = SlistEnd(queue -> list);
	

	/* if dummy*/
	if(SlistIsEqual(result, end))
	{
		return -1;
	}
	return 0;
}

/******************************************************************************
* Function Description:  remove element from the head of the queue.
* Arguments: - pointer to the queue.
* Return value: -
* Notes: 

* Time Complexity: O(1)
*******************************************************************************/
void QueueDequeue(queue_ty *queue)
{
	iterator_ty begin; 

	assert(queue);
	assert(!QueueIsEmpty(queue));
	

	begin = SlistBegin(queue -> list);
	SlistRemove(begin);
}

/******************************************************************************
* Function Description: returns the pointer to the queue's head.
* Arguments: - pointer to the queue
* Return value: pointer to the data. 
* Notes: if the queue is empty - undefined behaviour.

* Time Complexity: O(1)
*******************************************************************************/
void *QueuePeek(const queue_ty *queue)
{
	iterator_ty begin; 

	assert(queue);

	begin = SlistBegin(queue -> list);

	return SlistGetData(begin);

}

/******************************************************************************
* Function Description: returns number of elements currently in the queue
* Arguments: - pointer to the queue.
* Return value: non-negative number of elements.
* Notes: 

* Time Complexity: O(n)
*******************************************************************************/
size_t QueueSize(const queue_ty *queue)
{
	assert(queue);

	return SlistCount(queue -> list);
}

/******************************************************************************
* Function Description: returns true is queue is empty, false otherwise
* Arguments: - pointer to the queue
* Return value: int (boolean) with value of either 0 (false) or 1 (true). 
* Notes: 

* Time Complexity: O(1)
*******************************************************************************/
int QueueIsEmpty(const queue_ty *queue)
{
	assert(queue);

	return SlistIsEmpty(queue -> list);
}

/******************************************************************************
* Function Description: appends one queue to another.
* Arguments: pointers to first and second queue
* Return value: -
* Notes: The second queue will be invalid after this operation.
			   both queue will be merged into the first queue.
			   (create in slist - SlistAppend function);

* Time Complexity: O(1)
*******************************************************************************/
void QueueAppend(queue_ty *first, queue_ty *second)
{
	assert(first);
	assert(second);

	SlistAppend(first->list, second->list);	
	free(second);
}

/************************Helpers implementatios********************************/
