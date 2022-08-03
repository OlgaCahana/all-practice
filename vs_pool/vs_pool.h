

#ifndef __VS_POOL_H__
#define __VS_POOL_H__

#include <stddef.h> /*size_t*/

typedef struct vs_pool *vsp_ty;


/* Notes: memory must be alligned to your needs (aligned to 8 bytes if double used)
 * provide memory size in bytes
 * Time Complexity: O(1) - memory_size / chunk_size */
vsp_ty *VSPoolInit(void *memory, size_t memory_size);


/* 	Notes: Returns a pointer to a new chunk of memory of requested size
		   Returns NULL pointer if no chunk of requested size is available.
	Time Complexity: O(n) */

void *VSPoolAlloc(vsp_ty *vs_pool, size_t chunk_size);


/* 	Notes: if sent chunk to free is not in range - undefined behaviour
	Time Complexity: O(1) */  
void VSPoolFree(void *chunk_to_free);


/* 	Notes: returns the size of the largest available memory block in the pool
	Time Complexity: O(n) */
size_t VSPoolMaxAvlChunk(vsp_ty *vs_pool);





#endif /*__FS_POOL_H__*/
