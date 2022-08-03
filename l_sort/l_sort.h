/*******************************************************************************
*	Written by:		Olga Danielle Cahana									   *
*	Date:			15/2/2022												   *
*	Reviewed by:							    					 	   *
*																			   *
*******************************************************************************/

#ifndef __L_SORT_H__
#define __L_SORT_H__

#include <stddef.h> /*size_t*/

#include <stddef.h>

/* parameters: 
 * src[] input array of items to be sorted  
 * dest[] to hold the sorted output
 * size of src and dest arrays, 
 * digit_lsb_idx the index of lsb bit relevant to sorting, from right to left 
 * num_bits_in_digit the digit width in bits 
 * histogram[] temporary working storage 
 * num_significant_bits number of bits relevant to sorting, starting from digit_lsb_idx */

void CountSort( const int src[],
                int dest[],
                size_t size, 
                int digit_lsb_idx, 
                int num_bits_in_digit, 
                size_t histogram[]);

void RadixSort( int src[],
                int dest[],
                size_t size,
                int lsb_idx,
                int num_bits_in_digit,
                int num_significant_bits, 
                size_t histogram[]);


#endif /*__L_SORT_H__*/

