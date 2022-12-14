#ifndef __SLIST_H__
#define __SLIST_H__

#include <stddef.h> /*size_t*/

#ifndef NDEBUG
	#define DEBUG_ONLY(exp) exp;
#else
	#define DEBUG_ONLY(exp) 
#endif


typedef struct slist slist_ty;

typedef struct node node_ty;

typedef struct iterator iterator_ty;

/* Linked List struct */


/*DO NOT CHANGE*/
/*TODO:Perhaps if we use is equal we sould encpsulate iterator definition*/
struct iterator
{
	node_ty *slist_node;
	
	DEBUG_ONLY(slist_ty *list)
	
};

/*SlistForEach func prototype (returns 1 if fail 0 upon succsess) */
typedef int(*op_func_ty)(void *data, void *param);
/* SlistFind func prototype (returns 1 if fail 0 upon succsess) */
typedef int(*match_func_ty)(const void *data, void *param);

/******************************************************************************
* Function Description: returns a pointer to an empty slist DS.   
* Arguments: - 
* Return value: Pointer to slist.
* Notes: Return NULL in case of failure

* Time Complexity: O(1)
*******************************************************************************/
slist_ty *SlistCreate(void);

/******************************************************************************
* Function Description: destroys the slist	       
* Arguments: pointer to a slist structure
* Return value: none
* Notes:

* Time Complexity: O(n)
*******************************************************************************/
void SlistDestroy(slist_ty *slist);

/******************************************************************************
* Function Description: return a boolian if the list is empty	       
* Arguments: pointer to a slist structure
* Return value: 1 empty 0 not
* Notes:

* Time Complexity: O(1)
*******************************************************************************/
int SlistIsEmpty(const slist_ty *slist);

/******************************************************************************
* Function Description: insert a node before begginig of a given node ds.   
* Arguments: pointer to node,  void *data to insert, pointer to slist.
* Return value: iterator to the new element.
* Notes: 
* Time Complexity: O(1)
*******************************************************************************/
iterator_ty SlistInsertBefore(iterator_ty where, const void *data);

/******************************************************************************
* Function Description: remove a node before begginig of a given node ds.   
* Arguments: pointer to head, void *data to insert, pointer to slist.
* Return value: iterator to the next element in the list  
* Notes: 
2. removing last node (dummy) will cause undefined behaviour.

* Time Complexity: O(1)

*******************************************************************************/
iterator_ty SlistRemove(iterator_ty where);

/******************************************************************************
* Function Description: count num of elements in slist.   
* Arguments: pointer to head slist,
* Return value: size of list
* Notes: 
*  
* Time Complexity: O(n)
*******************************************************************************/
size_t SlistCount(const slist_ty *slist);

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
				 void *param);

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
					  void *param);


/******************************************************************************
* Function Description: return a beginning of a slist
* Arguments: pointer to head.
* Return value: head slist.
* Notes:

* Time Complexity: O(1)
*******************************************************************************/
iterator_ty SlistBegin(const slist_ty *slist);

/******************************************************************************
* Function Description: return the end of a slist
* Arguments: pointer to head.
* Return value: last node in slist.
* Notes:

* Time Complexity: O(1)
*******************************************************************************/
iterator_ty SlistEnd(const slist_ty *slist);

/******************************************************************************
* Function Description: return the next node in a slist
* Arguments: pointer to node.
* Return value: iterator of the next node in slist.
* Notes: 

* Time Complexity: O(1)
*******************************************************************************/
iterator_ty SlistNext(iterator_ty iterator);

/******************************************************************************
* Function Description: return the data of a given node 
* Arguments: pointer to node.
* Return value: void * to data.
* Notes: Return NULL in case of empty slist

* Time Complexity: O(1)
*******************************************************************************/
void *SlistGetData(const iterator_ty iterator);

/******************************************************************************
* Function Description: set data in a node of slist 
* Arguments: pointer to node.
* Return value: node , data.
* Notes: size of data must match data size of element

* Time Complexity: O(1)
*******************************************************************************/
void SlistSetData(iterator_ty iterator, void *data);

/******************************************************************************
* Function Description: returns true if two iterators are equal (hold the same node) 
* Arguments: two iterators
* Return value: true or false
* Notes: 

* Time Complexity: O(1)
*******************************************************************************/
int SlistIsEqual(iterator_ty iter1, iterator_ty iter2);


/******************************************************************************
* Function Description: rmake the append of 2 slists: second to the end of first 
* Arguments: two list pointers
* Return value: void
* Notes: 

* Time Complexity: O(1)
*******************************************************************************/
void SlistAppend(slist_ty *first, slist_ty *second);

/******************************************************************************
* Function Description: Prints the values, works on lists holding only integers 
* Arguments: two iterators
* Return value: true or false
* Notes: 

* Time Complexity: O(1)
*******************************************************************************/
void PrintListOfInts(slist_ty * list);

#endif /*__SLIST_H__*/

