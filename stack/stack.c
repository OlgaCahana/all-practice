/*******************************************************************************
*	Written by:		Olga Danielle Cahana									   *
*	Date:			14/12/221												   *
*	Reviewed by:	Tal							    					 	   *
*																			   *
*******************************************************************************/
#include <assert.h> /* assert */
#include <stdio.h> /* printf */ 
#include <stdlib.h> /* size_t, malloc, free */
#include <string.h> /* memcpy */
#include "../include/stack.h"

#define RETURN_IF_NULL(result)\
			if(result == NULL)\
			{\
				fprintf(stderr, "Failed, NULL result\n");\
				return NULL; \
			}
			
/*****************************Types********************************************/
struct stack
{
	char *top;
	char *arr;
	size_t elem_size;
	size_t capacity;
};

/******************************************************************************
* Function Description: returns a pointer to an empty stack data structure      
* Arguments: size of stack element (in bytes), capacity of the stack
* Return value: pointer to a stack.
* Notes: return NULL in case of failure

* Time Complexity: O(1)
*******************************************************************************/
stack_ty *StackCreate(size_t element_size, size_t capacity)
{
	stack_ty *stack = NULL;

	assert(element_size > 0);
	assert(capacity > 0);
	
	stack = (stack_ty *)malloc((sizeof(stack_ty) + 
									   capacity * element_size * sizeof(char)));
	RETURN_IF_NULL(stack);

	stack->arr = (char *)stack + sizeof(stack_ty); /* also can be: stack->arr = (char *)(stack + 1) */
	stack->top = stack->arr;
	
	stack->elem_size = element_size;
	stack->capacity = capacity;

	return stack;
}


/******************************************************************************
* Function Description: destroys the stack	       
* Arguments: pointer to a stack structure
* Return value: none
* Notes: 

* Time Complexity: O(1)
*******************************************************************************/
void StackDestroy(stack_ty *stack)
{
	assert(stack);
	
	free(stack);
	stack = NULL;
}

/******************************************************************************
* Function Description: removes the last inserted element from the stack.	       
* Arguments: stack pointer.
* Return value: none.
* Notes: undefined in case of empty stack

* Time Complexity: O(1)
*******************************************************************************/
void StackPop(stack_ty *stack)
{
	assert(stack);
	assert(!StackIsEmpty(stack));
	
	stack->top -= stack->elem_size;
}

/******************************************************************************
* Function Description: inserts	an element to the array on the outermost posistion
* Arguments: stack pointer, pointer to the inserted element.
* Return value: none.
* Notes: undefined if stack is full

* Time Complexity: O(1)
*******************************************************************************/
void StackPush(stack_ty *stack, const void *elem)
{	
	assert(stack);
	assert(stack->capacity > StackSize(stack));
	
/*	if((stack->capacity - StackSize(stack)) < 1u)
	{
		fprintf(stderr, "Not enough space in stack to push a new element!\n");
		return;
	} */
	
	memcpy(stack->top, elem, stack->elem_size);
	
	stack->top += stack->elem_size;
	
}

/******************************************************************************
* Function Description: returns the value of the top-most element without popping	       
* Arguments: stack pointer
* Return value: pointer to the top-most element.
* Notes: 

* Time Complexity: O(1)
*******************************************************************************/
void *StackPeek(const stack_ty *stack)
{
	assert(stack);
	
	return (void *)(stack->top - stack->elem_size);
}

/******************************************************************************
* Function Description: returns the number of stacked elements.	       
* Arguments: stack pointer.
* Return value: number of elements.
* Notes: 

* Time Complexity: O(1)
*******************************************************************************/
size_t StackSize(const stack_ty *stack)
{
	assert(stack);
	assert(stack->elem_size > 0);
	
	return ((stack->top - stack->arr)/(stack->elem_size));
}

/******************************************************************************
* Function Description: returns true if stack is empty, false otherwise.	       
* Arguments: stack pointer.
* Return value: result of size check
* Notes: 

* Time Complexity: O(1)
*******************************************************************************/
int StackIsEmpty(const stack_ty *stack)
{
	assert(stack);
	
	return (stack->top == stack->arr);
}

/******************************************************************************
* Function Description: max capacity of the stack.	       
* Arguments: stack pointer.
* Return value: return stack capacity
* Notes: 

* Time Complexity: O(1)
*******************************************************************************/
size_t StackCapacity(const stack_ty *stack)
{
	assert(stack);
	
	return stack->capacity;
}


