/*******************************************************************************
*	Written by:		Olga Danielle Cahana									   *
*	Date:			19/01/2022												   *
*	Reviewed by:	Michael						    					 	   *
*																			   *
*******************************************************************************/
#include <stdio.h> /* printf */ 
#include <stddef.h> /* size_t, sizeof */
#include <stdlib.h> /* malloc, free */

#include "vs_pool.h"
#include "utils.h"


/****************Tests declarations********************************************/
static void Scenario_1_Tests(void);

/*********************Helpers declarations*************************************/
static void PrintPool(ptrdiff_t *pool, size_t size);

/******************************Main********************************************/
int main(void)
{
	Scenario_1_Tests(); 
	return 0;
}

/***********************Tests Implementation***********************************/
static void Scenario_1_Tests(void)
{
	vsp_ty *vs_pool = (vsp_ty *)calloc(22, sizeof(size_t));
	ptrdiff_t *allocated[10] = {0};
	size_t i = 0;

	/* Create vs pool of 22*8 = 176 bytes total size,
	 * i.e 160 free bytes available for allocation */
	vs_pool = VSPoolInit(vs_pool, 176);
	VSPoolMaxAvlChunk(vs_pool) == 160 ?
			printf("Max available chunk test. \t\tTest Passed\n") : 
			printf("Max available chunk test. \t\tTest Failed\n");

	PrintPool((ptrdiff_t *)vs_pool, 22);

	/* Allocate more than the available memory, NULL is expected */
	allocated[i] = VSPoolAlloc(vs_pool, 200);
	allocated[i] == NULL ?
			printf("Allocate too much memory \t\tTest Passed\n") :
			printf("Allocate too much memory \t\tTest Failed\n") ;


	/* Allocate the whole memory, print the pool */
	allocated[i] = VSPoolAlloc(vs_pool, 160);
	allocated[i] == (ptrdiff_t *)vs_pool + 1 ?
			printf("Allocate whole memory \t\tTest Passed\n") :
			printf("Allocate whole memory \t\tTest Failed\n") ;
	PrintPool((ptrdiff_t *)vs_pool, 22);

	/* Try to allocate again - NULL expected since there no free memory*/
	allocated[i+1] = VSPoolAlloc(vs_pool, 1);
	allocated[i+1] == NULL ?
			printf("Allocate while no free memory \tTest Passed\n") :
			printf("Allocate while no free memory \tTest Failed\n") ;

	/* Check MaxAvailChunk == 0, print the pool: "1 0 0 ... 0" */
	PrintPool((ptrdiff_t *)vs_pool, 22);
	VSPoolMaxAvlChunk(vs_pool) == 0 ?
			printf("Max available chunk test. \t\tTest Passed\n") : 
			printf("Max available chunk test. \t\tTest Failed\n");

	/* free the allocated chunk */
	VSPoolFree(allocated[i]);
	PrintPool((ptrdiff_t *)vs_pool, 22);

	/* allocate part of the available memory */
	allocated[i] = VSPoolAlloc(vs_pool, 88);
	PrintPool((ptrdiff_t *)vs_pool, 22);

	VSPoolMaxAvlChunk(vs_pool) == 64 ?
			printf("Max available chunk test. \t\tTest Passed\n") : 
			printf("Max available chunk test. \t\tTest Failed\n");

	allocated[1] = VSPoolAlloc(vs_pool, 3);
	PrintPool((ptrdiff_t *)vs_pool, 22);

	allocated[2] = VSPoolAlloc(vs_pool, 40);
	PrintPool((ptrdiff_t *)vs_pool, 22);
	
	/* free all allocated chunks */
	VSPoolFree(allocated[0]);
	PrintPool((ptrdiff_t *)vs_pool, 22);
	printf("max free: %ld\n", VSPoolMaxAvlChunk(vs_pool));
	VSPoolFree(allocated[1]);
	VSPoolFree(allocated[2]);
	PrintPool((ptrdiff_t *)vs_pool, 22);

	allocated[0] = VSPoolAlloc(vs_pool, 40);
	allocated[1] = VSPoolAlloc(vs_pool, 32);
	/* this allocation will require defragmentation */
	allocated[2] = VSPoolAlloc(vs_pool, 48);
	PrintPool((ptrdiff_t *)vs_pool, 22);

	VSPoolMaxAvlChunk(vs_pool) == 16 ?
			printf("Max available chunk test. \t\tTest Passed\n") : 
			printf("Max available chunk test. \t\tTest Failed\n");
	PrintPool((ptrdiff_t *)vs_pool, 22);
	
	/* free all allocated chunks */
	VSPoolFree(allocated[0]);
	VSPoolFree(allocated[1]);
	VSPoolFree(allocated[2]);

	VSPoolMaxAvlChunk(vs_pool) == 160 ?
			printf("Max available chunk test. \t\tTest Passed\n") : 
			printf("Max available chunk test. \t\tTest Failed\n");
	PrintPool((ptrdiff_t *)vs_pool, 22);

	/* allocate 10 chunks of different sizez */
	/* free some chuncs */
	/* allocate chunk of size that will require degragmentation */ 


	free(vs_pool);
}

 


/****************************Helpers Implementation****************************/

static void PrintPool(ptrdiff_t *pool, size_t size)
{
    size_t i = 0;
    fputs("pool: ", stdout);
    for(i = 0; i < size; ++i)
    {
        if(pool[i])
        {
            printf("%ld ", pool[i]);
        }
        else
        {
            fputs(" 0 ", stdout);
        }
    }
    putchar('\n');
}