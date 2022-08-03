/*******************************************************************************
*	Written by:		Olga Danielle Cahana									   *
*	Date:			14/12/221												   *
*	Reviewed by:	Tal							    					 	   *
*																			   *
*******************************************************************************/

#ifndef __STACK_H__
#define __STACK_H__

#include <stddef.h> /* size_t */

typedef struct stack stack_ty;

/******************************************************************************
* Function Description: returns a pointer to an empty stack data structure      
* Arguments: size of stack element (in bytes), capacity of the stack
* Return value: pointer to a stack.
* Notes: return NULL in case of failure

* Time Complexity: O(1)
*******************************************************************************/
stack_ty *StackCreate(size_t element_size, size_t capacity);


/******************************************************************************
* Function Description: destroys the stack	       
* Arguments: pointer to a stack structure
* Return value: none
* Notes: 

* Time Complexity: O(1)
*******************************************************************************/
void StackDestroy(stack_ty *stack);

/******************************************************************************
* Function Description: removes the last inserted element from the stack.	       
* Arguments: stack pointer.
* Return value: none.
* Notes: undefined in case of empty stack

* Time Complexity: O(1)
*******************************************************************************/
void StackPop(stack_ty *stack);

/******************************************************************************
* Function Description: inserts	an element to the array on the outermost posistion
* Arguments: stack pointer, pointer to the inserted element.
* Return value: none.
* Notes: undefined if stack is full

* Time Complexity: O(1)
*******************************************************************************/
void StackPush(stack_ty *stack, const void *elem);

/******************************************************************************
* Function Description: returns the value of the top-most element without popping	       
* Arguments: stack pointer
* Return value: pointer to the top-most element.
* Notes: 

* Time Complexity: O(1)
*******************************************************************************/
void *StackPeek(const stack_ty *stack);

/******************************************************************************
* Function Description: returns the number of stacked elements.	       
* Arguments: stack pointer.
* Return value: number of elements.
* Notes: 

* Time Complexity: O(1)
*******************************************************************************/
size_t StackSize(const stack_ty *stack);

/******************************************************************************
* Function Description: returns true if stack is empty, false otherwise.	       
* Arguments: stack pointer.
* Return value: result of size check
* Notes: 

* Time Complexity: O(1)
*******************************************************************************/
int StackIsEmpty(const stack_ty *stack);

/******************************************************************************
* Function Description: max capacity of the stack.	       
* Arguments: stack pointer.
* Return value: return stack capacity
* Notes: 

* Time Complexity: O(1)
*******************************************************************************/
size_t StackCapacity(const stack_ty *stack);



#endif /*__STACK_H__*/
