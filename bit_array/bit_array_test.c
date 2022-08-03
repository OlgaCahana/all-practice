/*******************************************************************************
*	Written by:		Olga Danielle Cahana									   *
*	Date:			13/12/221												   *
*	Reviewed by:	Larisa					    							   *
*																			   *
*******************************************************************************/
#include <stdio.h> /* printf */ 
#include <stdlib.h> /* malloc, free */
#include <stddef.h> /* size_t, sizeof */
#include <assert.h> /* assert */

#include "bit_array.h"


/* Helper, prints a binary representation of an unsigned long integer */
static void BinaryPrint(unsigned long num);

/****************Tests declarations********************************************/

void TestBitArraySetAll(void);
void TestBitArrayResetAll(void);
void TestBitArrayToString(void);
void TestBitArraySetOn(void);
void TestBitArraySetOff(void);
void TestBitArraySetBit(void);
void TestBitArrayGetVal(void);
void TestBitArrayFlip(void);
void TestBitArrayMirror(void);
void TestBitArrayRotR(void);
void TestBitArrayRotL(void);
void TestBitArrayCountOn(void);
void TestBitArrayCountOff(void);


/****************************Main********************************************/
int main(void)
{
	TestBitArraySetAll();
	TestBitArrayResetAll();
	TestBitArrayToString();
	TestBitArraySetOn();
	TestBitArraySetOff();
	TestBitArraySetBit();
	TestBitArrayGetVal();
	TestBitArrayFlip();
	TestBitArrayMirror();
	TestBitArrayRotR();
	TestBitArrayRotL();
	TestBitArrayCountOn();
	TestBitArrayCountOff();
	return 0;

}


void TestBitArraySetAll(void)
{
	bit_array_ty my_bit_array = 0;
	
	printf("Testing set_all:\n");
	BinaryPrint(my_bit_array);	
	
	my_bit_array = BitArraySetAll(my_bit_array);
	BinaryPrint(my_bit_array);
	my_bit_array == -1lu ? printf("Test passed\n") : printf("Test Failed!!\n");	
}

void TestBitArrayResetAll(void)
{
	bit_array_ty my_bit_array = 11lu;
	
	printf("\nTesting reset_all:\n");
	BinaryPrint(my_bit_array);
		
	my_bit_array = BitArrayResetAll(my_bit_array);
	BinaryPrint(my_bit_array);
	my_bit_array == 0lu ? printf("Test passed\n") : printf("Test Failed!!\n");	
}

void TestBitArrayToString(void)
{
	char *dest = (char *)malloc((BIT_ARRAY_SIZE + 1) * sizeof(char));
	bit_array_ty my_bit_array = 0x8888888877777777lu;
	
	assert(dest);
	 
	printf("\nTesting ToString:\n");
	dest = BitArrayToString(my_bit_array, dest);
	printf("%s\n",dest);
	
	free(dest);
}

void TestBitArraySetOn(void)
{
	bit_array_ty my_bit_array = 0;
	
	printf("\nTesting BitArraySetOn:\n");
	BinaryPrint(my_bit_array);
	
	my_bit_array = BitArraySetOn(my_bit_array, 4);
	BinaryPrint(my_bit_array);
	my_bit_array == 0x10lu ? printf("Test passed\n") : printf("Test Failed!!\n");

}

void TestBitArraySetOff(void)
{
	bit_array_ty my_bit_array = 0xFFFFFFFFFFFFFFF1lu;
	
	printf("\nTesting BitArraySetOff:\n");
	BinaryPrint(my_bit_array);
	
	my_bit_array = BitArraySetOff(my_bit_array, 4);
	BinaryPrint(my_bit_array);
	my_bit_array == 0xFFFFFFFFFFFFFFE1lu ? 
							printf("Test passed\n") : printf("Test Failed!!\n");
							
	my_bit_array = BitArraySetOff(my_bit_array, 2);
	BinaryPrint(my_bit_array);
	my_bit_array == 0xFFFFFFFFFFFFFFE1lu ? 
							printf("Test passed\n") : printf("Test Failed!!\n");

}

void TestBitArraySetBit(void)
{
	bit_array_ty my_bit_array = 0xF1lu;
	
	printf("\nTesting BitArraySetBit:\n");
	BinaryPrint(my_bit_array);
	my_bit_array = BitArraySetBit(my_bit_array, 4, 1); /* 1 -> 1 */
	BinaryPrint(my_bit_array);
	my_bit_array == 0xF1lu ? 
							printf("Test passed\n") : printf("Test Failed!!\n");
							
	my_bit_array = BitArraySetBit(my_bit_array, 4, 0); /* 1 -> 0 */
	BinaryPrint(my_bit_array);
	my_bit_array == 0xE1lu ? 
							printf("Test passed\n") : printf("Test Failed!!\n");
							
	my_bit_array = BitArraySetBit(my_bit_array, 4, 1); /* 0 -> 1 */
	BinaryPrint(my_bit_array);
	my_bit_array == 0xF1lu ? 
							printf("Test passed\n") : printf("Test Failed!!\n");
							
	my_bit_array = BitArraySetBit(my_bit_array, 2, 0); /* 0 -> 0 */
	BinaryPrint(my_bit_array);
	my_bit_array == 0xF1lu ? 
							printf("Test passed\n") : printf("Test Failed!!\n");
}

void TestBitArrayGetVal(void)
{
	bit_array_ty my_bit_array = 0x8F00000000000088;
	
	printf("\nTesting BitArrayGetValue:\n");
	BinaryPrint(my_bit_array);
	
	printf("value of first bit is: %d\n", BitArrayGetVal(my_bit_array, 0));
	printf("value of index 3 (4th bit): %d\n", BitArrayGetVal(my_bit_array, 3));
	printf("the value of last bit is: %d\n", BitArrayGetVal(my_bit_array,63));	
}

void TestBitArrayFlip(void)
{
	bit_array_ty my_bit_array = 0x88;
	
	printf("\nTesting BitArrayFlip:\n");
	BinaryPrint(my_bit_array);
	
	my_bit_array = BitArrayFlip(my_bit_array, 3); /* 1 -> 0 */
	BinaryPrint(my_bit_array);
	my_bit_array = 0x80lu ? printf("Test passed\n") : printf("Test Failed!!\n");
	
	my_bit_array = BitArrayFlip(my_bit_array, 0); /* 0 -> 1 */
	BinaryPrint(my_bit_array);
	my_bit_array = 0x81lu ? printf("Test passed\n") : printf("Test Failed!!\n");
}


void TestBitArrayMirror(void)
{
	bit_array_ty my_bit_array = 0x8F00000000000088;
	
	printf("\nTesting BitArrayMirror:\n");
	BinaryPrint(my_bit_array);
	
	my_bit_array = BitArrayMirror(my_bit_array);
	BinaryPrint(my_bit_array);
	my_bit_array == 0x11000000000000F1 ?
							printf("Test passed\n") : printf("Test Failed!!\n");
							
	printf("\nTesting BitArrayMirror_LUT:\n");
	my_bit_array = 0x8F00000000000088;
	my_bit_array = BitArrayMirror(my_bit_array);
	my_bit_array == 0x11000000000000F1 ?
							printf("Test passed\n") : printf("Test Failed!!\n");
}

void TestBitArrayRotR(void)
{
	bit_array_ty my_bit_array = 0x8F00000000000083;
	
	printf("\nTesting BitArrayRotR:\n");
	BinaryPrint(my_bit_array);
	
	my_bit_array = BitArrayRotR(my_bit_array, 10);
	BinaryPrint(my_bit_array);
	my_bit_array == 0x20E3C00000000000 ? 
		  					printf("Test passed\n") : printf("Test Failed!!\n");
}
void TestBitArrayRotL(void)
{
	bit_array_ty my_bit_array = 0x8F00000000000083;
	
	printf("\nTesting BitArrayRotL:\n");
	BinaryPrint(my_bit_array);
	
	my_bit_array = BitArrayRotL(my_bit_array, 2);
	BinaryPrint(my_bit_array);
	my_bit_array == 0x3C0000000000020E ? 
							printf("Test passed\n") : printf("Test Failed!!\n");
}

void TestBitArrayCountOn(void)
{
	bit_array_ty my_bit_array = 0x5555555555555550lu; /* 0x5 == 0101 */
	
	printf("\nTesting BitArrayCountOn:\n");
	printf("%d\n", BitArrayCountOn(my_bit_array));
	
	BitArrayCountOn(my_bit_array) == 30 ?
						  printf("Test passed\n") : printf("Test Failed!!\n");
						  
	printf("\nTesting BitArrayCountOn_LUT:\n");
	BitArrayCountOn_LUT(my_bit_array) == 30 ?
						  printf("Test passed\n") : printf("Test Failed!!\n");

}
void TestBitArrayCountOff(void)
{
	bit_array_ty my_bit_array = 0x5555555555555555lu;
	
	printf("\nTesting BitArrayCountOff:\n");
	printf("%d\n", BitArrayCountOff(my_bit_array));
	
	BitArrayCountOff(my_bit_array) == 32 ?
						  printf("Test passed\n") : printf("Test Failed!!\n");
}

/****************************Helpers Implementation****************************/
/* helper, prints a binary representation of an unsigned long integer */
static void BinaryPrint(size_t num)
{
	size_t mask = 0x1;

	for (mask <<= (BIT_ARRAY_SIZE - 1) ; mask > 0; mask >>= 1)
	{
		(num & mask) >= 1 ? printf("1") : printf("0");
	}
	printf("\n");
}

