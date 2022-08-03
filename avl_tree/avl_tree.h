#ifndef __AVL_TREE_H__
#define __AVL_TREE_H__

#include <stddef.h> /*	size_t	*/ 

typedef enum
{
    INORDER,
    POSTORDER,
    PREORDER
}traverse_ty;

typedef struct avl_tree avl_tree_ty;
typedef struct avl_tree_node avl_node_ty;


/* cmp func: It returns an integer less than, equal to, or greater than zero 
             if key1 is  found,  respectively, to be less than, to match, or 
             be greater than key2. */
typedef int(*avl_cmp_func_ty)(const void *elem1,
                              const void *elem2,
                              const void *param);

/*  op func returns 1 on failure */
typedef int(*avl_op_func_ty)(void *elem, void *op_param);

/*  match func returns 1 on match, 0 on mismatch */
typedef int(*avl_match_func_ty)(const void *elem, const void *match_param);




/* General Notes:
    *   AVL Tree cannot contain 2 identical keys.
    *   
    *  */

/*  Return Value: NULL if fails.  */
avl_tree_ty *AVLCreate(avl_cmp_func_ty cmp_func, const void *param);	

void AVLDestroy(avl_tree_ty *avl);

/*  returns 1 if key not found, 0 on success */
int AVLRemove(avl_tree_ty *avl, const void *key_to_remove);

/*  undefined behaviour if key already exists in list */
/*  returns 1 if fails, 0 on success */
int AVLInsert(avl_tree_ty *avl, void *elem);

size_t AVLHeight(const avl_tree_ty *avl);

size_t AVLSize(const avl_tree_ty *avl);

int AVLIsEmpty(const avl_tree_ty *avl);

/* returns void * to data */
void *AVLFind(avl_tree_ty *avl, void *find_key);

/*  returns 1 if fails, 0 on success. */
int AVLForEach( avl_tree_ty *avl,
                avl_op_func_ty op_func,
                void *op_param,
                traverse_ty travel_type);

/*  returns number of removed elements.*/
size_t AVLRemoveMultiple(avl_tree_ty *avl,
                         avl_match_func_ty ismatch,
                         const void *match_param);


#endif /* __AVL_TREE_H__ */


