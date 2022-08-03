/*******************************************************************************
*	Written by:		Olga Danielle Cahana									   *
*	Date:			24/02/2022												   *
*	Reviewed by:							    					 	   *
*																			   *
*******************************************************************************/
#include <assert.h> /* assert */
#include <stdio.h> /* fprintf */ 
#include <stdlib.h> /* size_t, malloc, free*/

#include "priorityq.h"
#include "vector.h"
#include "utils.h"

							

/**************************** Types *******************************************/

struct priorityq
{
	vector_ty *m_heap_vec;
    pq_cmp_func_ty m_cmp_func;
};

/***************************Helpers declarations*******************************/

static void HeapifyUpIMP(pq_ty *pqueue, size_t elem_idx);
static void HeapifyDownIMP(pq_ty *pqueue, size_t elem_idx);

/* generic heapifyUP, recieves the index of last elem, heap is idx0 */
/*static void HeapifyUpIMPG(void *heap, int element_size, size_t elem_idx, cmp_func);*/

static void SwapIMP(void **elem1, void **elem2);
static int ISLeaf(pq_ty *pqueue, size_t elem_idx);
static int IsRoot(pq_ty *pqueue, size_t elem_idx);
static size_t FindIMP(pq_ty *pqueue,
                     int(*match_func)(const void *data1, void *param), void *param);

/* return NULL if no parent (root) or no child*/
static void *ParentDataIMP(vector_ty *heap_vec, size_t idx);
static void *RightChildDataIMP(vector_ty *heap_vec, size_t idx);
static void *LeftChildDataIMP(vector_ty *heap_vec, size_t idx);

/* get the data pointer located at vector[idx]*/
static void **GetElemIMP(vector_ty *heap_vec, size_t idx);
void PrintIntHeapIMP(vector_ty *vector_);



/******************************************************************************/
/*							Implementaion			     				      */
/******************************************************************************/

pq_ty *PQCreate(int(*cmp_func)(const void *data1, const void *data2))
{
	pq_ty *p_queue = NULL;
    int *dummy = 0;

	assert(cmp_func);

    /* allocate memory for pq struct */
	p_queue = (pq_ty *)malloc(sizeof(pq_ty));
	CHECK_ALLOC_IFBAD_FREE_RETURN(p_queue, NULL, NULL,NULL);

    /* allocate dummy to be hold at idx 0 */
 /*   dummy = malloc(sizeof(void *));
	CHECK_ALLOC_IFBAD_FREE_RETURN(dummy, NULL, NULL,NULL); */


	/* allocate memory for the vector to hold pointers to heap elements*/
    p_queue->m_heap_vec = VectorCreate(sizeof(void *), 2);
	CHECK_ALLOC_IFBAD_FREE_RETURN(p_queue, p_queue, NULL,NULL);

    p_queue->m_cmp_func = cmp_func;

    /* push dummy as first vector element, so heap indexes will start from 1 */
    VectorPushBack(p_queue->m_heap_vec, &dummy);

    /* return p_queue*/
	return p_queue; 
}


void PQDestroy(pq_ty *pq)
{

    /* scan the vector and free all the elements */
    /* Destroy the vector */
  /*  free(*GetElemIMP(pq->m_heap_vec,0)); */
    VectorDestroy(pq->m_heap_vec);

/*	free(pq); */
    free(pq);
}



int PQEnqueue(pq_ty *pq, const void *data)
{
	assert(pq);

	/* insert the element to the vector using VectorPushBack */
    if(VectorPushBack(pq->m_heap_vec, &data) != 0)
    {
        return 1;
    }

    /* BubbleUpIMP the element to its right place */
 /*   HeapifyUpIMP(pq, PQSize(pq)); */
    PrintIntHeapIMP(pq->m_heap_vec); 
    return 0;
}



void *PQDequeue(pq_ty *pq)
{
    void **top_element = NULL;
    void **last_leaf = NULL;
    void *ret = NULL;

	assert(pq);
	assert(!PQIsEmpty(pq));

    top_element = VectorGetElem(pq->m_heap_vec, 1);
    last_leaf = (void **)VectorGetElem(pq->m_heap_vec, PQSize(pq));
    ret = *top_element;

    /* swap first and last vector elements */
    SwapIMP(top_element, last_leaf); 

	/* top_element = VectorPopBack */
    VectorPopBack(pq->m_heap_vec);

    /* BubbleDownIMP on the first array element */

   /* TODO: if(!PQIsEmpty(pq)) */
 /*   HeapifyDownIMP(pq, 1); */

    return ret;

}


void *PQPeek(const pq_ty *pq)
{
	assert(pq);
	assert(!PQIsEmpty(pq));

	/* return Pointer to the top heap element (vector[1]) */
    return *GetElemIMP(pq->m_heap_vec, 1);
}



int PQIsEmpty(const pq_ty *pq)
{
	assert(pq);

	/* return VectorSize == 1 */
    return VectorSize(pq->m_heap_vec) == 1;
}


size_t PQSize(const pq_ty *pq)
{
	assert(pq);

	/* return VectorSize - 1 */
    return VectorSize(pq->m_heap_vec) - 1;
}


void PQClear(pq_ty *pq)
{
	srt_iter_ty start;
	srt_iter_ty end;

	assert(pq);

    /* while VectorSize > 1*/
    while (PQSize(pq))
    {
        /* VectorPopBack */
        VectorPopBack(pq->m_heap_vec);
    }
}


void *PQErase(pq_ty *pq,
			  int(*match_func)(const void *data1, void *param),
			  void *param)
{
    size_t found_idx = 0;
    void **last_leaf = NULL;
    void ** moved_elem = NULL;
    void *ret = NULL;

    assert(pq);

    /* Find the element */
    found_idx = FindIMP(pq, match_func, NULL);
    if(found_idx == 0)
    {
        return NULL;
    }

    last_leaf = GetElemIMP(pq->m_heap_vec, PQSize(pq));

    /* swap the element with last vector element */
    SwapIMP(GetElemIMP(pq->m_heap_vec, found_idx), last_leaf);

    moved_elem = *last_leaf;

    /* if swapped element > parent */
    if(!IsRoot(pq, found_idx) && 
            pq->m_cmp_func(moved_elem, *GetElemIMP(pq->m_heap_vec, found_idx/2)) < 0)
    {
        /* BubbleUpIMP */
        HeapifyUpIMP(pq, found_idx);
    }

    /* if swapped element < any of its children */
            /* has left child and is bigger, or*/
    else if ((!ISLeaf(pq, found_idx) && 
            pq->m_cmp_func(moved_elem, *GetElemIMP(pq->m_heap_vec, found_idx * 2)) > 0)
            || 
            /* has right child and is bigger*/
            (found_idx * 2 + 1 <= PQSize(pq) &&
            pq->m_cmp_func(moved_elem, *GetElemIMP(pq->m_heap_vec, found_idx * 2)) > 0))
            {
                /* BubbleDown */
                HeapifyDownIMP(pq, found_idx);
            }

    /* ret = PopBack */
    ret = *last_leaf;

    VectorPopBack(pq->m_heap_vec);

    return ret;
}

/***********************Helpers Implementation**********************************/
static void HeapifyUpIMP(pq_ty *pqueue, size_t elem_idx)
{
    size_t curr_idx = elem_idx;
    void ** parent_data = NULL;
    void ** curr_data = NULL;

    assert(pqueue);

    curr_data = GetElemIMP(pqueue->m_heap_vec, elem_idx);
    parent_data = GetElemIMP(pqueue->m_heap_vec, elem_idx/2);

    /* while curr is not heap root and curr data > root data*/
    while(curr_idx > 1 && pqueue->m_cmp_func(*curr_data, *parent_data) < 0)
    {
        /* swap current and parent data */
        SwapIMP(curr_data, parent_data);

        /* promote curr to its parent */
        curr_idx /= 2;
        curr_data = GetElemIMP(pqueue->m_heap_vec, curr_idx);
        parent_data = GetElemIMP(pqueue->m_heap_vec, curr_idx / 2);
        
    } 
}


static void HeapifyDownIMP(pq_ty *pqueue, size_t elem_idx)
{
    size_t curr_idx = elem_idx;
    size_t next_idx = elem_idx;

    void **curr_data = NULL;
    void **left_child_data = NULL;
    void **right_child_data = NULL;
    void **largest = NULL;


    assert(pqueue);

    /* while current is not a leaf */
    while(!ISLeaf(pqueue, curr_idx))
    {
        /* get current data */
        curr_data = GetElemIMP(pqueue->m_heap_vec, curr_idx);
        largest = curr_data;

        /* get left child data */
        left_child_data = GetElemIMP(pqueue->m_heap_vec, curr_idx * 2);

        /* if left child bigger, set largest to left child */
        if(pqueue->m_cmp_func(*curr_data, *left_child_data) > 0)
        {
            largest = left_child_data;
            next_idx = curr_idx * 2;
        }

        /* if right child exists, get its data */
        if(curr_idx * 2 + 1 <= PQSize(pqueue))
        {
            /* get its data */
            right_child_data = GetElemIMP(pqueue->m_heap_vec, curr_idx * 2 + 1);

            /* compare data to largest and update largest if necessary */
            if(pqueue->m_cmp_func(*largest, *right_child_data) > 0)
            {
                largest = right_child_data;
                next_idx = curr_idx * 2 + 1;
            }
        }

        /* if largest is equal to current, i.e. no violation found, break */
        if(largest == curr_data)
        {
            break;
        }

        /* swap the largest and current data */
        SwapIMP(curr_data, largest);

        /* update curr_idx to next_idx */
        curr_idx = next_idx;
    }
}

static void SwapIMP(void **elem1, void **elem2)
/* alternative parameters: (vector_ty *vector, size_t idx1, size_t idx2) */
{
    void *temp = NULL;

    assert(elem1);
    assert(elem2);

    /* swap between the pointed elements */
    temp = *elem1;
    *elem1 = *elem2;
    *elem2 = temp;
}


static int ISLeaf(pq_ty *pqueue, size_t elem_idx)
{
    /* if has no legt son. the node is a leaf node */
    return 2 * elem_idx > PQSize(pqueue);
}

static int IsRoot(pq_ty *pqueue, size_t elem_idx)
{
    return elem_idx == 1;
}

/* return NULL if no parent (root) or no child*/
static void **GetElemIMP(vector_ty *heap_vec, size_t idx)
{
    assert(heap_vec);
    
    return (void **)VectorGetElem(heap_vec, idx);
}


static size_t FindIMP(pq_ty *pqueue,
                     int(*match_func)(const void *data1, void *param), void *param)
{
    size_t idx = 0;

    for(idx = 1; idx <= PQSize(pqueue); ++idx)
    {
        if(match_func(*GetElemIMP(pqueue->m_heap_vec, idx), NULL) == 0)
        {
            return idx;
        }
    }
    return 0;
}

void PrintIntHeapIMP(vector_ty *vector_)
{
    size_t i = 1, lvl = 1;

    while(i < VectorSize(vector_))
    {
        printf("%d  ", *(int *) * GetElemIMP(vector_, i));
        if(i == lvl)
        {
            putchar('\n');
            lvl = lvl * 2 + 1;
        }
        ++i;
    }
    putchar('\n');putchar('\n');
}