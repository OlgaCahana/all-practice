/*******************************************************************************
*	Written by:		Olga Danielle Cahana									   *
*	Date:			3/2/2022												   *
*	Reviewed by:	Daniel						    					 	   *
*																			   *
*******************************************************************************/

#include <stddef.h> /*size_t*/
#include <stdlib.h> /* malloc, free */
#include <assert.h>

#include "btset.h"
#include "utils.h" /* DEBUG_ONLY */

/* do not change the tree order*/
enum{TREE_ORDER = 2};

typedef enum side {LEFT = 0, RIGHT = 1} side_ty;


struct binary_tree_node
{
    void *m_data;
    bt_node_ty *m_parent;
    bt_node_ty *m_children[TREE_ORDER]; /* {0:ptr to left child, 1:ptr to right child }*/
};

struct binary_tree_set
{
    bt_node_ty *m_root;
    bts_cmp_fnc_ty m_cmp_func;
    const void *m_cmp_param; /* TODO: */ 
};


/* this struct will be used as a return value of FindIMP func */
typedef struct nodeANDchild
{
    bt_node_ty *m_node;
    int m_side;
}nodeANDside_ty;

/* General notes:
    * Inserting the keys in sorted order significantly reduces the set performance
*/

/************************Helpers***********************************************/
/* create new node holding the provided data - relatives pointers are nullified */
static bt_node_ty *CreateNodeIMP(void *data);

/* attach child to 'where' node, as its 'side'(RIGHT/LEFT) child */
static void AttachChildIMP(bt_node_ty *node, bt_node_ty *where, side_ty side);

/* free leaf node, apdate the parent */
static void RemoveLeafIMP(btset_iter_ty leaf_iter);

/* traverse LEFT/RIGHT till the end and return pointer to side most node */
static bt_node_ty *SideMostChildIMP(bt_node_ty *node, side_ty side_);

/* Find the first bigger/smaller than me ancestor,
 * depending on side_ value: RIGHT for smaller, LEFT for bigger */
static bt_node_ty *FirstAncestorIMP(bt_node_ty *node, side_ty side_);

/* find prev/next node according to provided side: 
 * LEFT for Prev and RIGHT for Next */
static bt_node_ty *PrevNext(bt_node_ty *node, side_ty side); /*TODO: is_next istead side parameter */

/*returns parent and side where the key SHOULD be */
static nodeANDside_ty FindIMP(btset_ty *set, const void *key);

/* get dummy's left child, which is the actual tree root */
static bt_node_ty *GetActRootIMP(btset_ty *set);

static int IsDummyIMP(bt_node_ty *node);

/******************************************************************************/

/* Return value: returns null when fails */
btset_ty *BTSetCreate(bts_cmp_fnc_ty cmp_fnc_, const void *cmp_param_)
{
    bt_node_ty *dummy = NULL;

    /* create btset struct */
    btset_ty *set = (btset_ty *)malloc(sizeof(btset_ty));
    CHECK_ALLOC(set, NULL, NULL, NULL); /*TODO: change name to CLEANRETURN..*/

    /* create dummy node */
    dummy = CreateNodeIMP(set);
    CHECK_ALLOC(dummy, set, NULL, NULL);

    /* set the created set members */
    set->m_root = dummy;
    set->m_cmp_func = cmp_fnc_;
    set->m_cmp_param = cmp_param_;

    /* return a pointer to created btset struct */
    return set;
}


void BTSetDestroy(btset_ty *set_)
{
    /* traverse the tree in postorder manner and destroy every traversed node: */
    /* get begin and end iterators */
    /* while begin != end */
        /* begin = BTSetRemove(btset, begin) */
    /* free dummy */
    /* free handle struct */

      /* counts nodes using postorder traversal, while last remembers the last node 
     * visited before the current */

    bt_node_ty *curr = NULL;
    bt_node_ty *node_to_free = NULL;

    assert(set_);

    curr = set_->m_root;

    /* while dummy is not reached */
    while (!BTSetIsEmpty(set_))
    {
        /* while there is left child, go left */
        while(curr->m_children[LEFT] != NULL)
        {
            curr = curr->m_children[LEFT];
        }

        /* if there is no left child or we going up from left subtree */
        if(curr->m_children[RIGHT] != NULL)
        {   
            /* go to the right child */
            curr = curr->m_children[RIGHT];
            /* continue - will start the loop to go left till no left child */
            continue;
        }
       
       /* if its a leafe - free the curr, go up to the parent  */
       node_to_free = curr;
       if(curr == curr->m_parent->m_children[LEFT])
       {
           curr->m_parent->m_children[LEFT] = NULL;
       }
       else if(curr == curr->m_parent->m_children[RIGHT])
       {
           curr->m_parent->m_children[RIGHT] = NULL;
       }
       curr = curr->m_parent;
       free(node_to_free);
    }
    free(set_->m_root);
    set_->m_root = NULL;
    free(set_);
}


btset_iter_ty BTSetInsert(btset_ty *set_, void *element_)
{ 
    btset_iter_ty inserted_iter = {NULL};
    bt_node_ty *new_node = NULL;
    nodeANDside_ty where = {NULL};

    assert(set_);

    /* create new node holding the provided data */
    new_node = CreateNodeIMP(element_);
    CHECK_ALLOC(new_node, NULL, NULL, inserted_iter);

    /* get the parent node and the side where the new node should be inserted */
    where = FindIMP(set_,element_);

    /* if the place to insert is vacant, attach the node and update iterator */
    if(where.m_node->m_children[where.m_side] == NULL)
    {
        AttachChildIMP(new_node, where.m_node, where.m_side);
        inserted_iter.m_node = new_node;
        DEBUG_ONLY(inserted_iter.set = set_);
    } 
    /* else, the element is already exists, bad iter will be returned */
    else
    {
        free(new_node);
    }
    return inserted_iter; /*TODO: Node2IterIMP(new_node, set) including the DEBUG*/
}


/* Return value: iterator to the next element */
btset_iter_ty BTSetRemove(btset_ty *set_, btset_iter_ty where_)
{
    btset_iter_ty next = {NULL};
    bt_node_ty *temp = NULL;
    side_ty side = 0;

    assert(set_);
    assert(where_.m_node);
    /* TODO: WHY do we need set_ here? */
    UNUSED(set_);

    next = BTSetNext(where_);
    /* side to indicate if I'm the left or right child of my parent */
    side = (where_.m_node == where_.m_node->m_parent->m_children[RIGHT]);

     /* if where has 2 sons, copy next data to where,
      * let where to point to 'next' node and next to point to where_ */
    if(where_.m_node->m_children[LEFT] && where_.m_node->m_children[RIGHT])
    {
        where_.m_node->m_data = next.m_node->m_data;
        temp = where_.m_node;
        where_.m_node = next.m_node;
        next.m_node = temp;
    }

    /* 1. if where is a leaf, set it parent 'side' child to NULL */
    if(where_.m_node->m_children[LEFT] == NULL && where_.m_node->m_children[RIGHT] == NULL)
    {   
        where_.m_node->m_parent->m_children[side] = NULL;      
    }

    /* 2. where has one son only (part of branch), 
     *    let where's parent to point to its son, remove where */
    else
    {
        AttachChildIMP(where_.m_node->m_children[where_.m_node->m_children[RIGHT] != NULL],
                       where_.m_node->m_parent,
                       side);
        
    }

    free(where_.m_node);
    return next;
}


btset_iter_ty BTSetFind(btset_ty *set_, const void *key_element_)
{
    btset_iter_ty found_iter = {NULL};

    /* get the parent node and the side where the new node should be found */
    nodeANDside_ty where = FindIMP(set_,key_element_);

    /* if the right place to insert is vacant, attach the node and update iterator */
    if(where.m_node->m_children[where.m_side] != NULL)
    {
        found_iter.m_node = where.m_node->m_children[where.m_side];
    } 
    /* else, the element not found, bad iter will be returned */

    return found_iter;
}


size_t BTSetSize(const btset_ty *set_)
{
    /* counts nodes using postorder traversal, while last remembers the last node 
     * visited before the current */
    bt_node_ty *curr = NULL;
    bt_node_ty *last = NULL;
    int count = 0;

    assert(set_);

    last = set_->m_root;
    curr = GetActRootIMP((btset_ty *)set_);

    /* if tree is empty, return 0 */
    if(curr == NULL)
    {
        return count;
    }

    /* while dummy is not reached */
    while (!IsDummyIMP(curr))
    {
        /* while there is left child, go left */
        while(last == curr->m_parent && curr->m_children[LEFT] != NULL)
        {
            last = curr;
            curr = curr->m_children[LEFT];
        }

        /* if there is no left child or we going up from left subtree */
        if((last == curr->m_parent || last == curr->m_children[LEFT]) &&
                                              curr->m_children[RIGHT] != NULL)
        {   
            /* update last and go right one step */
            last = curr;
            curr = curr->m_children[RIGHT];
            /* continue - will start the loop to go left till no left child */
            continue;
        }
       
       /* if its a leafe or we going up from right subtree - handle the curr */
       ++count;
       last = curr;
       /* go up to the parent */
       curr = curr->m_parent;
    }
    
    return count;
}

/* Returns pointer to the first element */
btset_iter_ty BTSetBegin(btset_ty *set_)
{
    btset_iter_ty start_iter = {NULL};
    DEBUG_ONLY(start_iter.set = set_);

    assert(set_); 

    /* return iterator to the leftmost leaf  */
    start_iter.m_node = SideMostChildIMP(GetActRootIMP(set_), LEFT);
    return start_iter;

    /* TODO: return Noede2Iter(SidemostChildIMP(&(set_->m_dummy), LEFT, set)*/
}


/* Returns pointer to the end */
btset_iter_ty BTSetEnd(btset_ty *set_)
{
    btset_iter_ty end_iter = {NULL};
    DEBUG_ONLY(end_iter.set = set_); 

    assert(set_);

    /* return iterator to the dummy node */
    end_iter.m_node = set_->m_root;
    return end_iter; /*TODO: return Node2Iter(&set_->m_dummy, set)*/
}

/* next on end iter is undefined */
btset_iter_ty BTSetNext(btset_iter_ty iterator_to_inc_)
{
    /* find the smallest among those who're bigger than me: */
    iterator_to_inc_.m_node = PrevNext(iterator_to_inc_.m_node, RIGHT); /*TODO: is*/

    return iterator_to_inc_;

}

/* prev on begin, i.e on smallest element in the tree, is undefined 
 * (in practice, dummy is returned)*/
btset_iter_ty BTSetPrev(btset_iter_ty iterator_to_dec_)
{
    /* find the biggest among those who smaller than me: */
    iterator_to_dec_.m_node = PrevNext(iterator_to_dec_.m_node, LEFT);

    return iterator_to_dec_;
}


int BTSetIsSameIter(btset_iter_ty first_, btset_iter_ty second_)
{
    assert(first_.set == second_.set);
    return (first_.m_node == second_.m_node); 
}


/* never change values of key fields */
void *BTSetGetData(btset_iter_ty where_)
{
    return where_.m_node->m_data;
}


/* 1 empty 0 not */
int BTSetIsEmpty(const btset_ty *set_)
{
    return (set_->m_root->m_children[0] == NULL);
}

/* 1 for bad iterator, 0 if good */
int BTSetIsIterBad(btset_iter_ty iter)
{
    /*TODO: assert not Dummy not bad iter*/
    return (iter.m_node == NULL || IsDummyIMP(iter.m_node));

}

/********************Helpers Implementation****************************************/
/* traverse left till the end and return pointer to leftmost leaf node */
static bt_node_ty *SideMostChildIMP(bt_node_ty *node_, side_ty side_)
{
    /* curr = node */
    bt_node_ty *curr = node_;

    assert(node_);
    assert(side_ == LEFT || side_ == RIGHT);

    /* while curr. side_son != NULL */
    while(curr->m_children[side_] != NULL)
    {
        /* curr = curr.side_son */
        curr = curr->m_children[side_];
    }

    /* return iterator to current */
    return curr;
}


static bt_node_ty *FirstAncestorIMP(bt_node_ty *node_, side_ty side_)
{
    bt_node_ty * curr = node_;

    assert(node_);
    assert(side_ == LEFT || side_ == RIGHT);

    /* while dummy is not reached */
    while(!IsDummyIMP(curr))
    {   
        /* if I am the LEFT/RIGHT side child of my parent, return parent */
        if(curr == curr->m_parent->m_children[side_])
        {
            return curr->m_parent;
        }
        /* promote curr to its parent */
        curr = curr->m_parent;
    }
    /* not found, dummy is returned */
    return curr;
}

static bt_node_ty *PrevNext(bt_node_ty *node_, side_ty side_)
{
    /* side = LEFT: prev - find the biggest among those who smaller than me */
    /* side = (RIGHT): next - find the smallest among those who bigger than me */

    /* if LEFT(RIGHT) child exist */
    if(node_->m_children[side_] != NULL)
    {
        /* go one time left(right) to the left(right) subteree */
        node_ = node_->m_children[side_];

        /* go right(left) all the way till the rightmost(leftmost) node is reached */
        node_ = SideMostChildIMP(node_, !side_);
    }
    else /* else if no left(right) child, find the closest ancestor that is
          * smaller(bigger) than me */
    { 
        node_ = FirstAncestorIMP(node_, !side_);
    }
   
   return node_;
}

static nodeANDside_ty FindIMP(btset_ty *set_, const void *key_)
{
    nodeANDside_ty ret = {NULL,0};
    bt_node_ty *curr = NULL;
    int cmp_res;

    assert(set_);

    /* set the ret struct node member to the set dummy */
    ret.m_node = set_->m_root;

    /* get dummy's left son, i.e the actual root */
    curr = GetActRootIMP(set_);

    while(curr != NULL)
    {
        /* store the compare result between the provided key and the curr data key */
        cmp_res = set_->m_cmp_func(key_, curr->m_data, NULL);

        /* if found, update the ret struct */
        if (cmp_res == 0)
        {
            ret.m_node = curr->m_parent;
            /* side = 0 if curr is the left child of its parent an 1 if the right child*/
            ret.m_side = (curr->m_parent->m_children[RIGHT] == curr); 
            return ret;
        }

        /* if not found and NULL reached, update the ret struct */
        if(curr->m_children[cmp_res > 0] == NULL) /* key not found */
        {
            ret.m_node = curr;
            ret.m_side = (cmp_res > 0);
            return ret;
        }
        /* if cmp_res > 0 curr = right child, else curr = left child*/
        curr = curr->m_children[cmp_res > 0];
    }
    return ret;
}

static void AttachChildIMP(bt_node_ty *node_, bt_node_ty *where_, side_ty side_)
{
    where_->m_children[side_] = node_;
    node_->m_parent = where_;
}

static void RemoveLeafIMP(btset_iter_ty leaf_iter_)
{
      
    assert(leaf_iter_.m_node->m_children[LEFT] == NULL && 
           leaf_iter_.m_node->m_children[RIGHT] == NULL);
       
        /* if I'm left son, set my parent's LEFT child to NULL */
         if(leaf_iter_.m_node == leaf_iter_.m_node->m_parent->m_children[LEFT])
       {
            leaf_iter_.m_node->m_parent->m_children[LEFT] = NULL;
        }/* else, if I'm a RIGHT son, set parent's RIGHT child to NULL*/
        else if(leaf_iter_.m_node == leaf_iter_.m_node->m_parent->m_children[RIGHT])
        {
            leaf_iter_.m_node->m_parent->m_children[RIGHT] = NULL;
        }
        /* free me */
        free(leaf_iter_.m_node);
}


static bt_node_ty *CreateNodeIMP(void *data_)
{
    /* create new node holding the provided data */
    bt_node_ty *new_node = (bt_node_ty *)malloc(sizeof(bt_node_ty));
    CHECK_ALLOC(new_node, NULL, NULL, NULL);

    new_node->m_data = data_;
    new_node->m_parent = NULL;
    new_node->m_children[0] = NULL;
    new_node->m_children[1] = NULL;

    return new_node;
}


static int IsDummyIMP(bt_node_ty *node_)
{
    return (node_->m_parent == NULL);
}

static bt_node_ty *GetActRootIMP(btset_ty *set_)
{
    return set_->m_root->m_children[0];
}

