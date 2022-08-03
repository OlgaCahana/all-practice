/*******************************************************************************
*	Written by:		Olga Danielle Cahana									   *
*	Date:			19/01/2022												   *
*	Reviewed by:	Michael						    					 	   *
*																			   *
*******************************************************************************/
#include <stddef.h> /*size_t*/
#include <limits.h> /* LONG_MAX */
#include <assert.h> /* assert*/


#include "vs_pool.h"
 /*TODO: get rid of the macros, use enums and functions instead */
 /* TODO: add stsic assert: assert(sizeof(ptrdiff_t) == sizeof(double)) */
enum {MEM_END = 0};
#define ABS(x)((x) > 0 ? (x) : (x) * -1)
#define MAX(x, y)((x) > (y) ? (x) : (y))

struct vs_pool; /* undefined struct - can typedef it or create variavles */

/****************************** Helpers ****************************************/
/* defragment the memory until desired size is reached or occupied chunk is met */
/* passing LONG_MAX as desired_size argument,
 * will degrafment all chunks until first occupied */
static void DefragmentIMP(ptrdiff_t *chunk, size_t desired_size);

/* return ptr to next chunk */
static ptrdiff_t *GetNextIMP(ptrdiff_t *chunk);

/* calculate the actual memory size to search for,
 * returned value alligned to sizeof(size_t) */
static ptrdiff_t CalcActualMemSizeImp(size_t req_size);

/* Devide one chunk into 2, while the first one should be of size argument
 * return a pointer to the first chunk */
static ptrdiff_t *DevideChunkIMP(ptrdiff_t *chunk, ptrdiff_t size);



/*************************API Implementaion*************************************/ 
/*TODO: improve the description */
/* Description:
 * No handle struct, No actual vs_pool_ty struct - returning the recieved address, containing 
 * pointer to chunk returned to client is a pointer to memory and not its metadata
 * each memory chunk is preceded with 8 bytes of metadata (static ptrdiff_t type),
 * this fields holds the size of the memory chunk including the size of metadata  chunk itself,
 * the matadata value sign indicates whenever the chunk is free (+) or allocated (-).
 * zero size chunks are allowed
 * returns pointer to allocated - to the chunk itself, after the metadata 
 * before the pointer is returned, chunk pointer is a pointer to chunks metadata
 * memory_size should be provided in bytes */
 

 /*	Notes: memory must be alligned to your needs (aligned to 8 bytes if double used)
  * 	Time Complexity: O(1)  */
vsp_ty *VSPoolInit(void *memory_, size_t memory_size_)
{
	ptrdiff_t *memory = memory_; 
	/* calculate memory size in sizeof(size_t), without the last slice that will
	 * hold a distinct value indicating the end of memory*/
	size_t act_memory_size = memory_size_ / sizeof(size_t) - 1;

	assert(memory_);
	assert(0 < memory_size_);
	assert(0 == (size_t)memory_ % sizeof(double));
	assert(0 == memory_size_ % sizeof(double));
	 
 	/* assign END_OF_MEM in the last 8 bytes of the provided memory */
	*(memory + act_memory_size) = MEM_END;
	/* update the first metadata of the memory to memory_size */
	*memory = act_memory_size;
	
	/* return a pointer to vsp_ty */
	return (vsp_ty *)memory;	
}



/* 	Notes: Returned chunk size will be aligned to word size.
		   Returns a pointer to a new chunk of memory of requested size
		   Returns NULL pointer if no chunk of requested size is available.
		   requested size should be in terms of bytes 
	Time Complexity: O(n) */
void *VSPoolAlloc(vsp_ty *vs_pool_, size_t req_size_)
{
	/* scan the memory and return the first chunk big enough (>=chunk_size): */
	ptrdiff_t *curr = (ptrdiff_t *)vs_pool_;
	ptrdiff_t chunk_size = CalcActualMemSizeImp(req_size_);

	assert(vs_pool_);
	
	/* while end of memory not reached */
	while(*curr != MEM_END)
	{
		/* if curr chunk is free */
		if(*curr > 0)
		{
			/* if not big enougth, defragment the memory until desired size 
			 * or occupied chunk reached */
			if (*curr < chunk_size)
			{
				DefragmentIMP(curr, chunk_size);
			}

			if(*curr >= chunk_size)
			{
				/* if found chunk is bigger tham the needed size, devide it into two */
				if(*curr > chunk_size)
				{
					curr = DevideChunkIMP(curr, chunk_size);
				}

				/* return pointer to memory after the metadata, udate to negative*/
				*curr *= -1; 
				return (vsp_ty *)(curr + 1);
			}
		}
		/* promote current to next chunk */
		curr = GetNextIMP(curr);
	}

	/* if couldn't find a chunk of requested size return NULL */
	if(*curr == MEM_END)
	{
		return NULL;
	}
	
	/* return pointer to the found memory chunk and update its metadata to negative */
	*curr *= -1;
	return (vsp_ty *)(curr + 1);
}

 
void VSPoolFree(void *chunk_to_free_)
{
	ptrdiff_t *chunk =  (ptrdiff_t *)chunk_to_free_ - 1;
	if(chunk_to_free_ == NULL)
	{
		return;
	}

	assert(*chunk < 0);
	/* apdate the recieved chunk metadata, to positive */
	*(chunk) *= -1;
}


/* 	Notes: returns the size of the largest available memory block in the pool
	Time Complexity:  */
size_t VSPoolMaxAvlChunk(vsp_ty *vs_pool_)
{
	/* scan the memory looking for biggest free chunk, while defragmenting adjacent free chunks */
	ptrdiff_t *curr_chunk = (ptrdiff_t *)vs_pool_;
	ptrdiff_t max_free = 0;

	assert (vs_pool_);

	/* while end of memory is not reached */
	while(*curr_chunk != MEM_END)
	{
		/* if the chunk is free: defragment the memory till the next allocated */
		if(*curr_chunk > 0)
		{
			DefragmentIMP(curr_chunk, LONG_MAX);
			max_free = MAX(*curr_chunk, max_free);
		}
		/* move forward to the next chunk */
		curr_chunk = GetNextIMP(curr_chunk);
	}

	/* return the found max size in terms of bytes, reducing the metadata size*/
	return max_free == 0 ? 0 : (max_free - 1) * sizeof(ptrdiff_t);
}


/****************************** Helpers IML ****************************************/
/* assuming recieved chunk is free */
static void DefragmentIMP(ptrdiff_t *chunk_, size_t desired_size_)
{
	/* set curr_chunk to point to next chunk */
	ptrdiff_t *curr_chunk = GetNextIMP(chunk_);

	/* while the desired size is not acquired and end of memory is not reached,
	 * merge original chuk with current chunk */
	while(*chunk_ < (ptrdiff_t)desired_size_ && *curr_chunk > MEM_END)
	{
		/* update the start chunk size to new size, move to examine the next chunk*/
		*chunk_ += *curr_chunk;
		curr_chunk = GetNextIMP(curr_chunk);
	}
}


static ptrdiff_t *GetNextIMP(ptrdiff_t *chunk_)
{
	return chunk_ + ABS(*chunk_);
}


static ptrdiff_t CalcActualMemSizeImp(size_t req_size_)
{
	return req_size_ / sizeof(size_t) + 
		   !!(req_size_ % sizeof(size_t)) + 1;
}


static ptrdiff_t *DevideChunkIMP(ptrdiff_t *chunk_, ptrdiff_t size_)
{
	ptrdiff_t remaining_size = 0;

	assert(chunk_);
	assert(*chunk_ > size_);

	/* calculate remainig size after allocation */
	remaining_size = *chunk_ - size_;

	/* devide the memory to two chunks */
	*chunk_ = size_;
	*(chunk_ + size_) = remaining_size;

	return chunk_;
}
