/*******************************************************************************
*	Written by:		Olga Danielle Cahana									   *
*	Date:			31/12/221												   *
*	Reviewed by:	Shiran						    					 	   *
*																			   *
*******************************************************************************/
#include <assert.h> /* assert */
#include <stdio.h> /* fprintf */ 
#include <stdlib.h> /* size_t, malloc, free*/
#include "dlist.h"

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
	node_ty *prev;
	node_ty *next;
};

struct dlist
{
	node_ty *head;
	node_ty *tail;
};

/***************************Helpers declarations*******************************/

/* Return true if the iterator is iterator to the dummy node*/
static int IsDummy(iterator_ty iterator);

/* adds 1 to param, used in count with foreach */
static int Add1(void *data, void *param);

/******************************************************************************/
/*							Implementaion			     				      */
/*******************************************************************************
* Function Description: returns a pointer to an empty dlist DS.   
* Arguments: - 
* Return value: Pointer to dlist.
* Notes: Return NULL in case of failure

* Time Complexity: O(1)
*******************************************************************************/

dlist_ty *DlistCreate(void)
{
	dlist_ty *list = (dlist_ty *)malloc(sizeof(dlist_ty));
	RETURN_IF_NULL(list);
	
	/* Create first dummy */
	list -> head = (node_ty *)malloc(sizeof(node_ty));
	if(list -> head == NULL)
	{
		free(list);
		return NULL;
	}
	/* Create second dummy */
	list -> tail = (node_ty *)malloc(sizeof(node_ty));
	if(list -> tail == NULL)
	{
		free(list -> head);
		free(list);
		return NULL;
	}

	list -> head -> data = list;
	list -> head -> next = list -> tail;
	list -> head -> prev = NULL; 
	
	list -> tail -> data = list;
	list -> tail -> next = NULL;
	list -> tail -> prev = list -> head;

	return list;
}


/******************************************************************************
* Function Description: destroys the dlist	       
* Arguments: pointer to a dlist structure
* Return value: none
* Notes:

* Time Complexity: O(n)
*******************************************************************************/
void DlistDestroy(dlist_ty *dlist)
{
	/* TODO: destroy should work on NULL, thus can't implement this with remove */
	iterator_ty start = DlistBegin(dlist);
	
	assert(dlist);
	
	/* remove all the nodes until dummy node is reached */
	while(start.dlist_node -> next != NULL)
	{
		start = DlistRemove(start);
	}

	free(dlist -> head);
	free(dlist -> tail);

	/* free the dlist struct */
	free(dlist);	
}


/******************************************************************************
* Function Description: return a boolian if the list is empty	       
* Arguments: pointer to a dlist structure
* Return value: 1 empty 0 not
* Notes:

* Time Complexity: O(1)
*******************************************************************************/
int DlistIsEmpty(const dlist_ty *dlist)
{
	assert(dlist);
	
	return (dlist -> head -> next == dlist -> tail);
}


/******************************************************************************
* Function Description: insert a node before begginig of a given node ds.   
* Arguments: pointer to node,  void *data to insert, pointer to dlist.
* Return value: iterator to the new element.
* Notes: If fails to insert, returns pointer to dummy
* Time Complexity: O(1) in case of failure O(n)
*******************************************************************************/
iterator_ty DlistInsertBefore(iterator_ty where, const void *data)
{
	node_ty * new_node = NULL;

	assert(where.dlist_node);
	
	new_node = (node_ty *)malloc(sizeof(node_ty));
	/* if mem allocation failed, return dummy iterator */
	if(new_node == NULL)
	{
		while(!IsDummy(where))
		{
			where = DlistNext(where);
		}
		/*TODO: errno */
		printf("Memory allocation Failed!\n");
		
		return where;
	}
	
	new_node -> data = (void *)data;
	where.dlist_node -> prev -> next = new_node;
	new_node -> prev = where.dlist_node -> prev;
	new_node -> next = where.dlist_node;
	where.dlist_node -> prev = new_node;

	return DlistPrev(where);
}


/******************************************************************************
* Function Description: remove a node before begginig of a given node ds.   
* Arguments: pointer to head, void *data to insert, pointer to dlist.
* Return value: iterator to the next element in the list  
* Notes: 
2. removing last node (dummy) will cause undefined behaviour.

* Time Complexity: O(1)

*******************************************************************************/
iterator_ty DlistRemove(iterator_ty where)
{
	iterator_ty temp;

	/* assert if where holds the dummy node */
	/* the dummy node should not be removed */
	assert(!IsDummy(where));
	assert(where.dlist_node);
	
	temp = DlistNext(where);

	where.dlist_node -> prev -> next = where.dlist_node -> next;
	where.dlist_node -> next -> prev = where.dlist_node -> prev;

	free(where.dlist_node);

	return temp;
}


/******************************************************************************
* Function Description: insert a node before the head of Dlist.   
* Arguments: pointer to dlist,  void *data to insert.
* Return value: iterator to new element.
* Notes: 
* Time Complexity: O(1)
*******************************************************************************/
iterator_ty DlistPushFront(dlist_ty *dlist, const void *data)
{
	iterator_ty start;
	
	assert(dlist);

	start = DlistBegin(dlist);
	
	return DlistInsertBefore(start, data);
}


/******************************************************************************
* Function Description: insert a node before the tail of Dlist.   
* Arguments: pointer to node,  void *data to insert.
* Return value: iterator to new element.
* Notes: 
* Time Complexity: O(1)
*******************************************************************************/
iterator_ty DlistPushBack(dlist_ty *dlist, const void *data)
{
	iterator_ty end;
	
	assert(dlist);

	end = DlistEnd(dlist);
	
	return DlistInsertBefore(end, data);
}


/******************************************************************************
* Function Description: remove the node of the begginig of a given Dlist.   
* Arguments: pointer to dlist.
* Return value: void *data
* Notes:  removing from an empty Dlist will cause undefined behaviour.
* Time Complexity: O(1)

*******************************************************************************/
void *DlistPopFront(dlist_ty *dlist)
{
	iterator_ty start = {NULL};
	void * data = NULL;
	
	assert(dlist);
	assert(!DlistIsEmpty(dlist));

	start = DlistBegin(dlist);
	data = DlistGetData(start);
	DlistRemove(start);
	
	return data;
}


/******************************************************************************
* Function Description: remove the node from the end of a given dlist.   
* Arguments: pointer to dlist.
* Return value:  void *data
* Notes:  removing from an empty Dlist will cause undefined behaviour.
* Time Complexity: O(1)

*******************************************************************************/
void *DlistPopBack(dlist_ty *dlist)
{
	iterator_ty end;
	void * data;

	assert(dlist);
	assert(!DlistIsEmpty(dlist));

	end = DlistPrev(DlistEnd(dlist));
	data = DlistGetData(end);
	DlistRemove(end);

	return data;
}


/******************************************************************************
* Function Description: count num of elements in Dlist.   
* Arguments: pointer to head Dlist,
* Return value: size of list
* Notes: 
*  
* Time Complexity: O(n)
*******************************************************************************/
size_t DlistSize(const dlist_ty *dlist)
{
	size_t count = 0;
	iterator_ty begin = DlistBegin(dlist);
	iterator_ty end = DlistEnd(dlist);

	assert(dlist);

	while(!DlistIsSameIter(begin, end))
	{
		++count;
		begin = DlistNext(begin);
	}
	
	return count;
}


/******************************************************************************
* Function Description: return a beginning of a dlist
* Arguments: pointer to head.
* Return value: head dlist.
* Notes: Return NULL in case of empty dlist

* Time Complexity: O(1)
*******************************************************************************/
iterator_ty DlistBegin(const dlist_ty *dlist)
{
	iterator_ty iter;

	assert(dlist);
	assert(dlist->head);
	
	iter.dlist_node = dlist -> head -> next;
	DEBUG_ONLY(iter.list = (dlist_ty *)dlist);
	return iter;
}


/******************************************************************************
* Function Description: return the end of a dlist
* Arguments: pointer to head.
* Return value: last node in dlist.(dummy node)
* Notes: Return NULL in case of empty dlist

* Time Complexity: O(1)
*******************************************************************************/
iterator_ty DlistEnd(const dlist_ty *dlist)
{
	iterator_ty iter;

	assert(dlist);
	assert(dlist->tail);
	
	iter.dlist_node = dlist -> tail;
	DEBUG_ONLY(iter.list = (dlist_ty *)dlist);
	return iter;
}


/******************************************************************************
* Function Description: return the next node iterator in a dlist
* Arguments: pointer to node.
* Return value: iterator of the next node in dlist.
* Notes: Return iterator holding NULL value in case of empty dlist

* Time Complexity: O(1)
*******************************************************************************/
iterator_ty DlistNext(iterator_ty current)
{	
	assert(current.dlist_node);

	current.dlist_node = current.dlist_node -> next;
	return current;
}


/******************************************************************************
* Function Description: return the previous node in a Dlist
* Arguments: iterator.
* Return value: iterator of the previous node in Dlist.
* Notes: undefined in case of first node

* Time Complexity: O(1)
*******************************************************************************/
iterator_ty DlistPrev(iterator_ty current)
{
	assert(current.dlist_node);

	current.dlist_node = current.dlist_node -> prev;
	return current;
}


/******************************************************************************
* Function Description: return the data of a given node 
* Arguments: Iterator to node.
* Return value: void * to data.
* Notes: Return NULL in case of empty dlist

* Time Complexity: O(1)
*******************************************************************************/
void *DlistGetData(const iterator_ty iterator)
{
	assert(iterator.dlist_node);
	
	return iterator.dlist_node->data;

}


/******************************************************************************
* Function Description: set data in a node of dlist 
* Arguments: pointer to node.
* Return value: node , data.
* Notes: Return status in case of success or failure
size of data must match data size of element

* Time Complexity: O(1)
*******************************************************************************/
void DlistSetData(iterator_ty iterator, void *data)
{
	assert(!IsDummy(iterator));
	assert(iterator.dlist_node);
	
	iterator.dlist_node -> data = data;
}


/******************************************************************************
* Function Description: returns true if two iterators are equal
* (hold the same node) 
* Arguments: two iterators
* Return value: true or false
* Notes: 

* Time Complexity: O(1)
*******************************************************************************/
int DlistIsSameIter(iterator_ty iter1, iterator_ty iter2)
{	
	/*TODO: do i need this assert?*/
	/* debug mode assert, both iterators belong to the same list */
	DEBUG_ONLY(assert(iter1.list == iter2.list));

	return iter1.dlist_node == iter2.dlist_node;
}


/******************************************************************************
* Function Description: foreach element in specified range, perform function.
* Arguments: iterator of start of range, iterator of end of range, function
* Return value: 1 if fail 0 if succsess & fuc stops upon first failure
* Notes: undefined behaviour if start and end not from the same list.

* Time Complexity: O(n)
*******************************************************************************/
int DlistForEach(iterator_ty start,
				 iterator_ty end,
				 op_func_ty op_func,
				 void *param)
{
	DEBUG_ONLY(assert(start.list == end.list));
	assert(start.dlist_node->prev); /* not first dummy */
	assert(op_func);
	assert(start.dlist_node);
	assert(end.dlist_node);
	
	while (!DlistIsSameIter(start,end))
	{
		if(op_func(start.dlist_node -> data, param) == 0)
		{
			start = DlistNext(start);
		}
		else 
		{
			return 1;
		}
	}

	return 0;
}
					
		
/******************************************************************************
* Function Description: find first occurrence of data in dlist.   
* Arguments: pointer to head, iterator.
* Return value: iterator of data
* Notes: undefined behaviour if start and end not from the same list.

* Time Complexity: O(n)
*******************************************************************************/
iterator_ty DlistFind(iterator_ty start,
 					  iterator_ty end, 
					  match_func_ty op_func,
					  void *param)
{
	DEBUG_ONLY(assert(start.list == end.list));
	assert(op_func);
	assert(start.dlist_node);
	assert(end.dlist_node);
	
	while (!DlistIsSameIter(start, end))
	{
		if(op_func(start.dlist_node -> data, param) == 0)
		{
			return start;
		}

		start = DlistNext(start); /* promote start iterator*/
	}

 /* matched data not found, promote start to the dummy node and return the dummy */
	while(!IsDummy(start))
	{
		start = DlistNext(start);
	}

	return start;	
}


/******************************************************************************
* Function Description: find occurrence of data in Dlist.   
* Arguments: iterator_ty start, iterator_ty end, match_func, void *param, 
			 dlist *dest
* Return value: number of match nodes, if fail return -1
* Notes: undefined behaviour if start and end not from the same list.
* Time Complexity: O(n)
*******************************************************************************/
int DlistMultiFind(iterator_ty start, iterator_ty end, dlist_ty *dest, 
					  				  match_func_ty op_func, void *param)
{
	int count = 0;

	assert(dest);
	assert(start.list == end.list);
	assert(op_func);
	assert(start.dlist_node);
	assert(end.dlist_node);

	while(! DlistIsSameIter(start, end))
	{
		/* find match */
		start = DlistFind(start, end, op_func, param);

		/* no matches were found in the range */
		if(IsDummy(start))
		{
			return count;
		}
		/*TODO: catch pushback return value */
		DlistPushBack(dest, DlistGetData(start));
		++count;
		start = DlistNext(start);
		
	}
	return count;
}						

						  
/******************************************************************************
* Function Description: slice range of nodes from start to end and insert 
		   to dest
* Arguments: iterator of start of range, iterator of end of range, 
			 iterator of dest 
* Return value: iterator to start of dest 
* Notes: undefined behaviour if start and end not from the same list.
		 can be cut to another list
		 dest cannot be in the range - undefined

* Time Complexity: O(1)
*******************************************************************************/
iterator_ty DlistSplice(iterator_ty start, iterator_ty end, iterator_ty dest)
{
	node_ty *temp = NULL;

	assert(!IsDummy(start));
	assert(end.dlist_node->prev);
	assert(start.list == end.list);
	assert(start.dlist_node);
	assert(end.dlist_node);
	assert(dest.dlist_node);
	
	end = DlistPrev(end);
	dest = DlistPrev(dest);
	temp = dest.dlist_node->next;  /* the OG dest */

	/* take out the start to end segment */
	start.dlist_node->prev->next = end.dlist_node->next;
	end.dlist_node->next->prev = start.dlist_node->prev;

	/* connect the segment to dest */
	dest.dlist_node->next = start.dlist_node;
	start.dlist_node->prev = dest.dlist_node;

	end.dlist_node->next = temp ;
	temp->prev = end.dlist_node;

	return dest;
}


/* this function will append 2 dlists: second to the end of first */
void DlistAppend(dlist_ty *first, dlist_ty *second)
{
	iterator_ty first_end;
	iterator_ty second_begin;
	
	assert(first);
	assert(second);
	
	first_end = DlistEnd(first);
	second_begin = DlistBegin(second);
	
	
	/* Update second dummy data to first list and Update the first list tail */
	second  ->  tail  ->  data = first  ->  tail  ->  data;
	first  ->  tail = second  -> tail;
	
	/* copy the head of second to the dummy (tail) of the first list */
	first_end.dlist_node -> data = second_begin.dlist_node -> data;
	first_end.dlist_node -> next = second_begin.dlist_node -> next;
	first_end.dlist_node -> next -> prev = first_end.dlist_node;
	
	free(second  ->  head -> next);
	free(second -> head);
	free(second);
		
}



/************************Helpers implementatios********************************/
/* return true if iterator holds the dummy node */
static int IsDummy(iterator_ty iterator)
{
	return (iterator.dlist_node -> next == NULL || 
								iterator.dlist_node -> prev == NULL);

}

static int Add1(void *data, void *param)
{
	UNUSED(data);

	++(*(size_t *)param);
	return 0;
}
