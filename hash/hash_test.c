/*******************************************************************************
*	Written by:		Olga Danielle Cahana									   *
*	Date:			21/2/2022												   *
*	Reviewed by:							    					    	   *
*																			   *
*******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h> /* assert	*/

#include "utils.h"
#include "hash.h"

#define TEST_ARR_SIZE 10
/*********************Tests declarations***************************************/
static void Test_Hash_Simple(void);
/*********************Helpers declarations*************************************/
static size_t HashingIMP(const void *number, const void *param);
static int SameIntIMP(const void *key1,const void *key2);
static int PrintHashIMP(void *elem, void *op_param);

/******************************Main********************************************/
int main(void)
{
    Test_Hash_Simple();

    return 0;
}

/***********************Tests Implementation***********************************/
static void Test_Hash_Simple(void)
{
    int data[TEST_ARR_SIZE] = {2132,325,12311,435654,3453456,
                               34234,456,8678,32423,45760};
    int value;
    size_t hash_factor = 11;
    size_t idx = 0;

    hash_is_same_func_ty is_same_func = SameIntIMP;
    hash_func_ty hash_func = HashingIMP;
    hash_op_func_ty op_func = PrintHashIMP;


    hash_ty *my_hash = HashCreate(hash_factor, hash_func, is_same_func, &hash_factor);

    my_hash != NULL ?
            printf("Test Passed\n") :
            printf("Test Failed");

    HashSize(my_hash) == 0 ?
            printf("Test Passed\n") :
            printf("Test Failed");

    HashInsert(my_hash, &data[0]) == 0 ? 
            printf("Test Passed\n") :
            printf("Test Failed");

  /*  HashForEach(my_hash, op_func, NULL); */

    *(int *)HashFind(my_hash, &data[0]) == data[0] ?
            printf("Test Passed\n") :
            printf("Test Failed");

    HashSize(my_hash) == 1 ?
            printf("Test Passed\n") :
            printf("Test Failed");

    HashRemove(my_hash, &data[0]);

    HashSize(my_hash) == 0 ?
            printf("Test Passed\n") :
            printf("Test Failed");


    for(idx = 0; idx < TEST_ARR_SIZE; ++idx)
    {
        HashInsert(my_hash, &data[idx]);
    }

    HashForEach(my_hash, op_func, NULL);

    HashSize(my_hash) == 10 ?
            printf("Test Passed\n") :
            printf("Test Failed");

    
    printf("removed: %d\n\n", HashRemove(my_hash, &data[3]));

    HashSize(my_hash) == 9 ?
            printf("Test Passed\n") :
            printf("Test Failed");

    HashForEach(my_hash, op_func, NULL);
    

    HashDestroy(my_hash);

}
/***********************Helpers Implementation**********************************/
static size_t HashingIMP(const void *number, const void *param)
{
    return *(int *)number % *(size_t *)param;
}

static int SameIntIMP(const void *key1, const void *key2)
{
    return *(int *)key1 == *(int *)key2;
}

static int PrintHashIMP(void *elem, void *op_param)
{
    size_t idx = 0;

    UNUSED(op_param);

    printf("%d\n", *(int *)elem );
    return 0;
}
