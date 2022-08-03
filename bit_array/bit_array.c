/*******************************************************************************
*	Written by:		Olga Danielle Cahana									   *
*	Date:			13/12/221												   *
*	Reviewed by:	Larisa					    							   *
*																			   *
*******************************************************************************/
#include <assert.h> /* assert */
#include <stdio.h> /* printf */ 
#include "bit_array.h"

/* Macros to generate the lookup table to count set bits (at compilation) */
#define B2(n) n, n + 1, n + 1, n + 2
#define B4(n) B2(n), B2(n + 1), B2(n + 1), B2(n + 2)
#define B6(n) B4(n), B4(n + 1), B4(n + 1), B4(n + 2)
#define COUNT_BITS B6(0), B6(1), B6(1), B6(2)

/* Macros to generate the lookup table for bits mirror (at compile-time) */
#define R2(n) n, n + 2*64, n + 1*64, n + 3*64
#define R4(n) R2(n), R2(n + 2*16), R2(n + 1*16), R2(n + 3*16)
#define R6(n) R4(n), R4(n + 2*4 ), R4(n + 1*4 ), R4(n + 3*4 )
#define REVERSE_BITS R6(0), R6(2), R6(1), R6(3)



/******************************************************************************
* Function Description: sets the values of all bits of the array to 1	       
* Arguments: data - bit_array_ty.
* Return value: bit array
* Notes: 

* Time Complexity: NA
*******************************************************************************/
bit_array_ty BitArraySetAll(bit_array_ty data)
{
	UNUSED(data);
	
	return ~(bit_array_ty)0;
}


/******************************************************************************
* Function Description: sets the values of all bits of the array to 0	       
* Arguments: - data bit_array_ty.
* Return value: - bit_array_ty
* Notes: 

* Time Complexity: NA
*******************************************************************************/
bit_array_ty BitArrayResetAll(bit_array_ty data)
{
	UNUSED(data);
	
	return (bit_array_ty)0;
}


/******************************************************************************
* Function Description: returns the pointer to the bit-array bits converted 
  to 0/1 string.      
* Arguments: data - bit_array_ty, dest - pointer to the dest string.
* Return value: pointer to the converted string.
* Notes: dest needs to be able to hold word-long string.

* Time Complexity: NA
*******************************************************************************/
char *BitArrayToString(bit_array_ty data, char *dest)
{	
	bit_array_ty mask = 0x1lu;
	char *dest_start = dest;
	
	assert(dest);

	for (mask <<= (BIT_ARRAY_SIZE - 1) ; mask > 0; mask >>= 1)
	{
		*dest = ((data & mask) >= 1 ? '1' : '0');
		++dest;
	}
	*dest = '\0';
	
	return dest_start;
}


/******************************************************************************
* Function Description: sets the value of a bit on the index @idx to 1      
* Arguments: data - bit_array_ty, idx - index of the bit to be set to 1.
* Return value: bit_array_ty
* Notes: undefined if the argument is out of range.

* Time Complexity: NA
*******************************************************************************/
bit_array_ty BitArraySetOn(bit_array_ty data, const unsigned int idx)
{	
	
	assert(idx < BIT_ARRAY_SIZE);
	
	return ((1lu << idx) | data);
}

/******************************************************************************
* Function Description: sets the value of a bit on the index @idx to 0	       
* Arguments: data - bit_array_ty, idx - the index of the bit to be set to 0
* Return value: bit_array_ty.
* Notes: undefined if the argument is out of range.

* Time Complexity: NA
*******************************************************************************/
bit_array_ty BitArraySetOff(bit_array_ty data, const unsigned int idx)
{	
	bit_array_ty mask = 1lu << idx;
	
	assert(idx < BIT_ARRAY_SIZE);
	
	return (mask | data) ^ mask;
}


/******************************************************************************
* Function Description: sets the value of a bit on the index @idx to @val	    
* Arguments: data - bit_array_ty, idx - index of the bit to be set, 
  val - value to set the bit to.
* Return value: bit_array_ty.
* Notes: undefined if the argument is out of range.


* Time Complexity: NA
*******************************************************************************/
bit_array_ty BitArraySetBit(bit_array_ty data, const unsigned int idx, 
														const unsigned int val)
{
	unsigned int val1 = val;
	bit_array_ty mask_val = val1 << idx;
	bit_array_ty mask = 1lu << idx;
	
	assert(idx < BIT_ARRAY_SIZE);
	assert(val == 0 || val == 1);
	
	return ((data & ~mask) | mask_val); /* (data & ~mask) sets the bit to zero*/
}


/******************************************************************************
* Function Description: returns the value of the bit on the index @idx       
* Arguments: data - bit_array_ty, idx - the index of the bit who's value is 
to be returned
* Return value: value of the chosen bit.
* Notes: undefined if idx is out of range.

* Time Complexity: NA
*******************************************************************************/
int BitArrayGetVal(bit_array_ty data, const unsigned int idx)
{
	assert(idx < BIT_ARRAY_SIZE);
	
	return ((data & (1lu << idx)) >> idx);
}


/******************************************************************************
* Function Description: flips the value of the bit on the index @idx       
* Arguments: data - bit_array_ty, idx - the index of the bit ot be flipped.
* Return value: bit_array_ty.
* Notes: undefined if idx is out of range.

* Time Complexity: NA
*******************************************************************************/
bit_array_ty BitArrayFlip(bit_array_ty data, const unsigned int idx)
{
	assert(idx < BIT_ARRAY_SIZE);
	assert(idx < BIT_ARRAY_SIZE);
	
	return (data ^ (1lu << idx));
}


/******************************************************************************
* Function Description: returns the mirror of the current bit-array state       
* Arguments: data - data by value.
* Return value: bit_array_ty  holding the mirrord bits
* Notes: 

* Time Complexity: NA
*******************************************************************************/
bit_array_ty BitArrayMirror(bit_array_ty data)
{
	data = ((data >> 1lu) & 0x5555555555555555lu) | 
				  						 ((data & 0x5555555555555555lu) << 1lu);
    data = ((data >> 2lu) & 0x3333333333333333lu) | 
    			 					     ((data & 0x3333333333333333lu) << 2lu);
    data = ((data >> 4lu) & 0x0f0f0f0f0f0f0f0flu) | 
    						   		     ((data & 0x0f0f0f0f0f0f0f0flu) << 4lu);
    data = ((data >> 8lu) & 0x00ff00ff00ff00fflu) | 
    		   						     ((data & 0x00ff00ff00ff00fflu) << 8lu);
    data = ((data >> 16lu) & 0x0000ffff0000fffflu) | 
    			  				   	    ((data & 0x0000ffff0000fffflu) << 16lu);
    data = ((data >> 32lu) & 0x00000000fffffffflu) | 
    									((data & 0x00000000fffffffflu) << 32lu);
    return data;
}
 /* reverse bit array bits using lookup table */
bit_array_ty BitArrayMirror_LUT(bit_array_ty data)
{
	/* lookup table to store the reverse of each index of the table */
	static unsigned int lut[256] = { REVERSE_BITS };
	bit_array_ty reversed = 0;
 
 
    /* split, reverse, and rearrange each chunk */
    reversed = ((bit_array_ty)lut[data & 0xff] << 56) | /*move first byte to be the last, reversed*/
   		((bit_array_ty)lut[(data >> 8) & 0xff]) << 48 |         
        ((bit_array_ty)lut[(data >> 16) & 0xff]) << 40 |        
        ((bit_array_ty)lut[(data >> 24) & 0xff]) << 32 |               
        ((bit_array_ty)lut[(data >> 32) & 0xff]) << 24 |
 		((bit_array_ty)lut[(data >> 40) & 0xff]) << 16 |
 		((bit_array_ty)lut[(data >> 48) & 0xff]) << 8 |
 		((bit_array_ty)lut[(data >> 56) & 0xff]); /*last byte tirns to be the first,reversed bits */
    return reversed;

}

/******************************************************************************
* Function Description: rotates the contents of the bit-array right 
  @num_rot times       
* Arguments: data - bit_array_ty, num_rot - number of times to do the rotation.
* Return value: bit_array_ty
* Notes: 

* Time Complexity: NA
*******************************************************************************/
bit_array_ty BitArrayRotR(bit_array_ty data, const unsigned int num_rot)
{
	bit_array_ty mask = 1lu  ;
	bit_array_ty temp = 0;
	int new_rot = num_rot % BIT_ARRAY_SIZE;
		
	/* create mask for num_rot rightmous first bits */
	 mask = (1lu << new_rot)-1; 
	
	temp = data & mask;
	return ((data >> new_rot) | (temp << (BIT_ARRAY_SIZE - new_rot)));
}


/******************************************************************************
* Function Description: rotates the contents of the bit-array left 
  @num_rot times.       
* Arguments: data - bit_array_ty, num_rot - number of times to do the rotation.
* Return value: bit_array_ty
* Notes: 

* Time Complexity: NA
*******************************************************************************/
bit_array_ty BitArrayRotL(bit_array_ty data, const unsigned int num_rot)
{
	return BitArrayRotR(data, BIT_ARRAY_SIZE - num_rot);
}


/******************************************************************************
* Function Description: returns number of set bits in the array
* Arguments: - data - bit_array_ty.
* Return value: number of set bits in the array
* Notes: 

* Time Complexity: NA
*******************************************************************************/
unsigned int BitArrayCountOn(bit_array_ty data)
{
	int count = 0;
	
	/* (data - 1) sets all the tailing zeros to 1 and set first 1 to 0 and */
	while(data)
	{
		data &= (data - 1);
		++count;
	}
	return count;
}

unsigned int BitArrayCountOn_LUT(bit_array_ty data)
{
	/* Lookup table to store the total number of bits set for each index 
     in the table. The macro `COUNT_BITS` generates the table. */
	static unsigned int lut[256] = { COUNT_BITS };
	int count = 0;
	

		/* Break the bit_array into 8 bytes (8 bits each) */
    	count = lut[data & 0xff] +      /* consider the first 8 bits */
        lut[(data >> 8) & 0xff] +       /* consider the next 8 bits */
        lut[(data >> 16) & 0xff] +      
        lut[(data >> 24) & 0xff] +       
        lut[(data >> 32) & 0xff] +
 		lut[(data >> 40) & 0xff] +
 		lut[(data >> 48) & 0xff] +
 		lut[(data >> 56) & 0xff];		/* consider last 8 bits */
 		
    return count;
}

/******************************************************************************
* Function Description: returns number of unset bits in the array       
* Arguments: - data - bit_array_ty.
* Return value: number of unset bits in the array
* Notes: 

* Time Complexity: NA
*******************************************************************************/
unsigned int BitArrayCountOff(bit_array_ty data)
{
	return BIT_ARRAY_SIZE - BitArrayCountOn(data);
}





