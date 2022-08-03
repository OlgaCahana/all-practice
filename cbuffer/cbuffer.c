/*******************************************************************************
*	Written by:		Olga Danielle Cahana									   *
*	Date:			29/12/221												   *
*	Reviewed by:							    					 	   *
*																			   *
*******************************************************************************/
#include <stdio.h> /* printf, BUFSIZ*/ 
#include <stdlib.h> /* size_t, malloc, free */
#include <sys/types.h> /* ssize_t */
#include <string.h> /* memcpy */
#include <assert.h> /* assert */

#include "cbuffer.h"


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

#define OFFSETOF(st, m)\
		((size_t)&(((st *)0) -> m))
		
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))		
/*****************************Types********************************************/
struct cbuffer
{
	char *read;
	char *write;
	size_t bufsiz; 
	char buffer[1];
};

/************************Implementaion*****************************************/
/******************************************************************************
* Function Description: creates new cbuffer data structure
* Arguments: capacity of buffer
* Return value: pointer to new cbuffer
* Notes: returns NULL if failure 

* Time Complexity: O(1)
*******************************************************************************/
cbuffer_ty *CBufferCreate(size_t bufsiz)
{
	cbuffer_ty *cbuffer = NULL;
	
	assert(bufsiz <= BUFSIZ);
	
	cbuffer = (cbuffer_ty  *)malloc(OFFSETOF(cbuffer_ty, buffer) + (bufsiz + 1) * sizeof(char));
	RETURN_IF_NULL(cbuffer);
	
	cbuffer -> bufsiz = bufsiz;
	cbuffer -> read = cbuffer -> buffer;
	cbuffer -> write = cbuffer -> read;
	
	return cbuffer;
}

/******************************************************************************
* Function Description: destroys given cbuffer by freeing the memory allocated
* Arguments: - pointer to a cbuffer
* Return value: none
* Notes: if receives null - undefined behaviour.

* Time Complexity: O(1)
*******************************************************************************/
void CBufferDestroy(cbuffer_ty *cbuffer)
{
	assert(cbuffer);

	free(cbuffer);

}

/******************************************************************************
* Function Description: return number of free bytes in the buffer
* Arguments: - pointer to the cbuffer_ty
* Return value: number of free bytes to write
* Notes: 

* Time Complexity: O(1)
*******************************************************************************/
size_t CBufferFreeSpace(const cbuffer_ty *cbuffer)
{
	assert(cbuffer);

	if(CBufferIsEmpty(cbuffer))
	{
		return cbuffer -> bufsiz;
	}

	if(cbuffer -> write > cbuffer -> read)
	{
		return (cbuffer -> bufsiz - (cbuffer -> write - cbuffer -> read));
	}

	if(cbuffer -> write < cbuffer -> read)
	{
		return (cbuffer -> read - cbuffer -> write - 1);
	}

	return 0;
}


/***************************************************************************
* Function Description: return value of bufsiz	       
* Arguments: pointer to the cbuffer_ty
* Return value: return value of bufsiz (capacity)
* Notes: 

* Time Complexity: O(1)
*******************************************************************************/
size_t CBufferBufsiz(const cbuffer_ty *cbuffer)
{
	assert(cbuffer);

	return cbuffer -> bufsiz;
}

/******************************************************************************
* Function Description: attempts to read up to count bytes from circular buffer
* into dest
* Arguments: pointer to a circular buffer, dest and number of bytes
* Return value: number of bytes read ,On error -1 is returned.
* Notes: if count is bigger than the buffer current size - reads up to current
          size.
          If there's not enough space in dest - undefined.

* Time Complexity: O(n)
*******************************************************************************/
ssize_t CBufferRead(cbuffer_ty *cbuffer, void *dest, size_t count)
{
	
	size_t chunk1;
	size_t chunk2;
	char *result;

	/*num of bytes from write till the end of the buffer array */
	size_t end_space = cbuffer -> bufsiz + 1 - (cbuffer -> read - cbuffer -> buffer);
	size_t occupied = cbuffer -> bufsiz - CBufferFreeSpace(cbuffer);
	size_t bytes_to_read = MIN(occupied, count);

	assert(cbuffer);

	/*TODO: redundent if */
	if(cbuffer -> read < cbuffer ->write)
	{
		result = memcpy(dest, cbuffer -> read, bytes_to_read);
		if(result == NULL)
		{
			return -1;
		}

		cbuffer -> read += bytes_to_read;
	}

	else if(cbuffer -> read > cbuffer -> write)
	{
		chunk1 = MIN(end_space, bytes_to_read);
		/* second chunk of memory  - the rest, if exists*/
		chunk2 = bytes_to_read - chunk1;

		result = memcpy(dest, cbuffer -> read, chunk1);
		if(result == NULL)
		{
			return -1;
		}

		dest = (char *)dest + chunk1;
		cbuffer -> read += chunk1;

		if(chunk2 > 0)
		{
			result = memcpy(dest, cbuffer -> buffer, chunk2);
			if(result == NULL)
			{
				return chunk1;
			}

			cbuffer -> read += chunk1;
		}
	}

	return bytes_to_read;
}

/******************************************************************************
* Function Description: writes up to count bytes from src to the circular buffer
* Arguments: pointer to a circular buffer, buffer source and number of bytes to
* write
* Return value: number of written bytes, on error -1 is returned
* Notes: If count is bigger than the free space - writes up to bufsiz
* If not enougth data in src - undefined behavior***************
* Time Complexity: O(n)
*******************************************************************************/
ssize_t CBufferWrite(cbuffer_ty *cbuffer, const void *src, size_t count)
{
	size_t bytes_to_write;
	size_t chunk1;
	size_t chunk2;
	char *result;  /* holds memspy result*/
	/*num of bytes from write till the end of the buffer array */
	size_t end_space = cbuffer -> bufsiz + 1 - (cbuffer -> write - cbuffer -> buffer);
	

	assert(cbuffer);
	assert(src);

	/* MIN between the free space to requested count, will be attempted to write */
	bytes_to_write = MIN(CBufferFreeSpace(cbuffer), count);

	/* when write smaller than read (the space between them is the empty) */
	/* TODO: this if is probably redundent, this case is covered
	 * anyway later, and will be considered as chunk 1, since in any case we will
	 * not write more than the free space we have in the buffer  */
	if(cbuffer -> write <= cbuffer -> read )
	{
		result = memcpy(cbuffer -> write, src, bytes_to_write);
		if(result == NULL)
		{
			return -1;
		}

		cbuffer -> write = result + bytes_to_write; 
	}
	
	/* when write is after the read (the space between them is occupied) */
	else if(cbuffer -> write > cbuffer -> read)
	{
		/* first chunk of memory to be copied:
		Min between num of bytes from write till the end of the buffer array and bytes we want to write.
		the +1 is here, since in practice, the array size is one byte bigger than the bufsiz, 
		so there is an extra byte at the end of the array. In our case we can write to this byte,
		since we've already checked that there is enought space in buffer to the amount we are attempting to write,
		so if we are actually writing till the end, the read is not located at buffer start (idx 0) */
		chunk1 = MIN(end_space, bytes_to_write);

		/* second chunk of memory  - the rest, if exists*/
		chunk2 = bytes_to_write - chunk1;

		result = memcpy(cbuffer -> write, src, chunk1);
		if(result == NULL)
		{
			return -1;
		}

		cbuffer -> write += chunk1;
		src = (char *)src + chunk1;

		if(chunk2 > 0)
		{
			result = memcpy(cbuffer -> buffer, src, chunk2);
			if(result == NULL)
			{
				return chunk1;
			}

			cbuffer -> write = cbuffer -> buffer + chunk2;
			src = (char *)src + chunk2;
		}
	}
	return bytes_to_write;
}

/******************************************************************************
* Function Description: checks if the cbuffer is empty
* Arguments: - pointer to the cbuffer
* Return value: int (boolean) with value of either 0 (false) or 1 (true) 
* Notes: 

* Time Complexity: O(1)
*******************************************************************************/
int CBufferIsEmpty(const cbuffer_ty *cbuffer)
{
	assert(cbuffer);

	return cbuffer -> read == cbuffer ->write;
}

