/*******************************************************************************
*	Written by:		Olga Danielle Cahana									   *
*	Date:			14/12/221												   *
*	Reviewed by:	Tal							    					 	   *
*																			   *
*******************************************************************************/
#include <stdio.h> /* printf */ 
#include <stddef.h> /* size_t, sizeof */

#include "../include/stack.h"


/****************Tests declarations********************************************/
static void TestStackOfInts();
static void TestStackOfSize_7_Elemnts();


/****************************Main********************************************/
int main(void)
{

	TestStackOfInts();
	TestStackOfSize_7_Elemnts();	
			
	return 0;

}

/***********************Tests Implementation***********************************/
static void TestStackOfInts()
{
	const size_t capacity = 10;
	const size_t elem_size = 4;
	int elem1 = 5, elem2 = 123, elem3 = -1233;
	int *peek_val = NULL;
	size_t i = 0;
	
		
	/* Create my_stack */
	stack_ty *my_stack = StackCreate(elem_size, capacity);
	
	printf("Testing stack on int elments:\n");
	/* Check if empty */
	StackIsEmpty(my_stack) ?
		printf("Stack is empty. \t\t\tTest Passed\n"):
		printf("Stack is not empty. Test Failed!\n");
	
	/* Check size of empty stack */
	StackSize(my_stack) == 0 ?
		printf("There're 0 elements in my_stuck.\tTest Passed\n"):
		printf("StackSize test on empty stack Failed!\n");
	
	/* Check my_stack capacity */	
	StackCapacity(my_stack) == capacity ?
		printf("Capcity size is correct: %lu \t\tTest Passed\n", capacity):
		printf("Wrong capacity size. Test Failed!\n");
	
	/* Push an element to the stack */	
	StackPush(my_stack, &elem1);
	printf("Element Pushed\n");
	
	/* Check size of non empty stack */
	StackSize(my_stack) == 1 ?
		printf("There is 1 element in my_stuck. \tTest Passed\n"):
		printf("StackSize test on nonempty stack Failed!\n");
		
	/* Push another element to my stack */
	StackPush(my_stack, &elem2);
	printf("Element Pushed\n");
	
	/* Check size of stack after Push */
	StackSize(my_stack) == 2 ?
		printf("There are 2 elements in my_stuck. \tTest Passed\n"):
		printf("StackSize test on nonempty stack Failed!\n");
	
	/* Pop an element */	
	StackPop(my_stack);
	printf("Element Popped\n");
	
	/* Check size of stack after Pop */
	StackSize(my_stack) == 1 ?
		printf("There is 1 element in my_stuck. \tTest Passed\n"):
		printf("StackSize test on nonempty stack Failed!\n");
		
	StackPush(my_stack, &elem3);
	printf("Element Pushed\n");
	
	/* Check size of stack after Push */
	StackSize(my_stack) == 2 ?
		printf("There are 2 elements in my_stuck. \tTest Passed\n"):
		printf("StackSize test on nonempty stack Failed!\n");
	
	/* Peek */
	peek_val = (int *)StackPeek(my_stack);
	*peek_val == elem3 ?
		printf("Peek: top element value is: %d. \tTest Passed\n", *peek_val) :
		printf("Peek test Failed!!\n");
	
	/* Pop an element */	
	StackPop(my_stack);
	printf("Element Popped\n");
	
	/* Pop an element */	
	StackPop(my_stack);
	printf("Element Popped\n");
	
	/* Check size of stack after Pop */
	StackSize(my_stack) == 0 ?
		printf("There're 0 elements in my_stuck.\tTest Passed\n"):
		printf("StackSize test on empty stack Failed!\n");
	
	/* Push until the maximum capacity is reached */
	printf("\nPush %lu elements (max stack capacity)\n", capacity);	
	while(i < capacity)
	{
		StackPush(my_stack, &elem2);
		
		printf("Element Pushed. Stack size is: %lu\n", StackSize(my_stack));
		++i;
	}
	
	/* Try to Push element exceeding the stack capacity */
/*	printf("\nTry to Push element exceeding the stack capacity\n");
	StackPush(my_stack, &elem2);  */
	
	/* Destroy my_stack */
	StackDestroy(my_stack);
	
}

static void TestStackOfSize_7_Elemnts()
{
	const size_t capacity = 17;
	size_t i = 0;
	
	typedef struct seven 
	{
		int var;
		char ch1, ch2, ch3 ;
	}seven_ty;
	
	seven_ty elem = {777, 'a', 'b', 'c'};		
	
	
	/* Create my_stack */
	stack_ty *my_stack = StackCreate(sizeof(seven_ty), capacity);
	
	printf("\n\nTesting stack on elments with size of 7 bytes:\n");
	
	/* Check if empty */
	StackIsEmpty(my_stack) ?
		printf("Stack is empty. \t\t\tTest Passed\n"):
		printf("Stack is not empty. Test Failed!\n");
	
	/* Check size of empty stack */
	StackSize(my_stack) == 0 ?
		printf("There're 0 elements in my_stuck.\tTest Passed\n"):
		printf("StackSize test on empty stack Failed!\n");
	
	/* Check my_stack capacity */	
	StackCapacity(my_stack) == capacity ?
		printf("Capcity size is correct: %lu \t\tTest Passed\n", capacity):
		printf("Wrong capacity size. Test Failed!\n");
	
	/* Push an element to the stack */	
	StackPush(my_stack, &elem);
	printf("Element Pushed\n");
	
	/* Check size of non empty stack */
	StackSize(my_stack) == 1 ?
		printf("There is 1 element in my_stuck. \tTest Passed\n"):
		printf("StackSize test on nonempty stack Failed!\n");
		
	/* Push another element to my stack */
	StackPush(my_stack, &elem);
	printf("Element Pushed\n");
	
	/* Check size of stack after Push */
	StackSize(my_stack) == 2 ?
		printf("There are 2 elements in my_stuck. \tTest Passed\n"):
		printf("StackSize test on nonempty stack Failed!\n");
	
	/* Pop an element */	
	StackPop(my_stack);
	printf("Element Popped\n");
	
	/* Check size of stack after Pop */
	StackSize(my_stack) == 1 ?
		printf("There is 1 element in my_stuck. \tTest Passed\n"):
		printf("StackSize test on nonempty stack Failed!\n");
		
	StackPush(my_stack, &elem);
	printf("Element Pushed\n");
	
	/* Check size of stack after Push */
	StackSize(my_stack) == 2 ?
		printf("There are 2 elements in my_stuck. \tTest Passed\n"):
		printf("StackSize test on nonempty stack Failed!\n");
	
	/* Peek 
	peek_val = (int *)StackPeek(my_stack);
	*peek_val == elem3 ?
		printf("Peek: top element value is: %d. \tTest Passed\n", *peek_val) :
		printf("Peek test Failed!!\n"); */
	
	/* Pop an element */	
	StackPop(my_stack);
	printf("Element Popped\n");
	
	/* Pop an element */	
	StackPop(my_stack);
	printf("Element Popped\n");
	
	/* Check size of stack after Pop */
	StackSize(my_stack) == 0 ?
		printf("There're 0 elements in my_stuck.\tTest Passed\n"):
		printf("StackSize test on empty stack Failed!\n");
	
	/* Push until the maximum capacity is reached */
	printf("\nPush %lu elements (max stack capacity)\n", capacity);	
	while(i < capacity)
	{
		StackPush(my_stack, &elem);
		
		printf("Element Pushed. Stack size is: %lu\n", StackSize(my_stack));
		++i;
	}
	
	/* Try to Push element exceeding the stack capacity */
/*	printf("\nTry to Push element exceeding the stack capacity\n");
	StackPush(my_stack, &elem);  */
	
	/* Destroy my_stack */
	StackDestroy(my_stack);

}

/****************************Helpers Implementation****************************/

