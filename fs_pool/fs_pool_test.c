/*******************************************************************************
*	Written by:		Olga Danielle Cahana									   *
*	Date:			17/01/2022												   *
*	Reviewed by:	Meirav						    					 	   *
*																			   *
*******************************************************************************/
#include <stdio.h> /* printf */ 
#include <stddef.h> /* size_t, sizeof */
#include <stdlib.h>

#include "fs_pool.h"
#include "utils.h"


/****************Tests declarations********************************************/
static void Scenario_1_Tests(void);

/*********************Helpers declarations*************************************/


/******************************Main********************************************/
int main(void)
{
	Scenario_1_Tests();


	return 0;
}

/***********************Tests Implementation***********************************/
static void Scenario_1_Tests(void)
{
	fsp_ty *my_pool = NULL;
    size_t mem_size = 0;
    size_t chunk_size = 10;
    fsp_ty * allocated[10];
    int i;

    

    mem_size = FSPoolCalcSize(10,10);
    mem_size == 110 ?
			printf("Test release FSPoolCalcSize. \t\tTest Passed\n") :
			printf(" release FSPoolCalcSize. \t\tTest Failed!!\n");

    DEBUG_ONLY(mem_size == 120 ?
			printf("Test debug FSPoolCalcSize. \t\tTest Passed\n") :
			printf("Test debug FSPoolCalcSize. \t\tTest Failed!!\n"));

    my_pool = malloc(mem_size * sizeof(char));
    my_pool = FSPoolInit(my_pool, mem_size, chunk_size);

    FSPoolCountFreeChunks(my_pool) == 10 ?
            printf("Test full FSPoolCountFreeChunks. \tTest Passed\n") :
			printf("Test full FSPoolCountFreeChunks. \tTest Failed!!\n");
   

    printf("allocate 10 chunks of memory\n");
    for (i = 0; i<10; ++i)
    {
        allocated[i] = FSPoolAlloc(my_pool);
    }

     FSPoolCountFreeChunks(my_pool) == 0 ?
        printf("Test empty FSPoolCountFreeChunks. \tTest Passed\n") :
        printf("Test empty FSPoolCountFreeChunks. \tTest Failed!!\n");

    /* allocate one chunk - should fail since no free memory left */
    FSPoolAlloc(my_pool);
    /* free one chunk */
    FSPoolFree(my_pool, allocated[0]);

    FSPoolCountFreeChunks(my_pool) == 1 ?
        printf("Test  FSPoolCountFreeChunks. \t\tTest Passed\n") :
        printf("Test  FSPoolCountFreeChunks. \t\tTest Failed!!\n");

    FSPoolFree(my_pool, allocated[5]);

    FSPoolCountFreeChunks(my_pool) == 2 ?
        printf("Test  FSPoolCountFreeChunks. \t\tTest Passed\n") :
        printf("Test  FSPoolCountFreeChunks. \t\tTest Failed!!\n");

    allocated[5] = FSPoolAlloc(my_pool);

    for(i = 1; i < 10; ++i)
    {
        FSPoolFree(my_pool, allocated[i]);
    }

    FSPoolCountFreeChunks(my_pool) == 10 ?
        printf("Test full FSPoolCountFreeChunks. \tTest Passed\n") :
        printf("Test full FSPoolCountFreeChunks. \tTest Failed!!\n");

    free(my_pool);

}
 


/****************************Helpers Implementation****************************/

