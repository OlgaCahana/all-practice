#ifndef __RECURSION__
#define __RECURSION__

#include <stddef.h>

#define STACK_SIZE 10
typedef struct node node_ty;

struct node 
{
    int data;
    node_ty *next;
};

typedef struct stack
{
    int arr[STACK_SIZE];
    int top;

}stack_ty;


int Fibonacci(int elem_idx);

int FibonacciIter(int elem_idx);

node_ty *FlipList(node_ty *head);

void SortStack(stack_ty *stack);


/* The StrLen() function calculates the length of the string pointed to by
     							  s, excluding the terminating null byte ('\0')
Returns the number of bytes in the string pointed to by s
*/
size_t StrLen(const char *s);


/*
The  StrCmp()  function compares the two strings s1 and s2.  The locale
       is not taken into account (for  a  locale-aware  comparison,  see  str‐
       coll(3)).   It  returns an integer less than, equal to, or greater than
       zero if s1 is found, respectively, to be less than,  to  match,  or  be
       greater than s2.
*/
int StrCmp(const char *str1, const char *str2);

/* Copies the string pointed to by src, including the terminating null byte ('\0'),
to the buffer  pointed  to  by  dest. The  strings  may  not overlap, 
and the destination string dest must be large enough to receive the copy.
Returns a pointer to the destination string dest */
char *StrCpy(char *dest, const char *src);

/*Strings concatination: appends the src string to the dest string,
overwriting the terminating null byte ('\0') at the end of dest, and then adds 
a terminating null byte. The dest string must have enough space for the result.
If dest is not large enough, behavior is unpredictable.
Returns a pointer to the resulting string dest*/
char *StrCat(char *dest, const char *src);

 /*Locate a substring
Finds the first occurrence of the substring find_str in the string orig_str.
The terminating null bytes ('\0') are not compared.
Returns a pointer to the beginning of the located substring or NULL if not found.
 */
char *StrStr(const char *orig_str, const char *find_str);
char *StrStrIter(const char *haystack, const char *needle);


#endif /* __RECURSION__ */