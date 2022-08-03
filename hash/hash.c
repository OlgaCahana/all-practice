/*******************************************************************************
*	Written by:		Olga Danielle Cahana									   *
*	Date:			21/2/2022												   *
*	Reviewed by:							    			    		 	   *
*																			   *
*******************************************************************************/

#include <stdlib.h>
#include <assert.h> /* assert	*/

#include "utils.h"
#include "hash.h"
#include "dlist.h"

enum{FAIL = -1, SUCCESS = 0};

struct hash_set
{
    dlist_ty **m_hash_table;
    hash_func_ty m_hash_func;
    hash_is_same_func_ty m_is_same;
    const void *m_param;
    size_t m_size;
};


/*********************Helpers declarations*************************************/
static int InitHashIMP(hash_ty *hash_table, size_t size);
static void FreeHashArrayIMP(hash_ty *hash_table);
static iterator_ty FindIMP(const dlist_ty *dlist, hash_is_same_func_ty is_same,const void *elem);
static dlist_ty * GetHashEntryIMP(const hash_ty *hash_table , const void *elem);

/****************************Implementation*************************************/
hash_ty *HashCreate(size_t max_size,
                    hash_func_ty hash_func,
                    hash_is_same_func_ty is_same_func,
                    const void *param)
{
    /* TODO: 1. calloc, so the destroy in case of mem alloc failure will work properly
     * 2. add modulu hashing here */
    /* allocate memory for hash struct plus hash table */
    hash_ty * hash = (hash_ty *)malloc(sizeof(hash_ty)
                                     + max_size * sizeof(dlist_ty *));
    CHECK_ALLOC_IFBAD_FREE_RETURN(hash, NULL, NULL, NULL);

  /* hash->m_hash_table = (dlist **)malloc(sizeof(dlist_ty *) * max_size); */

    /* set hash table memory to start righ after */
    hash->m_hash_table = ((dlist_ty **)(hash + 1));

    /* init struct members */
    hash->m_hash_func = hash_func;
    hash->m_is_same = is_same_func;
    hash->m_param = param;
    hash->m_size = max_size;

    /* initialize each table entry with an empty dlist */
    if(InitHashIMP(hash, max_size) == FAIL)
    {
        FreeHashArrayIMP(hash);
        free(hash);
        return NULL;
    }

    return hash;
}



/*  null is allowed 4! */
void HashDestroy(hash_ty *hash_set)
{
    FreeHashArrayIMP(hash_set);
    /*TODO: before freeing the hash_set, set all its members to NULL*/
    free(hash_set);
}



/*   if fails to find elem returns 1, else returns 0    8!*/
/*   int(*is_same)(const void *key1, const void *key2) */
int HashRemove(hash_ty *hash_set, const void *elem_key_rmv)
{
    iterator_ty found_iter = {NULL};
    dlist_ty *dlist  = 0;

    assert(hash_set);

    /* get the list from table hash key entry */
    dlist = GetHashEntryIMP(hash_set, elem_key_rmv);

    /* search for elem_key_rmv in the acquired dlist */
    found_iter = FindIMP(dlist, hash_set->m_is_same, elem_key_rmv);

    /* if not found, return FAIL, else remove */
    RETURN_IF_BAD(!DlistIsSameIter(found_iter, DlistEnd(dlist)), 
                            FAIL, "faled to find element to remove");

    DlistRemove(found_iter);
    
    return SUCCESS;
}



/*   assert that not same with int(*is_same)(const void *key1, const void *key2) 2! */
int HashInsert(hash_ty *hash_set, void *elem)
{
    dlist_ty *element = NULL;
    iterator_ty inserted = {NULL};
    dlist_ty *dlist = NULL;

    /* asserts */
    assert(hash_set);
    assert(elem);

    dlist = GetHashEntryIMP(hash_set, elem);

    /* check for duplicates */
    /* assert if found, duplicates are not allowed */
    assert(!DlistIsSameIter(DlistEnd(dlist), 
                           FindIMP(dlist, hash_set->m_is_same, elem)));

    /* if unique, insert the element to the right entry according to the key */
    inserted = DlistPushFront(dlist, elem);
    RETURN_IF_BAD(!DlistIsSameIter(DlistEnd(dlist), inserted), 
                            FAIL, "faled to insert to hash");

    /* return success */
    return SUCCESS;
}


size_t HashSize(const hash_ty *hash_set)
{
    size_t count = 0;
    size_t idx = 0;

    assert(hash_set);

    /* free each table entry dlist */ 
     for(idx = 0; idx < hash_set->m_size; ++idx)
    {
        count += DlistSize(hash_set->m_hash_table[idx]);
    }

    return count;
}


/*  returns ptr to data, NULL if fails 3! */
void *HashFind(const hash_ty *hash_set, const void *key_element)
{
    dlist_ty *dlist;
    iterator_ty found_iter;

    assert(hash_set);

    /* get the list where the find_param should be searched in */
    dlist = GetHashEntryIMP(hash_set, key_element);

    /* get iterator if found*/
    found_iter = FindIMP(dlist, hash_set->m_is_same, key_element);

    /* if the itrator is end iterator, the element was not found*/
    if(DlistIsSameIter(DlistEnd(dlist), found_iter))
    {
        return NULL;
    }

    /* return the data from the founf iterator */
    return DlistGetData(found_iter);
}


/*  returns return value of first op_func failure */
/*  if fails all of the elements post failure point remain untouched. 5! */
int HashForEach(hash_ty *hash_set, hash_op_func_ty op_func, void *param)
{
    size_t idx = 0;
    iterator_ty start;
    iterator_ty end;
    int result = 0;

    assert(hash_set);

    /* for each hash entry, while success */
    for(idx = 0; idx < hash_set->m_size && result == 0; ++idx)
    {
        /*printf("curr entry:\n");*/

        start = DlistBegin(hash_set->m_hash_table[idx]);
        end = DlistEnd(hash_set->m_hash_table[idx]);
        result = DlistForEach(start, end, op_func, param);

    }
    return result;
}

/*  contains stats of average list, max list, etc.. 7!*/
/*  ATM returns 7 */
hash_stats_ty HashStats(const hash_ty *hash_set)
{
  /*  int count = 0;
    hash_stats_ty stats;*/
    /* for each list*/
       /* count += lenght; */
        /* num used += length >0;*/
        /* if max < list lenfgth*/
     /*   ret.m_avg
        ret.m_long = max;
    return stats; */
}


/***********************Helpers Implementation**********************************/

static int InitHashIMP(hash_ty *hash_table, size_t size)
{
    size_t idx = 0;

    assert(hash_table);


    /* each table entry should hold an empty dlist */ 
     for(idx = 0; idx < size; ++idx)
    {
        hash_table->m_hash_table[idx] = DlistCreate();
        RETURN_IF_BAD(hash_table->m_hash_table[idx], FAIL, "mem allocation failed\n");
    }

    return SUCCESS;
}


static void FreeHashArrayIMP(hash_ty *hash_table)
{
    size_t idx = 0;

    assert(hash_table);

    /* free each table entry dlist */ 
     for(idx = 0; idx < hash_table->m_size; ++idx)
    {
        DlistDestroy(hash_table->m_hash_table[idx]);
        hash_table->m_hash_table[idx] = NULL;
    }
}


static iterator_ty FindIMP(const dlist_ty *dlist, hash_is_same_func_ty is_same_fnc,const void *elem)
{
    iterator_ty curr = {NULL};
    iterator_ty end = {NULL};

    assert(dlist);

    curr = DlistBegin(dlist);
    end = DlistEnd(dlist);

    while (!DlistIsSameIter(curr, end))
    {
        if(is_same_fnc(elem, DlistGetData(curr)))
        {
            return curr;
        }
        curr = DlistNext(curr);
    }
    return end;
}


static dlist_ty * GetHashEntryIMP(const hash_ty *hash_table , const void *elem)
{
    size_t hash_key = 0;

    assert(hash_table);
    
    /* find the entry associated with the key */
    hash_key = hash_table->m_hash_func(elem, hash_table->m_param);
    
    /* return the pointer to list located in found entry */
    return hash_table->m_hash_table[hash_key];
}