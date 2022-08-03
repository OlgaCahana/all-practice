/*******************************************************************************
*	Written by:		Olga Danielle Cahana									   *
*	Date:			16/12/221												   *
*	Reviewed by:	Shiran						    					 	   *
*																			   *
*******************************************************************************/
#include <assert.h> /* assert */
#include <stdio.h> /* fprintf */ 
#include <stdlib.h> /* size_t, malloc, realloc, free, max */
#include <string.h> /* memcpy */
#include "vector.h"

#define GROWTH_FACTOR 2
#define RETURN_IF_NULL(result)\
			if(result == NULL)\
			{\
				fprintf(stderr, "Failed, NULL result\n");\
				return NULL; \
			}
#define RETURN_STATUS_IF_NULL(result)\
			if(result == NULL)\
			{\
				fprintf(stderr, "Failed, NULL result\n");\
				return -1; \
			}

#define MAX(X, Y) (((X) < (Y)) ? (Y) : (X))			
/*****************************Types********************************************/
struct vector 
{
	char *vector_start; 	/* char type for convinience only; 
							 * vector can hold any type			*/	
	size_t element_size;
	size_t vector_size;		/* in elements 						*/
	size_t capacity;
	size_t init_capacity;
};

/************************Implementaion*****************************************/

/******************************************************************************
* Function Description: returns a pointer to an empty dynamic vector DS.   
* Arguments: size of vector elements (in bytes), capacity of vec (in elem).
* Return value: Pointer to vector.
* Notes: Return NULL in case of failure

* Time Complexity: O(1)
*******************************************************************************/
vector_ty *VectorCreate(size_t element_size, size_t capacity)
{
	vector_ty *vector = (vector_ty *)malloc(sizeof(vector_ty));
	RETURN_IF_NULL(vector);
	
	vector->element_size = element_size;
	vector->capacity = capacity;
	vector->vector_size = 0;
	vector->init_capacity = capacity;
	
	vector->vector_start = (char *)malloc(element_size * capacity * sizeof(char));
	if(vector->vector_start == NULL)
	{
		fprintf(stderr,"Memory allocation failed!");
		free(vector);
		return NULL;
	} 
	
	return vector;
}

/******************************************************************************
* Function Description: destroys the vector	       
* Arguments: pointer to a dynamic vector structure
* Return value: none
* Notes:

* Time Complexity: O(1)
*******************************************************************************/
void VectorDestroy(vector_ty *vector)
{
	
	free(vector->vector_start);
	free(vector);
}

/******************************************************************************
* Function Description: Points to element vector in specified idx.
* Arguments: Pointer to vector, idx.
* Return value: Pointer to element in idx
* Notes: 1. Undefined in case of index out of boundary.
*		 2. Repeat memory allocations may make the pointer redundant.
*		 	Must be used before each operation.
*  
* Time Complexity: O(1)
*******************************************************************************/
void *VectorGetElem(const vector_ty *vector, size_t idx)
{
	assert(vector);
	assert(idx < vector->vector_size);
	
	return (vector->vector_start + idx * vector->element_size);
}

/*****************************Super advanced ***********************************
* Function Description: Inserts	an element to the vector at specified index
* Arguments: Vector pointer, index, element to add
* Return value: int status
* Notes: Return error in case of failure.

* Time Complexity: O(n)
*******************************************************************************/
/*int VectorAddElem(vector_ty *vector, size_t idx, const void *elem)
{
	return 0;
}*/

/******************************************************************************
* Function Description: Inserts	an element to the end of the vector.
* Arguments: Vector pointer, element to add
* Return value: int status
* Notes: Return error in case of failure.

* Time Complexity: amortized O(1)
*******************************************************************************/
int VectorPushBack(vector_ty *vector, const void *elem)
{
	char *temp_realloc = NULL;
	size_t new_capacity = (vector->capacity == 0 ? 1 : vector->capacity) *
													   GROWTH_FACTOR;
	
	assert(vector);
	
	/* if the vector is full, resize  */
	if(vector->vector_size == vector->capacity)
	{
		temp_realloc = 
			 realloc(vector->vector_start, new_capacity * vector->element_size);
		RETURN_STATUS_IF_NULL(temp_realloc);
		
		vector->vector_start = temp_realloc;
		vector->capacity = new_capacity;
	}
	/* copy the element to vector end */
	memcpy((vector->vector_start + vector->vector_size * vector->element_size),
	 		elem, 
	 		vector->element_size);
	 
	++(vector->vector_size);
	
	return 0;
}

/******************************************************************************
* Function Description: Deletes the last element of vector. If the vector is only 
* 1/4 full, it will be recized to 1/2 of its size, but it will never recized to be
* smaller than the initial capacity provided by the user. If the actual capacity 
* is smaller then the initial, the vector will not be recized. 
* Arguments: Pointer to vector.
* Return value: void

* Time Complexity: O(1)
*******************************************************************************/
void VectorPopBack(vector_ty *vector)
{
	int realloc_size = MAX(vector->init_capacity, 
							(vector->capacity) / GROWTH_FACTOR); 
	
	assert(vector);
	assert(vector->vector_size > 0);
	
	--(vector->vector_size);

	/* in case the capacity smaller than the init capacity, i.e the ShrinkToFit was 
	 * previously called, the vector will not be recized further */
	if(vector->capacity < vector->init_capacity)
	{
		return;
	}

	/* resize to realloc_size */
	if(vector->vector_size == (vector->capacity) / 4u)
	{
		vector->vector_start = realloc(vector->vector_start, realloc_size);
		vector->capacity =  realloc_size;		
	}
}

/******************************************************************************
* Function Description: Returns the current capacity.
* Arguments: Pointer to vector.
* Return value: Current capacity.
* Notes:
* 
* Time Complexity: O(1)
*******************************************************************************/
size_t VectorCapacity(const vector_ty *vector)
{
	assert(vector);
	
	return vector->capacity;
}

/******************************************************************************
* Function Description: Returns the number of elements in vector.
* Arguments: Pointer to vector.
* Return value: Number of elements in vector.
* Notes:
* 
* Time Complexity: O(1)
*******************************************************************************/
size_t VectorSize(const vector_ty *vector)
{
	assert(vector);
	
	return vector->vector_size;
}

/******************************************************************************
* Function Description: Expands memory (in terms of elements) to new capacity.
* Arguments: Pointer to vector, new capacity.
* Return value: int status
* Notes: 1. Return error in case of failure.
* 		 2. Only changes capacity if new_capacity is greater than capacity.
* 
* Time Complexity: O(1)
*******************************************************************************/
int VectorReserveSize(vector_ty *vector, size_t new_capacity)
{/* TODO: do we need assert if we have the if???*/
	char *temp_realloc = NULL;

	assert(vector);
	assert(new_capacity > vector->capacity);

	/* if the new capacity smaller than the current, return */
	if(new_capacity <= vector->capacity)
	{
		return 0;
	}

	/* resize the vector according to new capacity */
	temp_realloc = realloc(vector->vector_start, new_capacity * vector->element_size);
	RETURN_STATUS_IF_NULL(temp_realloc);

	vector->vector_start = temp_realloc;
	vector->capacity = new_capacity;

	return 0;
}

/******************************************************************************
* Function Description: Diminish capacity to to size.
* Arguments: Pointer to vector.
* Return value: void
* Notes: Does nothing if vector size is 0;
* 
* Time Complexity: O(1)
*******************************************************************************/
void VectorShrinkToSize(vector_ty *vector)
/*TODO: realloc can fail when resizing to smaller size, teturn status instead void*/
{
	char *temp_realloc = NULL;
	
	assert(vector);

	/* uses if so we not accidently free the vector, 
	 * since realloc with 0 size argument equivelent to calling free() */
	if(vector->vector_size == 0)
	{
		return;
	}
	
	temp_realloc = realloc(vector->vector_start, 
						   vector->vector_size * vector->element_size);
	vector->vector_start = temp_realloc;
	vector->capacity = vector->vector_size;
}


