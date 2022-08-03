#ifndef __HASH_MAP__
#define __HASH_MAP__

#include <stddef.h>

typedef struct hash_map hash_ty;
typedef size_t(*hash_func_ty)(const void * elem, const void *param);
typedef int(*is_same_ty)(const void * elem1, const void * elem2);

struct hash_map
{
    int *hash_arr;
    int capacity;
};

/* recommendation: size should be a prime number*/
hash_ty *HashCreate(hash_func_ty hash_func,const void *param 
is_same_ty cmp_func, size_t size);

/* null is allowed */
void HashDestroy(hash_ty *hash_table);


int HashInsert(hash_ty *hash_map, void *elem);


void *HashFind(hash_ty *hash_map, void *elem);

/* returns 1 if fails to find the element */
int HashRemove(hash_ty *hash_map, void *elem);

int HashFreeSize(hash_ty *hash_map);

/* num of elements in the hash */
int HashSize(hash_ty *hash_map);



hash_stats_ty HashStats(const hash_map *)

#endif /* __HASH_MAP__ */
