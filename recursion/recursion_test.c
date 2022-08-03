#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "recursion.h"

static void Fibonacci_Test(void);

static void FibonacciIter_Test(void);


static void ListFlip_Test(void);

static void TestSortStack(void);

/*Test for TestStrLen function */
static void TestStrLen(void);

/*Test for TestStrCmp function */
static void TestStrCmp(void);

/*Test for TestStrCpy function */
static void TestStrCpy(void);

/*Test for TestStrCat function */
static void TestStrCat(void);

/*Test for TestStrStr function */
static void TestStrStr(void);

static void TestStrStrIter(void);

static void PrintList(node_ty *head);

static void PrintStack(stack_ty *stack);



int main(void)
{
    Fibonacci_Test();
    FibonacciIter_Test();
    ListFlip_Test();
    TestStrLen();
    TestStrCpy();
    TestStrCmp();
    TestStrCat();
    TestStrStr();
	TestStrStrIter();
    TestSortStack();
    return 0;
}

static void TestSortStack(void)
{
    stack_ty stack_ = {{1,5,2,45,3,7,12,9,10,0}, STACK_SIZE - 1};
    stack_ty *stack = &stack_;

    PrintStack(stack);
    SortStack(stack);
    PrintStack(stack);
}


static void Fibonacci_Test(void)
{
    int i = 0;

    printf("Fibonacci testing:\n");
    for(i = 0; i < 20; ++i)
    {
        printf("%d: %d \n", i, Fibonacci(i));
    }
    printf("\n");
}

static void FibonacciIter_Test(void)
{
    int i = 0;

    printf("Fibonacci iterative testing:\n");
    for(i = 0; i < 20; ++i)
    {
        printf("%d: %d \n", i, FibonacciIter(i));
    }
    printf("\n");
}

static void ListFlip_Test(void)
{
    node_ty node1, node2, node3, node4, node5, node6, node7, node8;
	
	int x1 = 1, x2 = 2, x3 = 3, x4 = 4, x5 = 5, x6 = 6, x7 = 7, x8 = 8;
	
	node_ty *head1 = &node1;
	
	node1.data = x1;
	node2.data = x2;
	node3.data = x3;
	node4.data = x4;
	node5.data = x5;
	node6.data = x6;
	node7.data = x7;
	node8.data = x8;
	
	
	/*Liniar list*/
	node1.next = &node2;
	node2.next = &node3;
	node3.next = &node4;
	node4.next = &node5;
	node5.next = &node6;
	node6.next = &node7;
	node7.next = &node8;
	node8.next = NULL;
	
	printf("Flip list testing:\n");
	PrintList(head1);	
	head1 = FlipList(head1); 
	PrintList(head1);
 
}

void TestStrLen(void)
{
    char *str = "abcdef";
    char *str1 = "";
    char *str2 = "a";
    char *str3 = "abcdef gg";

    printf("\nStrLen testing:\n");

    printf("%s length is %ld\n", str, StrLen(str));

    printf("%s length is %ld\n", str1, StrLen(str1));

    printf("%s length is %ld\n", str2, StrLen(str2));
 
    printf("%s length is %ld\n", str3, StrLen(str3));
}

void TestStrCpy(void)
{
	const char * src1 = "Hello World";
	const char * src2 = "";
	char dest1[50] = {0};
	char dest11[50] = {0};
	char dest2[12] = {0};
	char dest22[12] = {0};
	
	printf("StrCpy testing:\n");
	/*tests 1-3: compare StrCpy and strcpy returned strings, using StrCmp */
	StrCmp(StrCpy(dest1,src1),strcpy(dest11, src1)) == 0 ?
		printf("test1 Passed\n") : printf("test1 Failed!!\n");
	StrCmp(StrCpy(dest2, src1), strcpy(dest22,src1)) == 0 ?
		printf("test2 Passed\n") : printf("test2 Failed!!\n");	
	StrCmp(StrCpy(dest1, src2), strcpy(dest11,src2)) == 0 ?
		printf("test3 Passed\n") : printf("test3 Failed!!\n");
	/*tests 4-5: compare returned addresses*/
	StrCpy(dest1,src1) == strcpy(dest1,src1) ?
		printf("test4 Passed\n") : printf("test4 Failed!!\n");	
	(StrCpy(dest1,src2) != strcpy(dest11,src2)) ?
		printf("test5 Passed\n") : printf("test5 Failed!!\n");
	/* test 6: compare output string length using StrLen */
	StrLen(StrCpy(dest2, src1)) == StrLen(strcpy(dest1,src1)) ? 
		printf("test6 Passed\n") : printf("test6 Failed!!\n");

}

static void TestStrCmp(void)
{
    char *str1 = "Hello World";
	char *str2 = "Hello World";
	char *str3 = "";
	char *str4 = "Hello6&&$#@World";
	
	printf("\nStrCmp testing:\n");
	StrCmp(str1,str2) == strcmp(str1, str2) ?
		printf("test1 Passed\n") : printf("test1 Failed!!\n");
	StrCmp(str1, str3) * strcmp(str1, str3) > 0 ?
		printf("test2 Passed\n") : printf("test2 Failed!!\n");
	StrCmp(str1,str4) * strcmp(str1, str4) > 0 ?
		printf("test3 Passed\n") : printf("test3 Failed!!\n");
	StrCmp(str3,str3) == strcmp(str3, str3) ?
		printf("test4 Passed\n") : printf("test4 Failed!!\n");

}

/*Test for TestStrCat function */
static void TestStrCat(void)
{
	char dest1[8] = "Hi";
	char dest2[8] = "Hi";
	char dest3[8] = "";
	printf("\nStrCat testing:\n");
	StrCmp("HiBye", StrCat(dest1,"Bye")) == 0 ?
		printf("test1 Passed\n") : printf("test1 Failed!!\n");
	StrCmp("Hi", StrCat(dest2,"")) == 0 ?
		printf("test2 Passed\n") : printf("test2 Failed!!\n");
	StrCmp("HiBye!!!", StrCat(dest2,"Bye!!!")) == 0 ?
		printf("test3 Passed\n") : printf("test3 Failed!!\n"); 
	StrCmp("Bye", StrCat(dest3,"Bye")) == 0 ?
		printf("test4 Passed\n") : printf("test4 Failed!!\n"); 
}



static void TestStrStr(void)
{
    char *result = NULL;
	printf("\nStrStr testing:\n");

	result = StrStr("Where is the sub string??","Where");
	StrCmp(result, "Where is the sub string??") == 0 ?
		printf("test1 Passed\n") : printf("test1 Failed!!\n");

	result = StrStr("Where is the sub string??","sub");
	StrCmp(result, "sub string??") == 0 ?
		printf("test2 Passed\n") : printf("test2 Failed!!\n");

	result = StrStr("Where is the sub string??","??");
	StrCmp(result, "??") == 0 ?
		printf("test3 Passed\n") : printf("test3 Failed!!\n");

	result = StrStr("Where is the sub string??","string?!");
    result == NULL ?
		printf("test4 Passed\n") : printf("test4 Failed!!\n");
}

static void TestStrStrIter(void)
{
    char *result = NULL;
	printf("StrStrIter testing:\n");

	result = StrStrIter("Where is the sub string??","Where");
	StrCmp(result, "Where is the sub string??") == 0 ?
		printf("test1 Passed\n") : printf("test1 Failed!!\n");

	result = StrStrIter("Where is the sub string??","sub");
	StrCmp(result, "sub string??") == 0 ?
		printf("test2 Passed\n") : printf("test2 Failed!!\n");

	result = StrStrIter("Where is the sub string??","??");
	StrCmp(result, "??") == 0 ?
		printf("test3 Passed\n") : printf("test3 Failed!!\n");

	result = StrStrIter("Where is the sub string??","string?!");
    result == NULL ?
		printf("test4 Passed\n") : printf("test4 Failed!!\n");
}




static void PrintList(node_ty *head)
{
	while(head)
	{
		printf("%d  ", head->data);
		head = head->next;
	}
	printf("\n");
}	

 static void PrintStack(stack_ty *stack)
 {
     int i = stack->top;
     for(; i >= 0; --i)
     {
         printf("%d ",stack->arr[i]);
     }
     printf("\n");
 }