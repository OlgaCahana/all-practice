/*******************************************************************************
*	Written by:		Olga Danielle Cahana									   *
*	Date:			06/01/2022												   *
*	Reviewed by:	Yonatan						    					 	   *
*																			   *
*******************************************************************************/
#include <assert.h> /* assert */
#include <stdio.h> /* fprintf */ 
#include <stdlib.h> /* size_t, malloc, free*/

#include "sorted_list.h"
#include "priorityq.h"

/*************************** Defines ******************************************/
#define UNUSED(param) ((void)param)
#define CHECK_ALLOC(x, FREE, FREE2, RETURN_VAL)	\
do 											 	\
{										 		\
	if (NULL == x)						 		\
	{											\
		fprintf(stderr, "Allocation failed\n");	\
		free(FREE);						 		\
		free(FREE2);						 	\
		return RETURN_VAL;				 		\
	}									 		\
}										 		\
while(0)										

/**************************** Types *******************************************/

struct priorityq
{
	sortlist_ty *sortlist;
};

/***************************Helpers declarations*******************************/


/******************************************************************************/
/*							Implementaion			     				      */
/******************************************************************************
* Function Description: Returns a pointer to an empty priority queue
* DS.   
* Arguments: compare function to determine priority.
* Return value: Pointer to priority queue or NULL in case of failure
* Notes: If cmp_func returns value that is less than, equal to, or greater than
* zero, data2 will have have, respectively, lower priority, equal priority or 
* greater priority than data1.

* Time Complexity: O(1)
*******************************************************************************/
pq_ty *PQCreate(int(*cmp_func)(const void *data1, const void *data2))
{
	pq_ty *priority_q = NULL;

	assert(cmp_func);

	priority_q = (pq_ty *)malloc(sizeof(pq_ty));
	CHECK_ALLOC(priority_q, NULL, NULL, NULL);

	priority_q->sortlist = SortedListCreate(cmp_func);
	CHECK_ALLOC(priority_q->sortlist, priority_q, NULL, NULL);

	return priority_q;
}


/******************************************************************************
* Function Description: Destroys priority queue       
* Arguments: pointer to a priority queue DS.
* Return value: none
* Notes:

* Time Complexity: O(n)
*******************************************************************************/
void PQDestroy(pq_ty *pq)
{
	assert(pq);

	SortedListDestroy(pq->sortlist);
	free(pq);
	pq = NULL;
}


/******************************************************************************
* Function Description: Enqueue a member holding data in the apropriate
* place according to the cmp_func
* Arguments: pointer to priority queue, void *data to insert.
* Return value: return 0 if success and 1 if fail
* Notes: if the new element has an equal priority to an existing element the 
* order is undefined
* Time Complexity: O(n).
*******************************************************************************/
int PQEnqueue(pq_ty *pq, const void *data)
{
	srt_iter_ty result;

	assert(pq);

	result = SortedListInsert(pq->sortlist, data);
	if(SortedListGetData(result) == data)
	{
		return SUCCESS;
	}
	else 
	{
		return FAIL;
	}
}

/******************************************************************************
* Function Description: Removes the member with the highest priority
* Arguments: pointer to priority queue
* Return value: void pointer to the data in the member
* Notes: Removes from an empty queue is undefined
* Time Complexity: O(1).
*******************************************************************************/
void *PQDequeue(pq_ty *pq)
{
	assert(pq);
	assert(!PQIsEmpty(pq));

	return SortedListPopFront(pq->sortlist);

}

/******************************************************************************
* Function Description: Returns the data of the member with the highest 
* priority
* Arguments: pointer to priority queue
* Return value: void pointer to the data
* Notes: Peek an empty queue is undefined 
* Time Complexity: O(1).
*******************************************************************************/
void *PQPeek(const pq_ty *pq)
{
	assert(pq);
	assert(!PQIsEmpty(pq));

	return SortedListGetData(SortedListBegin(pq->sortlist));
}

/******************************************************************************
* Function Description: return a boolean if the priority queue is empty	       
* Arguments: pointer to a priority queue DS
* Return value: 1 empty 0 not
* Notes:

* Time Complexity: O(1)
*******************************************************************************/
int PQIsEmpty(const pq_ty *pq)
{
	assert(pq);

	return SortedListIsEmpty(pq->sortlist);
}


/******************************************************************************
* Function Description: count num of elements in priority queue.   
* Arguments: 
* Return value: size of the priority queue
* Notes: 
*  
* Time Complexity: O(n)
*******************************************************************************/
size_t PQSize(const pq_ty *pq)
{
	assert(pq);

	return SortedListSize(pq->sortlist);
}

/******************************************************************************
* Function Description: Remove all the elements fron the priority queue.   
* Arguments: pointer to priority queue
* Return value: 
* Notes: 
*  
* Time Complexity: O(n)
*******************************************************************************/
void PQClear(pq_ty *pq)
{
	srt_iter_ty start;
	srt_iter_ty end;

	assert(pq);

	start = SortedListBegin(pq->sortlist);
	end = SortedListEnd(pq->sortlist);

	while (!SortedListIsSameIter(start, end))
	{
		start = SortedListRemove(start);
	}	
}

/******************************************************************************
* Function Description: Erase the first occurance with the highest priority
* that matches according to
* match function   
* Arguments: pointer to priority queue, match function and a parameter
* Return value: returns the data that was erased, if there is no match returns
* NULL 
* Notes: 
*  
* Time Complexity: O(n)
*******************************************************************************/
void *PQErase(pq_ty *pq,
			  int(*match_func)(const void *data1, void *param),
			  void *param)
{
	srt_iter_ty found;
	srt_iter_ty end;
	void * data_erased = NULL;

	assert(pq);
	assert(match_func);

	end = SortedListEnd(pq->sortlist);
	found = SortedListFindIf(SortedListBegin(pq->sortlist), SortedListEnd(pq->sortlist),
							 match_func, param);
	if(SortedListIsSameIter(found, end))
	{
		return NULL;
	}
	data_erased = SortedListGetData(found);
	SortedListRemove(found);
	return data_erased;
}

