/*******************************************************************************
*	Written by:		Olga Danielle Cahana									   *
*	Date:			17/01/2022												   *
*	Reviewed by:	Meirav						    					 	   *
*																			   *
*******************************************************************************/
#include <stddef.h> /* size_t */
#include <assert.h>

#include "fs_pool.h"    /* fs_pool types and function declerations */
#include "utils.h"       /* util macros */


struct fixed_size_pool
{
    size_t first_free_blk;     /* offset in bytes from adress of stuct to available chunk */
    DEBUG_ONLY(size_t pool_size)   /* dbg? keeps number of elements - for free function (dbg) */
};


/****************************** Helpers ****************************************/
/* calculate the offset of the first chunk in the memory pool */
size_t CalcPoolOffset(size_t chunk_size);


/*************************API Implementaion*************************************/

fsp_ty *FSPoolInit(void *memory, size_t memory_size, size_t chunk_size)
{   
    fsp_ty *fsp_mem = memory;
    char *mem_curr = memory;
    size_t offset = CalcPoolOffset(chunk_size);

    /* asserts */
    assert(memory);
    assert(memory_size > chunk_size);
    assert(chunk_size >= sizeof(size_t));
    
    /* if needed to normalize chunk_size to be word aligned */
    /*chunk_size += sizeof(size_t) - chunk_size % sizeof(size_t);*/

    /* initialize metadata:    */
    fsp_mem->first_free_blk = offset;
    DEBUG_ONLY(fsp_mem->pool_size = memory_size);


    /* ptomote the mem_curr to the first non metadata block */
    mem_curr += offset;

    /*  eager initialization */
    /*  initialize each freelist's index content with the offset of the next free,
        the final offset is 0. */
    
    while(mem_curr + chunk_size < (char *)memory + memory_size)
    {
        offset += chunk_size;
        *((size_t *)mem_curr) = offset;
        mem_curr += chunk_size;
    }

    *((size_t *)mem_curr) = 0;
    return fsp_mem;
}


void *FSPoolAlloc(fsp_ty *fs_pool)
{
    size_t offset = 0;

    /*  handle empty freelist */
    if(fs_pool->first_free_blk == 0)
    {
        printf("No memory left in the pool!\n");
        return NULL;
    }
    
    /*  save freelist[first_blk] address in local temp var */
    offset = fs_pool->first_free_blk;

    /*  copy first_blk */

    /*  progression: first_blk = next */
    fs_pool->first_free_blk = *((char *)fs_pool + fs_pool->first_free_blk);

    /*  convert copy to pointer and return */
    return (char *)fs_pool + offset;
}


void FSPoolFree(fsp_ty *fs_pool, void *chunk_to_free)
{
    size_t offset = 0;
    /*  assert given pointer is part of the pool"
        chunk >= freelist && chunk <= (char *)freelist + pool_size  */
    assert(fs_pool);
    assert(chunk_to_free); 
    assert((char *)chunk_to_free > (char *)fs_pool);
    assert((char *)chunk_to_free < ((char *)fs_pool + fs_pool->pool_size));

    /* set next free offset of chunk_to free to current next free */
    *((size_t *)chunk_to_free) = fs_pool->first_free_blk;

    /* calculate the offset of chunk_to_free */
    offset = (char *)chunk_to_free - (char *)fs_pool;

    /* point first_blk at chunk */
    fs_pool->first_free_blk = offset;
}


size_t FSPoolCountFreeChunks(fsp_ty *fs_pool)
{ 
    /*  create counter. */
    size_t counter = 0;
    size_t curr_offset = 0;

    assert(fs_pool);

    /* save first_blk to temp variable */
    curr_offset = fs_pool->first_free_blk;

    /*  while temp isnt containing distinct value(0) - go to that address */
    while(curr_offset != 0)
    {
        ++counter;
        curr_offset = *(size_t *)((char *)fs_pool + curr_offset);
    }
       
    return counter;
}


size_t FSPoolCalcSize(size_t num_chunks, size_t chunk_size)
{
    assert(chunk_size > sizeof(size_t));
    
    /*  calculate size of num_chunks * chunk_size + size of fsp_ty alligned to chunk_size */
    return CalcPoolOffset(chunk_size) + num_chunks * chunk_size;
}



/****************************Helpers Impl*****************************************/
size_t CalcPoolOffset(size_t chunk_size)
{
    if(sizeof(fsp_ty) <= chunk_size)
    {
        return chunk_size;
    }
    
    return (sizeof(fsp_ty) / chunk_size)*chunk_size + 
            chunk_size * !!(sizeof(fsp_ty) % chunk_size);

}

