/*******************************************************************************
*	Written by:		Olga Danielle Cahana									   *
*	Date:			3/2/2022												   *
*	Reviewed by:	Daniel						    					 	   *
*																			   *
*******************************************************************************/

#include <stddef.h> /*size_t*/
#include <stdlib.h> /* malloc, free */
#include <assert.h>

#include "avl_tree.h"
#include "utils.h"

typedef enum balance
{
    LEFTHEAVY = 0,
    RIGHTHEAVY = 1,
    BALANCED = -1
} balance_factor_ty;

typedef enum side {LEFT = 0, RIGHT = 1} side_ty;

struct avl_tree
{
    avl_node_ty *m_root;
    avl_cmp_func_ty m_cmp_func;
    const void *m_cmp_param;
};

struct avl_tree_node
{
    void *data;
    avl_node_ty *m_children[2]; /* {0:ptr to left child, 1:ptr to right child }*/
    int height;
};

/************************Helpers***********************************************/
/* create new node holding the provided data - relatives pointers are nullified */
static avl_node_ty *CreateNodeIMP(void *data_);

/* return 1 if the node is a leaf */
static int IsLeaf(avl_node_ty *node);

static void AVLInsertIMP(avl_tree_ty *avl, avl_node_ty **subtree, avl_node_ty *new_node);

static void *FindIMP(avl_tree_ty *avl,avl_node_ty *subtree, void *find_key);

static void RemoveSubTreeIMP(avl_node_ty *root);


static int PreorderTraverseIMP(avl_node_ty *root, avl_op_func_ty op_func, void *op_param);
static int InorderTraverseIMP(avl_node_ty *root, avl_op_func_ty op_func, void *op_param);
static int PostorderTraverseIMP(avl_node_ty *root, avl_op_func_ty op_func, void *op_param);
static int GetBalanceFactorIMP(avl_node_ty *node);
static void RebalanceTreeIMP(avl_node_ty *root);

static int Add1IMP(void *data, void *param);
static void RebalanceIMP(avl_node_ty **subtree);
static int GetHeightIMP(avl_node_ty *node);
static void RotateSideIMP(avl_node_ty **node, side_ty side);


/******************************************************************************/


avl_tree_ty *AVLCreate(avl_cmp_func_ty cmp_func, const void *param)
{
    avl_tree_ty *avl_tree = NULL; 
    /* create avl tree handle struct (avl_ty *) */
    avl_tree = (avl_tree_ty *)malloc(sizeof(avl_tree_ty));
    CHECK_ALLOC_IFBAD_FREE_RETURN(avl_tree, NULL, NULL, NULL);

    /* init avl members */
    avl_tree->m_root = NULL;
    avl_tree->m_cmp_func = cmp_func;
    avl_tree->m_cmp_param = param;

    /* return a pointer to created struct */
    return avl_tree;
}

void AVLDestroy(avl_tree_ty *avl)
{
    /* free all tree nodes */
    RemoveSubTreeIMP(avl->m_root);

    /* free handle struct */
    avl->m_root = NULL;
    free(avl);
}

int AVLInsert(avl_tree_ty *avl, void *elem)
{
    avl_node_ty *new_node = CreateNodeIMP(elem);

    /* assert sub_tree, tree */
    assert(avl);

    AVLInsertIMP(avl, &(avl->m_root), new_node);

    return 0;
}

int AVLRemove(avl_tree_ty *avl, const void *key_to_remove)
{
/*  returns 1 if fails, 0 on success */

}

/* returns void * to data */
void *AVLFind(avl_tree_ty *avl, void *find_key)
{
    assert(avl);

    return FindIMP(avl, avl->m_root, find_key);
}

size_t AVLHeight(const avl_tree_ty *avl)
{
    return avl->m_root->height;
}

size_t AVLSize(const avl_tree_ty *avl)
{
    size_t count = 0;
    avl_op_func_ty op_func = Add1IMP;

    assert(avl);

    AVLForEach((avl_tree_ty *)avl, op_func, &count, PREORDER);
    return count;
}

int AVLIsEmpty(const avl_tree_ty *avl)
{
    /* if root is NULL return 1, otherwise 0 */
    return avl->m_root == NULL;
}

/*  returns 1 if fails, 0 on success. */
int AVLForEach( avl_tree_ty *avl,
                avl_op_func_ty op_func,
                void *op_param,
                traverse_ty travel_type)
{
    assert(avl);

    /* switch travel type :*/
    switch (travel_type)
    {
    /* case PREORDER: return PreorderTraverseIMP */
    case PREORDER:
        return PreorderTraverseIMP(avl->m_root, op_func, op_param);

    /* case INORDER: return InorderTraverseIMP */
    case INORDER:
        return InorderTraverseIMP(avl->m_root, op_func, op_param);

    /* case POSTORDER: return PreorderTraverseIMP */
    case POSTORDER:
        return PostorderTraverseIMP(avl->m_root, op_func, op_param);

    default:
        return 1;
    }



}

/*  returns number of removed elements.*/
size_t AVLRemoveMultiple(avl_tree_ty *avl,
                         avl_match_func_ty ismatch,
                         const void *match_param)
{
    /*TODO: implement */
    return 0;
}


/********************Helpers Implementation****************************************/
static avl_node_ty *CreateNodeIMP(void *data)
{
    /* create new node holding the provided data */
    avl_node_ty *new_node = (avl_node_ty *)malloc(sizeof(avl_node_ty));
    CHECK_ALLOC_IFBAD_FREE_RETURN(new_node, NULL, NULL, NULL);

    new_node->data = data;
    new_node->m_children[0] = NULL;
    new_node->m_children[1] = NULL;
    new_node->height = 0;

    return new_node;
}

static void AVLInsertIMP(avl_tree_ty *avl, avl_node_ty **subtree, avl_node_ty *new_node)
{
    side_ty side;

    /* assert sub_tree, tree */
    assert(subtree);
    assert(new_node);
    assert(avl);

    /* if *subtree == null */
    if(*subtree == NULL)
    {
        /* insert here */
       *subtree = new_node;
        return;
    } 

    /* assert not equal to current node */
     assert(avl->m_cmp_func((*subtree)->data, new_node->data , avl->m_cmp_param) != 0);

    /* AvlInsert(children[side]) */
    side = (avl->m_cmp_func(new_node->data, (*subtree)->data, avl->m_cmp_param) > 0);
    AVLInsertIMP(avl, &((*subtree)->m_children[side]), new_node);

    /* update subtree height */
  
    RebalanceIMP(subtree);
 
    /* get new balance factor*/
    /* rebalance the tree if necessary */

}

static void *FindIMP(avl_tree_ty *avl,avl_node_ty *subtree, void *find_key)
{
    int cmp_res = 0;

    /* if NULL is reached, i.e. key not found, return NULL */
    if(subtree == NULL)
    {
        return NULL;
    }

    /* compare the key to current node data */
    cmp_res = avl->m_cmp_func(find_key, subtree->data, avl->m_cmp_param);

    /* if cmp_res = 0, the key found, return the data */
    if(cmp_res == 0)
    {
        return subtree->data;
    }

    FindIMP(avl, subtree->m_children[cmp_res > 0], find_key);
}

static void RemoveSubTreeIMP(avl_node_ty *root)
{
    /* traverse the tree in postorder manner */
    /* if node is NULL, return */
    if(root == NULL)
    {
        return;
    }
    /* traverse left subtree */
    RemoveSubTreeIMP(root->m_children[LEFT]);

    /* traverse right subtree */
    RemoveSubTreeIMP(root->m_children[RIGHT]);

    /* handle (free) the root */
    free(root);
}


static int InorderTraverseIMP(avl_node_ty *root, avl_op_func_ty op_func, void *op_param)
{
    int res = 0;

    /* if the root is NULL, return 0 (success) */
    if(root == NULL)
    {
        return 0;
    }

    /* inorder travers on left sub tree, if failure detected return 1 */
    res = InorderTraverseIMP(root->m_children[LEFT], op_func, op_param);
    if( res != 0)
    {
        return res;
    } 

    /* handle the root, if failed, return 1 */
    res = op_func(root->data, op_param);
    if(res != 0)
    {
        return res;
    }

    /* inorder travers on right sub tree, if failure detected return 1 */
    res = InorderTraverseIMP(root->m_children[RIGHT], op_func, op_param); 
    if(res != 0)
    {
        return res;
    }

    /* no failure detected */
    return 0;
}

static int PreorderTraverseIMP(avl_node_ty *root, avl_op_func_ty op_func, void *op_param)
{
    int res = 0;

    /* if the root is NULL, return 0 (success) */
    if(root == NULL)
    {
        return 0;
    }

    /* handle the root, if failed, return 1 */
    res = op_func(root->data, op_param);
    if(res != 0)
    {
        return res;
    }

    /* preorder travers on left sub tree, if failure detected return 1 */
    res = PreorderTraverseIMP(root->m_children[LEFT], op_func, op_param);
    if(res != 0)
    {
        return res;
    }

    /* preorder travers on right sub tree, if failure detected return 1 */
    res = PreorderTraverseIMP(root->m_children[RIGHT], op_func, op_param);
    if(res != 0)
    {
        return res;
    }

    /* no failure detected */
    return 0;
}


static int PostorderTraverseIMP(avl_node_ty *root, avl_op_func_ty op_func, void *op_param)
{
    int res = 0;

    /* if the root is NULL, return 0 (success) */
    if(root == NULL)
    {
        return 0;
    }

    /* postorder travers on left sub tree, if failure detected return 1 */
    res = PostorderTraverseIMP(root->m_children[LEFT], op_func, op_param);
    if(res != 0)
    {
        return res;
    } 

    /* postorder travers on right sub tree, if failure detected return 1 */
    res = PostorderTraverseIMP(root->m_children[RIGHT], op_func, op_param);
    if(res != 0)
    {
        return res;
    }

    /* handle the root, if failed, return 1 */
    res = op_func(root->data, op_param);
    if(res != 0)
    {
        return res;
    }

    /* no failure detected */
    return 0;
}


static int GetBalanceFactorIMP(avl_node_ty *node)
{
    if(!node)
    {
        return 0;
    }

    /* return left subtree height - right subtree height */
    return GetHeightIMP(node->m_children[LEFT]) - 
            GetHeightIMP(node->m_children[RIGHT]);
}

static int GetHeightIMP(avl_node_ty *node)
{
    return (node == NULL) ? -1 : node->height;
}


static void RebalanceIMP(avl_node_ty **subtree)
{
    int balance_factor = 0;
    int child_balance = 0;

    assert(subtree);

    if(*subtree == NULL)
    {
        return;
    }

    /* get subtree balance factor */
    balance_factor = GetBalanceFactorIMP(*subtree);

    /* if balance factor is 2 or -2, rebalancing is required */
    if(balance_factor > 1 || balance_factor < -1)
    {
        child_balance = GetBalanceFactorIMP((*subtree)->m_children[balance_factor < 0]);

        /* if balance of right/left child is 1/-1 accordingly */
        if(balance_factor / -2 == child_balance)
        {
            /* rotate right child right if BF = -2 and left child left if BF = 2 */
            RotateSideIMP(&((*subtree)->m_children[balance_factor < 0]),
                          balance_factor < 0);
        }

        /* rotate parrent to opposite side */
        RotateSideIMP(subtree, balance_factor > 0);
    }

    /* update subtree root height */
    (*subtree)->height = 1 + MAX2(GetHeightIMP((*subtree)->m_children[LEFT]), 
                                  GetHeightIMP((*subtree)->m_children[RIGHT]));

}


static void RotateSideIMP(avl_node_ty **node, side_ty side)
{
    avl_node_ty *temp = NULL;

    /* temp = node.!side.side */
    temp = (*node)->m_children[!side]->m_children[side];
    (*node)->m_children[!side] = *node;
    *node = (*node)->m_children[!side];
    (*node)->m_children[side]->m_children[!side] = temp;

    return;
    
}

static int IsLeaf(avl_node_ty *node)
{
    if(node->m_children[LEFT] == NULL && node->m_children[RIGHT] == NULL)
    {
        return 1;
    }
    return 0;
}

static int Add1IMP(void *data, void *param)
{
	UNUSED(data);

	++(*(size_t *)param);
	return 0;
}