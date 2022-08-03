/*******************************************************************************
*	Written by:		Olga Danielle Cahana									   *
*	Date:			16/12/221												   *
*	Reviewed by:	Shiran							    					   *
*																			   *
*******************************************************************************/
#include <stdio.h> /* printf */ 
#include <stddef.h> /* size_t, sizeof */

#include "../include/vector.h"


/****************Tests declarations********************************************/
static void TestVectorOfInts();
/*static void TestStackOfSize_7_Elemnts();*/


/****************************Main********************************************/
int main(void)
{

	TestVectorOfInts();
/*	TestStackOfSize_7_Elemnts();	*/
			
	return 0;

}

/***********************Tests Implementation***********************************/
static void TestVectorOfInts()
{
	vector_ty *my_vector = NULL;
	size_t capacity = 0;
	const size_t elem_size = 4;
	int elem1 = 5, elem2 = 123, elem3 = -1233;
	int *val = NULL;
	size_t i = 0;
	

	/***************** Test1: Initial capacity = 0:*********************************/	
	printf("Testing vector of int elments, init capacity is 0:\n");
	

	/* Create my_vector */
	capacity = 0;
	my_vector = VectorCreate(elem_size, capacity);

	my_vector != NULL ?
			printf("New vector created\t\tTest Passed\n") :
			printf("Failed to create vector.\t\tTest Failed!\n"); 

	/* Check size of empty vector */
	VectorSize(my_vector) == 0 ?
		printf("Vector size is 0. \t\tTest Passed\n"):
		printf("VectorSize test on empty vector Failed!\n");
	
	/* Check vector inital capacity */	
	VectorCapacity(my_vector) == capacity ?
		printf("Capacity is: %lu \t\t\tTest Passed\n", capacity):
		printf("Wrong capacity size. \tTest Failed!\n");
	
	/* Push an element to the vector - recizing from 0 to 2 */	
	VectorPushBack(my_vector, &elem1);
	printf("Element Pushed\n");

	/* Check my_vector capacity */	
	VectorCapacity(my_vector) == 2 ?
		printf("Capacity is: 2 \t\t\tTest Passed\n"):
		printf("Wrong capacity size. \t\tTest Failed!\n");
	
	/* Check size of non empty vector */
	VectorSize(my_vector) == 1 ?
		printf("Vector size is 1. \t\tTest Passed\n"):
		printf("VectorSize test on nonempty vector \tTest Failed!\n");
		
	/* Push another element to my vector - No recizing */
	VectorPushBack(my_vector, &elem2);
	printf("Element Pushed\n");

	/* Check my_vector capacity */	
	VectorCapacity(my_vector) == 2 ?
		printf("Capacity is: 2 \t\t\tTest Passed\n"):
		printf("Wrong capacity size. Test Failed!\n");
	
	/* Check size of vector after Push */
	VectorSize(my_vector) == 2 ?
		printf("Vector size is 2. \t\tTest Passed\n"):
		printf("VectorSize test on nonempty vector Failed!\n");
	
	/* Pop an element - No recizing: capacity = 2, size after pop = 1 */	
	VectorPopBack(my_vector);
	printf("Element Popped\n");

	/* Check my_vector capacity */	
	VectorCapacity(my_vector) == 2 ?
		printf("Capacity is: 2 \t\t\tTest Passed\n"):
		printf("Wrong capacity size. Test Failed!\n");

	/* Check size of empty vector */
	VectorSize(my_vector) == 1 ?
		printf("Vector size is 1. \t\tTest Passed\n"):
		printf("VectorSize test on nonempty vector Failed!\n\n");

	/* Pop an element - recizing from 2 to 0 */	
	VectorPopBack(my_vector);
	printf("Element Popped\n");

	/* Check my_vector capacity */	
	VectorCapacity(my_vector) == 1 ?
		printf("Capacity is 0 \t\t\tTest Passed\n"):
		printf("Wrong capacity size. Test Failed!\n");

	/* Check size of empty vector */
	VectorSize(my_vector) == 0 ?
		printf("Vector size is 0. \t\tTest Passed\n"):
		printf("VectorSize test on empty vector Failed!\n");

	/* Shrink to size on empty vector*/ 
	VectorShrinkToSize(my_vector);
	
	/* Free empty vector */
	VectorDestroy(my_vector);

/***************Test2 - common scenario: vector of int with capacity 10 ****/

	printf("\nTesting vector of int elments, init capacity is 10:\n\n");
	
	/* Create my_vector */
	capacity = 10;
	my_vector = VectorCreate(elem_size, capacity);

	my_vector != NULL ?
			printf("New vector created\t\tTest Passed\n") :
			printf("Failed to create vector.\t\tTest Failed!\n"); 

	/* Check size of empty vector */
	VectorSize(my_vector) == 0 ?
		printf("Vector size is 0. \t\tTest Passed\n"):
		printf("VectorSize test on empty vector Failed!\n");
	
	/* Check vector inital capacity */	
	VectorCapacity(my_vector) == capacity ?
		printf("Capacity is: %lu \t\tTest Passed\n", capacity):
		printf("Wrong capacity size. \tTest Failed!\n");
	
	/* Push an element to the vector */	
	VectorPushBack(my_vector, &elem1);
	printf("Element Pushed\n");

	/* Check size of non empty vector */
	VectorSize(my_vector) == 1 ?
		printf("Vector size is 1. \t\tTest Passed\n"):
		printf("VectorSize test on nonempty vector \tTest Failed!\n");

	/* Pop an element */	
	VectorPopBack(my_vector);
	printf("Element Popped\n");
	
	/* Check size of vector after Pop */
	VectorSize(my_vector) == 0 ?
		printf("Vector size is 0. \t\tTest Passed\n"):
		printf("VectorSize test on empty vector Failed!\n");

	/* reserve on empty vector */
	VectorReserveSize(my_vector, 15);
	printf("Resreve size 15\n");
	VectorCapacity(my_vector) == 15 ?
		printf("Capacity is: 15 \t\tTest Passed\n"):
		printf("Wrong capacity size. Test Failed!\n");

	/* reserve for smaller capacity - should do nothing */
	VectorReserveSize(my_vector, 0);
	printf("Reserve size 0 (shoulde do nothing)\n");
	VectorCapacity(my_vector) == 15 ?
		printf("Capacity is: 15 \t\tTest Passed\n"):
		printf("Wrong capacity size. Test Failed!\n");


	/* Push 31 elemnts, the capacity should be doubled twice */
	printf("Pushing 31 elements:\n");
	while (i < 31)
	{
		VectorPushBack(my_vector, &elem3);
		printf("Pushed element num %lu\n", i+1);
		++i;
	}
		
	/* Check size of vector after Push */
	VectorSize(my_vector) == 31 ?
		printf("There are 31 elements in my_vector. \tTest Passed\n"):
		printf("VectorSize test on nonempty vector Failed!\n");

	VectorCapacity(my_vector) == 60 ?
		printf("Capacity is: 60 \t\t\tTest Passed\n"):
		printf("Wrong capacity size. Test Failed!\n");

	/* Shrink to size */ 
	VectorShrinkToSize(my_vector);
	printf("Shrinking\n");

	VectorSize(my_vector) == 31 ?
		printf("There are 31 elements in my_vector. \tTest Passed\n"):
		printf("VectorSize test on nonempty vector Failed!\n");

	VectorCapacity(my_vector) == 31 ?
		printf("Capacity is: 31 \t\t\tTest Passed\n"):
		printf("Wrong capacity size. Test Failed!\n");
	
	/* Get element value */ 
	val = (int *)VectorGetElem(my_vector,1);
	*val == elem3 ?
		printf("Top element value is: %d. \t\tTest Passed\n", *val) :
		printf("GetElement test Failed!!\n"); 
	
	/* Pop all 31 elements, print the capacity when changing */
	printf("Pop All elements, print the capacity when changing\n");
	i = 0;
	while (i < 31)
	{
		VectorPopBack(my_vector);
		printf("Element %lu popped\n", i+1);
		++i;
	}
	VectorSize(my_vector) == 0 ?
		printf("There are 0 elements in my_vector. \tTest Passed\n"):
		printf("VectorSize test on nonempty vector Failed!\n");

	VectorCapacity(my_vector) == 10 ?
		printf("Capacity is: 10 \t\t\tTest Passed\n"):
		printf("Wrong capacity size. Test Failed!\n");
	/* Pop an element */	
	

	


	VectorDestroy(my_vector);

	/***************Undefined behaviour Tests***************************************/
	/* Pop an element from empty vector - undefined behavior */	
	/*VectorPopBack(my_vector);
	printf("Element Popped\n"); */

	/*GetElem on empty vector/ wrong index */

	/*******************************************************************************/
	/* Try to Push element exceeding the vector capacity */
/*	printf("\nTry to Push element exceeding the vector capacity\n");
	VectorPush(my_vector, &elem2);  */
	
	/* Destroy my_vector */
	/*VectorDestroy(my_vector);*/
	
}



/****************************Helpers Implementation****************************/

