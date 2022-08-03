#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include "recursion.h"

/*******************************HELPERS*******************************************/
static int IsNeedleIMP(const char *haystack, const char *needle);
static void Insert2SortedStackIMP(stack_ty *stack, int elem);


/*___________________________stack imp ___________________________________________*/

static int IsEmpty(stack_ty *stack)
{
    return stack->top == -1;
}

static int Pop(stack_ty *stack)
{
    if(IsEmpty(stack)) return INT_MIN;
    --stack->top;
    return stack->arr[stack->top + 1];
}

static void Push(stack_ty *stack, int num)
{
    if(stack->top == STACK_SIZE - 1) return ;
    ++stack->top;
    stack->arr[stack->top] = num;
}

static int Peek(stack_ty *stack)
{
    if(IsEmpty(stack)) return INT_MIN;

    return stack->arr[stack->top];
}

/*_________________________________________________________________________________*/


void SortStack(stack_ty *stack)
{
    int top_elem;

    /* if stack is empty or has one element, return */
    if(IsEmpty(stack) || stack->top == 0)
    {
        return;
    }

    /* Pop top element */
    top_elem = Pop(stack);
    /* Sort the stack */
    SortStack(stack);
    /* insert the top element back */
    Insert2SortedStackIMP(stack, top_elem);
}

static void Insert2SortedStackIMP(stack_ty *stack, int elem)
{
    int temp_elem;

    /* if the elem smaller/equal to top element, push*/
    if(elem <= Peek(stack) || IsEmpty(stack))
    {
        Push(stack, elem);
        return;
    }
    /* insert elem to the right place in the stack */
    temp_elem = Pop(stack);
    Insert2SortedStackIMP(stack, elem);
    Push(stack, temp_elem);
}

/*_________________________________________________________________________________*/


/* generate fibonacci sequence n'th term*/
int Fibonacci(int elem_idx)
{
    if(elem_idx < 2)
    {
        return elem_idx;
    }

    return Fibonacci(elem_idx - 1) + Fibonacci(elem_idx - 2);
}

int FibonacciIter(int elem_idx)
{
    int i = 0;
    int fib0 = 0, fib1 = 1, fibres = 0;
    
    if(elem_idx == 0)
    {
        return fib0;
    }
    else if(elem_idx == 1)
    {
        return fib1;
    }

    for (i = 2; i <= elem_idx; ++i)
    {
        fibres = fib0 + fib1;
        fib0 = fib1;
        fib1 = fibres;
    }
    return fibres;
}

/*_________________________________________________________________________________*/


/* reverse singly linked list */
node_ty *FlipList(node_ty *head)
{
    node_ty *reversed_head = NULL;

    /* if empty list or single node, return */
    if(head == NULL || head->next == NULL)
    {
        return head;
    }

    reversed_head = FlipList(head->next);
    head->next->next = head;
    head->next = NULL;

    /* propogate the new head upwards */
    return reversed_head;

}


/*_________________________________________________________________________________*/

size_t StrLen(const char *str)
{
    if(*str == '\0')
    {
        return 0;
    }

    return 1 + StrLen(str + 1);
}

/*_________________________________________________________________________________*/

int StrCmp(const char *str1, const char *str2)
{
    /*compare first char: if string is empty or unequal character is found return */
    if(!* str1 || *str1 != *str2)
    {
        return *str1 - *str2;
    }

    /* compare the rest */
    return StrCmp(str1+1, str2 + 1);
}

/*_________________________________________________________________________________*/

char *StrCpy(char *dest, const char *src)
{
    assert(dest);
    assert(src);
    /* copy the first character, if src is empty, it will be the null terminator */
    *dest = *src;

    /*if src is empty, return dest*/
    if(!*src)
    {
        return dest;
    }

    /* copy the rest of the string' return dest */
    StrCpy(dest + 1, src + 1);
    return dest;
}

/*_________________________________________________________________________________*/

char *StrCat(char *dest, const char *src)
{   /* if end of dest is reached, copy src to dest */
    if(!*dest)
    {
        StrCpy(dest, src);
        return dest;
    }

    /* prompte dest */
    StrCat(dest + 1, src);
    return dest;
}

/*_________________________________________________________________________________*/

/* Implementation 1 - single func */
char *StrStr1(const char *haystack, const char *needle)
{
    /* if needle end is reached, the needle found*/
    if(!*needle)
    {
        return (char *)haystack;
    }

    /* if haystack end is reached, the needle was not found, return NULL*/
    if(!*haystack)
    {
        return NULL;
    }

    /* if *haystack == *needle - good path **/
    if((*haystack == *needle) && (StrStr(haystack + 1, needle + 1) == haystack + 1))
    {
        return (char *)haystack;
    }

    /*opt for 215-219:
     * if (*haystack == * needle) return StrStr(haystack+1, needle+1);*/

    /* continue looking for needle in reduced haystack - bad path*/
    return StrStr(haystack + 1, needle);
}

/* Implementation 2 - tail recursion */
char *StrStr(const char *haystack, const char *needle)
{
    /* if needle end is reached, the needle found*/
    if(!*needle)
    {
        return (char *)haystack;
    }

    /* if haystack end is reached, the needle was not found, return NULL*/
    if(!*haystack)
    {
        return NULL;
    }

    /* if *haystack == *needle && whole needle found **/
    if(*haystack == *needle && IsNeedleIMP(haystack, needle))
    {
        return (char *)haystack;
    }

    /* continue looking for needle in reduced haystack */
    return StrStr(haystack + 1, needle);
}

int IsNeedleIMP(const char *haystack, const char *needle)
{
    /* if needle end is reached, the needle found*/
    if(!*needle)
    {
        return 1;
    }

    /* if haystack end is reached, the needle was not found, return NULL*/
    if(!*haystack || *haystack != *needle)
    {
        return 0;
    }
    return IsNeedleIMP(haystack + 1, needle + 1);
}

/* iterative strstr */
char *StrStrIter(const char *haystack, const char *needle)
{
    const char *haystack_curr = NULL;
    const char *needle_curr = NULL;

    while( *haystack)
    {
        while(*haystack && *haystack != *needle)
        {
            ++haystack;
        }

        if(*haystack == '\0') return NULL;

        haystack_curr = haystack;
        needle_curr = needle;

        while(*haystack_curr && *needle_curr && *haystack_curr == *needle_curr)
        {
            ++haystack_curr;
            ++needle_curr;
        }

        if(*needle_curr == '\0') return (char *)haystack; /* needle found */

        haystack = haystack_curr;
    }
    return NULL;

}