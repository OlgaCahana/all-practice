/*******************************************************************************
*	Written by:		Olga Danielle Cahana									   *
*	Date:			02/01/2022												   *
*	Reviewed by:	Shulamit						    				 	   *
*																			   *
*******************************************************************************/
#include <assert.h> /* assert */
#include <stdio.h> /* fprintf */ 
#include <stdlib.h> /* size_t, malloc, free*/

#include "sorted_list.h"

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

struct sortlist
{
	dlist_ty *dlist;	
	cmp_func_ty cmp_func;
};

/***************************Helpers declarations*******************************/
static int IsDummy(srt_iter_ty iter);
static int IsFirstDummy(srt_iter_ty iter);


/******************************************************************************/
/*							Implementaion			     				      */
/******************************************************************************
* Function Description: returns a pointer to an empty SortedList DS.   
* Arguments: compar function.
* Return value: Pointer to SortedList.
* Notes: Return NULL in case of failure

* Time Complexity: O(1)
*******************************************************************************/
sortlist_ty *SortedListCreate(cmp_func_ty cmp_func)
{
	sortlist_ty *list = NULL;

	list = (sortlist_ty *)malloc(sizeof(sortlist_ty));
	CHECK_ALLOC(list, NULL, NULL, NULL);

	list->dlist = DlistCreate();
	CHECK_ALLOC(list->dlist, list, NULL, NULL);

	list->cmp_func = cmp_func;

	return list;
}


/******************************************************************************
* Function Description: destroys SortedList	       
* Arguments: pointer to a SortedList DS.
* Return value: none
* Notes:

* Time Complexity: O(n)
*******************************************************************************/
void SortedListDestroy(sortlist_ty *sortlist)
{
	assert(sortlist);
	assert(sortlist->dlist);

	DlistDestroy(sortlist->dlist);
	free(sortlist);
	sortlist = NULL;
}


/******************************************************************************
* Function Description: count num of elements in SortedList.   
* Arguments: pointer to list,
* Return value: size of the list
* Notes: 
*  
* Time Complexity: O(n)
*******************************************************************************/
size_t SortedListSize(const sortlist_ty *sortlist)
{
	assert(sortlist);
	assert(sortlist->dlist);

	return DlistSize(sortlist->dlist);
}

/******************************************************************************
* Function Description: return a boolean if the SortedList is empty	       
* Arguments: pointer to a SortedList DS
* Return value: 1 empty 0 not
* Notes:

* Time Complexity: O(1)
*******************************************************************************/
int SortedListIsEmpty(const sortlist_ty *sortlist)
{
	assert(sortlist);
	assert(sortlist->dlist);

	return DlistIsEmpty(sortlist->dlist);
}


/******************************************************************************
* Function Description: return a beginning of a SortedList DS
* Arguments: pointer to SortedList.
* Return value: first valid node of the SortedList.
* Notes: Return dummy tail node in case of empty list

* Time Complexity: O(1)
*******************************************************************************/
srt_iter_ty SortedListBegin(const sortlist_ty *sortlist)
{
	srt_iter_ty begin;

	assert(sortlist);
	assert(sortlist->dlist);

	begin.iterator = DlistBegin(sortlist->dlist);
	DEBUG_ONLY(begin.list = (sortlist_ty *)sortlist);

	return begin;
}

/******************************************************************************
* Function Description: return the dummy end of a SortedList DS
* Arguments: pointer to SortedList.
* Return value: last node in SortedList.
* Notes: -

* Time Complexity: O(1)
*******************************************************************************/
srt_iter_ty SortedListEnd(const sortlist_ty *sortlist)
{
	srt_iter_ty end;

	assert(sortlist);
	assert(sortlist->dlist);

	end.iterator = DlistEnd(sortlist->dlist);
	DEBUG_ONLY(end.list = (sortlist_ty *)sortlist);

	return end;
}


/******************************************************************************
* Function Description: return the next node in a SortedList
* Arguments: iterator.
* Return value: iterator of the next node in SortedList.
* Notes: undifeined behaviour in case user gave the last dummy node.

* Time Complexity: O(1)
*******************************************************************************/
srt_iter_ty SortedListNext(srt_iter_ty current)
{
	assert(current.iterator.dlist_node);

	current.iterator = DlistNext(current.iterator);

	return current;
}

/******************************************************************************
* Function Description: return the previous node in a SortedList
* Arguments: iterator.
* Return value: iterator of the previous node in SortedList.
* Notes: undefined in case of first node

* Time Complexity: O(1)
*******************************************************************************/
srt_iter_ty SortedListPrev(srt_iter_ty current)
{
	assert(current.iterator.dlist_node);

	current.iterator = DlistPrev(current.iterator);

	return current;
}

/****************************************************************************** 
* Function Description: retrun true if two iterators points the same node 
* Arguments: two iterators
* Return value: 1 if true 0 if false
* Notes:  

* Time Complexity: O(1)
*******************************************************************************/
int SortedListIsSameIter(srt_iter_ty first, srt_iter_ty second)
{
	/* debug mode assert, both iterators belong to the same list */
	DEBUG_ONLY(assert(first.list == second.list));
	
	return DlistIsSameIter(first.iterator, second.iterator);
}

/******************************************************************************
* Function Description: return the data of a given node 
* Arguments: iterator.
* Return value: void * to data.
* Notes: undefined in case of empty SortedList 

* Time Complexity: O(1)
*******************************************************************************/
void *SortedListGetData(srt_iter_ty current)
{
	assert(current.iterator.dlist_node);
	
	return DlistGetData(current.iterator);
}

/******************************************************************************
* Function Description: insert a node and sort it by the compare function.
						so that  compare function of member to the previous member
*						will return  positive.
* Arguments: pointer to sortlist,  void *data to insert.
* Return value: iterator to the new node.
* Notes: return dummy if fail
* Time Complexity: O(n).
*******************************************************************************/
srt_iter_ty SortedListInsert(sortlist_ty *sortlist, const void *data)
{
	srt_iter_ty current;
	srt_iter_ty end;
	srt_iter_ty inserted;

	assert(sortlist);
	assert(sortlist->dlist);

	current = SortedListBegin(sortlist);
	inserted = SortedListEnd(sortlist);
	end = SortedListEnd(sortlist);

	/* if data is bigger then the last element in sorted list, insert to the end */
	if(!SortedListIsEmpty(sortlist) && 
		sortlist->cmp_func(SortedListGetData(SortedListPrev(end)), data) <= 0)
	{
		inserted.iterator = DlistInsertBefore(end.iterator, data);
		return inserted;
	}
	
	/* insert the data before the first element found that is bigger than the data */
	while(!SortedListIsSameIter(current, end))
	{
		/* if current data >= data, insert before the current */
		if(sortlist->cmp_func(SortedListGetData(current), data) > 0)
		{
			inserted.iterator = DlistInsertBefore(current.iterator, data);
			return inserted;
		}
		current = SortedListNext(current);
	}
	
	/* will be executed only if the first 'if' will be omitted*/
	inserted.iterator = DlistInsertBefore(current.iterator, data);

	return inserted;
}

/******************************************************************************
* Function Description: remove the given node.   
* Arguments: iterator.
* Return value: iterator to the next element in the list  
* Notes:  removing from an empty SortedList will cause undefined behaviour.
* Time Complexity: O(1)

*******************************************************************************/
srt_iter_ty SortedListRemove(srt_iter_ty where)
{
	assert(!IsDummy(where));

	where.iterator = DlistRemove(where.iterator);
	return where;
}

/******************************************************************************
* Function Description: remove the node of the beginning of a given SortedList.   
* Arguments: pointer to sortlist.
* Return value: void *data
* Notes:  removing from an empty SortedList will cause undefined behaviour.
* Time Complexity: O(1)

*******************************************************************************/
void *SortedListPopFront(sortlist_ty *sortlist)
{
	assert(sortlist);
	assert(sortlist->dlist);
	assert(!SortedListIsEmpty(sortlist));

	return DlistPopFront(sortlist->dlist);
}

/******************************************************************************
* Function Description: remove the node from the end of a given sortlist.   
* Arguments: pointer to sortlist.
* Return value:  void *data
* Notes:  removing from an empty SortedList will cause undefined behaviour.
* Time Complexity: O(1)

*******************************************************************************/
void *SortedListPopBack(sortlist_ty *sortlist)
{
	assert(sortlist);
	assert(sortlist->dlist);
	assert(!SortedListIsEmpty(sortlist));

	return DlistPopBack(sortlist->dlist);
}

/******************************************************************************
* Function Description: foreach element in specified range, perform function.
* (not including the end node)
* Arguments: iterator of start of range, iterator of end of range, function,
* parameter
* Return value: 1 if fail 0 if succsess & func stops upon first failure
* Notes: undefined behaviour if start and end not from the same list.

* Time Complexity: O(n)
*******************************************************************************/
int SortedListForEach(srt_iter_ty start,
				 srt_iter_ty end,
				 int(*op_func_ty)(void *data, void *param),
				 void *param)
{
	DEBUG_ONLY(assert(start.list == end.list));
	assert(!IsFirstDummy(start));
	assert(op_func_ty);
	assert(start.iterator.dlist_node);
	assert(end.iterator.dlist_node);

	return DlistForEach(start.iterator, end.iterator, op_func_ty, param);
}

/******************************************************************************
* Function Description: merge the two list and sort them by the compare function.
* Arguments: two sorted list pointers 
* Return value: pointer to the sortlist of the merged lists  
* Notes: undefined behaviour if user giving the same list.
*		 undefined if the comapare function is not the same.
* the second list will be empty afetr using the function.
* Time Complexity: O(n + m)
*******************************************************************************/
sortlist_ty *SortedListMerge(sortlist_ty *first ,sortlist_ty *second)
{
	srt_iter_ty start1;
	srt_iter_ty start2;
	srt_iter_ty current2;
	srt_iter_ty end2;
	srt_iter_ty dest;

	assert(first);
	assert(second);
	assert(first->dlist);
	assert(second->dlist);

	start1 = SortedListBegin(first);
	start2 = SortedListBegin(second);
	current2 = SortedListBegin(second);
	end2 = SortedListEnd(second);


	/* While the second list is not empty */
	while(!SortedListIsEmpty(second))
	{	
		/* find the first element in first list that is bigger than the first element 
		 * in the second list, this is the dest */	
		while(!IsDummy(start1) &&
			(first->cmp_func(SortedListGetData(start1), SortedListGetData(start2)) <= 0))
		{
			start1 = SortedListNext(start1);
		}
		dest = start1;

		/* if bigger element not found and the first's list dummy is reached,
		 * merge the rest of second to dest and return */
		if(IsDummy(dest))
		{
			DlistSplice(start2.iterator, end2.iterator, dest.iterator);
			return first;
		}

		/* find all the elements from the second list that should be merged to dest
		 * i.e the first element in second that is bigger than the dest */
		while(!IsDummy(current2) &&
			(second->cmp_func(SortedListGetData(current2), SortedListGetData(dest)) <= 0))
		{
			current2 = SortedListNext(current2);
		} 

		/*move elements from start2 to one before the current, to the dest (before) */
		DlistSplice(start2.iterator, current2.iterator, dest.iterator);
		start2 = current2;
	}
	/* return pointer to first sorted list that is now merged */
	return first;
}
				 
/******************************************************************************
* Function Description: find first node that return true by the comapre function
	given the data  
* Arguments: sortlist pointer iterator_ty start, iterator_ty end, void * of 
*			 data to find
* Return value: iterator of found data
* Notes: undefined behaviour if start and end not from the same list.
* in case no node found return thr dummy end.

* Time Complexity: O(n)
*******************************************************************************/
srt_iter_ty SortedListFind(sortlist_ty *list,srt_iter_ty start, srt_iter_ty end,
														const void *to_find)
{
	srt_iter_ty end_dummy;

	assert(!IsFirstDummy(start));
	assert(list);
	assert(start.iterator.dlist_node);
	assert(end.iterator.dlist_node);

	end_dummy = SortedListEnd(list);
	
	/* if to_find is bigger than the last list element, no match is possible */
	if(!SortedListIsEmpty(list) && 
		(list->cmp_func(SortedListGetData(SortedListPrev(end_dummy)), to_find) < 0 ||
		 list->cmp_func(SortedListGetData(SortedListBegin(list)), to_find) > 0))
	{
		return end_dummy;
	}
 
	while (!SortedListIsSameIter(start, end))
	{	
		/* if bigger value than data met. stop looking and return dummy */
		if((list->cmp_func(SortedListGetData(start), to_find)) > 0)
		{
			return end_dummy;
		}
		/* if value we're looking for is found */
		if((list->cmp_func(SortedListGetData(start), to_find)) == 0)
		{
			return start;
		}
		start = SortedListNext(start);
	}

	return end_dummy;
}

/******************************************************************************
* Function Description: compare the data and the parameter by the function user 
						send to function 
* Arguments: iterator start, itearator end, match function, parameter
* Return value: iterator to matches node
* Notes: undefined behaviour if start and end not from the same list.
*		 in case no node found return thr dummy end.
* Time Complexity: O(n)
*******************************************************************************/
srt_iter_ty SortedListFindIf(srt_iter_ty start,
 					   srt_iter_ty end, 
					   int(*match_func)(const void *data, void *param),
					     void *param)
{
	DEBUG_ONLY(assert(start.list == end.list));
	assert(!IsFirstDummy(start));
	assert(match_func);
	assert(start.iterator.dlist_node);
	assert(end.iterator.dlist_node);

	start.iterator = DlistFind(start.iterator, end.iterator,match_func, param);
	return start;
}


/************************Helpers implementatios********************************/
static int IsDummy(srt_iter_ty iter)
{
	return (SortedListNext(iter).iterator.dlist_node == NULL ||
			SortedListPrev(iter).iterator.dlist_node == NULL);
}

static int IsFirstDummy(srt_iter_ty iter)
{
	return (SortedListPrev(iter).iterator.dlist_node == NULL);
}

