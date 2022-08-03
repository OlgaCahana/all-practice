/*******************************************************************************
*	Written by:		Olga Danielle Cahana									   *
*	Date:			19/12/221												   *
*	Reviewed by:	Maoz						    					 	   *
*																			   *
*******************************************************************************/
#include <assert.h> /* assert */
#include <stdio.h> /* fprintf */ 
#include <stdlib.h> /* size_t, malloc, free*/
#include "../include/slist.h"

/*************************** Defines ******************************************/
#define UNUSED(param) ((void)param)
#define RETURN_IF_NULL(result)\
			if(result == NULL)\
			{\
				fprintf(stderr, "Failed, NULL result\n");\
				return NULL; \
			}		
/**************************** Types *******************************************/
/* node struct */
struct node
{
	void *data;
	node_ty *next;
};
/* struct list */
struct slist
{
	node_ty *head;
	node_ty *tail;
};

/***************************Helpers declarations*******************************/

/* Return true if the iterator is iterator to the dummy node*/
static int IsDummy(iterator_ty iterator);

/* adds 1 to param, used in count with foreach */
int Add1(void *data, void *param);

/* print int list (to be used with foreach) */
int PrintInt(void *data, void *param);


/******************************************************************************/
/*							Implementaion			     				      */
/*******************************************************************************
* Function Description: returns a pointer to an empty slist DS.   
* Arguments: - 
* Return value: Pointer to slist.
* Notes: Return NULL in case of failure

* Time Complexity: O(1)
*******************************************************************************/

slist_ty *SlistCreate(void)
{
	slist_ty *list = (slist_ty *)malloc(sizeof(slist_ty));
	RETURN_IF_NULL(list);
	
	list->head = (node_ty *)malloc(sizeof(node_ty));
	if(list->head == NULL)
	{
		free(list);
		return NULL;
	}
	
	list->head->data = list;
	list->head->next = NULL;

	list->tail = list->head;
	return list;
	

}

/******************************************************************************
* Function Description: destroys the slist	       
* Arguments: pointer to a slist structure
* Return value: none
* Notes:

* Time Complexity: O(n)
*******************************************************************************/
void SlistDestroy(slist_ty *slist)
{
	iterator_ty start = SlistBegin(slist);
	
	assert(slist);
	
	/* remove all the nodes until dummy node is reached */
	while(start.slist_node->next != NULL)
	{
		start = SlistRemove(start);
	}

	/* remove the dummy node */
	free(start.slist_node); 

	/* free the slist struct */
	free(slist);	
}

/******************************************************************************
* Function Description: return a boolian if the list is empty	       
* Arguments: pointer to a slist structure
* Return value: 1 empty 0 not
* Notes:

* Time Complexity: O(1)
*******************************************************************************/
int SlistIsEmpty(const slist_ty *slist)
{
	assert(slist);
	
	return (slist->head == slist->tail);
}

/******************************************************************************
* Function Description: insert a node before begginig of a given node ds.   
* Arguments: pointer to node,  void *data to insert, pointer to slist.
* Return value: iterator to the new element.
* Notes: If fails to insert, returns pointer to dummy
* Time Complexity: O(1)
*******************************************************************************/
iterator_ty SlistInsertBefore(iterator_ty where, const void *data)
{
	node_ty *new_node = (node_ty *)malloc(sizeof(node_ty));
	/* if mem allocation failed, return dummy iterator */
	if(new_node == NULL)
	{
		while(!IsDummy(where))
		{
			where = SlistNext(where);
		}
		
		printf("Memory allocation Failed!\n");
		
		return where;
	}

	/* Copy where node to new node */
	new_node->data = SlistGetData(where);
	new_node->next = SlistNext(where).slist_node;

	/* If where is iterator to the dummy node, update the tail */
	if(IsDummy(where))
	{
		((slist_ty *)(SlistGetData(where)))->tail = new_node;
	}

	/* Copy the arg data to where node */
	SlistSetData(where, (void *)data);

	/* Set the where next to point to new node */
	where.slist_node->next = new_node;

	return where;
}

/******************************************************************************
* Function Description: remove a node before begginig of a given node ds.   
* Arguments: pointer to head, void *data to insert, pointer to slist.
* Return value: iterator to the next element in the list  
* Notes: 
2. removing last node (dummy) will cause undefined behaviour.

* Time Complexity: O(1)

*******************************************************************************/
iterator_ty SlistRemove(iterator_ty where)
{
	iterator_ty temp;

	/* assert if where holds the dummy node */
	/* the dummy node should not be removed */
	assert(!IsDummy(where));

	/* get iterator to where next */
	temp = SlistNext(where);

	/* copy where next data to where */
	where.slist_node->data = temp.slist_node->data;

	/* set where.node->next to point to temp.node->next */
	where.slist_node->next = temp.slist_node->next;

	/* if temp is the dummy, update the tail to point to where */
	if(IsDummy(temp))
	{
		((slist_ty *)(temp.slist_node->data))->tail = where.slist_node;
	}

	/* free the temp */
	free(temp.slist_node);

	return where;
}

/******************************************************************************
* Function Description: count num of elements in slist.   
* Arguments: pointer to head slist,
* Return value: size of list
* Notes: 
*  
* Time Complexity: O(n)
*******************************************************************************/
/*Note: Other implementation for Slist count*/
/*size_t SlistCount(const slist_ty *slist)
{
	assert(slist);

	size_t count = 0;
	iterator_ty begin = SlistBegin(slist);
	iterator_ty end = SlistEnd(slist);

	while(!SlistIsEqual(begin, end))
	{
		++count;
		begin = SlistNext(begin);
	}
	return count;
}*/

/* Count implemented with foreach */
size_t SlistCount(const slist_ty *slist)
{
	size_t count = 0;
	iterator_ty start = SlistBegin(slist);
	iterator_ty end = SlistEnd(slist);
	/* to be used in count with foreach */
	op_func_ty func_ptr = Add1;

	assert(slist);

	SlistForEach(start, end, func_ptr, &count);
	
	return count;
}

/******************************************************************************
* Function Description: foreach element in specified range, perform function.
* Arguments: iterator of start of range, iterator of end of range, function
* Return value: 1 if fail 0 if succsess & fuc stops upon first failure
* Notes: undefined behaviour if start and end not from the same list.

* Time Complexity: O(n)
*******************************************************************************/
int SlistForEach(iterator_ty start,
				 iterator_ty end,
				 op_func_ty op_func,
				 void *param)
{
	DEBUG_ONLY(assert(start.list == end.list));

	while (!SlistIsEqual(start,end))
	{
		if(op_func(start.slist_node->data, param) == 0)
		{
			start = SlistNext(start);
		}
		else 
		{
			return 1;
		}
	}

	return 0;
}
					
		
/******************************************************************************
* Function Description: find first occurrence of data in slist.   
* Arguments: pointer to head, iterator.
* Return value: iterator of data
* Notes: undefined behaviour if start and end not from the same list.

* Time Complexity: O(n)
*******************************************************************************/
iterator_ty SlistFind(iterator_ty start,
 					  iterator_ty end, 
					  match_func_ty op_func,
					  void *param)
{
	DEBUG_ONLY(assert(start.list == end.list));

	while (!SlistIsEqual(start, end))
	{
		if(op_func(start.slist_node->data, param) == 0)
		{
			return start;
		}

		start = SlistNext(start); /* promote start iterator*/
	}

 /* matched data not found, promote start to the dummy node and return the dummy */
	while(!IsDummy(start))
		{
			start = SlistNext(start);
		}

	return start;	
}


/******************************************************************************
* Function Description: return a beginning of a slist
* Arguments: pointer to head.
* Return value: head slist.
* Notes: Return NULL in case of empty slist

* Time Complexity: O(1)
*******************************************************************************/
iterator_ty SlistBegin(const slist_ty *slist)
{
	iterator_ty iter;

	assert(slist);

	iter.slist_node = slist->head;
	DEBUG_ONLY(iter.list = (slist_ty *)slist);
	return iter;
}

/******************************************************************************
* Function Description: return the end of a slist
* Arguments: pointer to head.
* Return value: last node in slist.(dummy node)
* Notes: Return NULL in case of empty slist

* Time Complexity: O(1)
*******************************************************************************/
iterator_ty SlistEnd(const slist_ty *slist)
{
	iterator_ty iter;

	assert(slist);

	iter.slist_node = slist->tail;
	DEBUG_ONLY(iter.list = (slist_ty *)slist);
	return iter;
}

/******************************************************************************
* Function Description: return the next node iterator in a slist
* Arguments: pointer to node.
* Return value: iterator of the next node in slist.
* Notes: Return iterator holding NULL value in case of empty slist

* Time Complexity: O(1)
*******************************************************************************/
iterator_ty SlistNext(iterator_ty iterator)
{	
	iterator.slist_node = iterator.slist_node->next;
	return iterator;
}

/******************************************************************************
* Function Description: return the data of a given node 
* Arguments: Iterator to node.
* Return value: void * to data.
* Notes: Return NULL in case of empty slist

* Time Complexity: O(1)
*******************************************************************************/
void *SlistGetData(const iterator_ty iterator)
{
	return iterator.slist_node->data;

}

/******************************************************************************
* Function Description: set data in a node of slist 
* Arguments: pointer to node.
* Return value: node , data.
* Notes: Return status in case of success or failure
size of data must match data size of element

* Time Complexity: O(1)
*******************************************************************************/
void SlistSetData(iterator_ty iterator, void *data)
{	
	iterator.slist_node->data = data;
}

/******************************************************************************
* Function Description: returns true if two iterators are equal
* (hold the same node) 
* Arguments: two iterators
* Return value: true or false
* Notes: 

* Time Complexity: O(1)
*******************************************************************************/
int SlistIsEqual(iterator_ty iter1, iterator_ty iter2)
{
	/* debug mode assert, both iterators belong to the same list */
	DEBUG_ONLY(assert(iter1.list == iter2.list));

	return iter1.slist_node == iter2.slist_node;
}


/* this function will append 2 slists: second to the end of first */
void SlistAppend(slist_ty *first, slist_ty *second)
{
	iterator_ty first_end;
	iterator_ty second_begin;
	
	assert(first);
	assert(second);
	
	first_end = SlistEnd(first);
	second_begin = SlistBegin(second);
	
	
	/* Update second dummy data to first list and Update the first list tail */
	second -> tail -> data = first -> tail -> data;
	first -> tail = second ->tail;
	
	/* copy the head of second to the dummy (tail) of the first list */
	first_end.slist_node->data = second_begin.slist_node->data;
	first_end.slist_node->next = second_begin.slist_node->next;
	
	free(second -> head);
	free(second);
		
}

void PrintListOfInts(slist_ty * list)
{
	iterator_ty begin = SlistBegin(list);
	iterator_ty end = SlistEnd(list);
	op_func_ty print = PrintInt;

	assert(list);

	SlistForEach(begin, end, print, NULL);

	printf("\n");
}


/************************Helpers implementatios********************************/
static int IsDummy(iterator_ty iterator)
{
	return (iterator.slist_node->next == NULL);

}

int Add1(void *data, void *param)
{
	UNUSED(data);

	++(*(size_t *)param);
	return 0;
}

/* print int list (to be used with foreach) */
int PrintInt(void *data, void *param)
{
	UNUSED(param);

	printf("%d ",*(int *)data);
	return 0;
}