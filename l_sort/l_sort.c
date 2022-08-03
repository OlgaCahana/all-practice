/*******************************************************************************
*	Written by:		Olga Danielle Cahana									   *
*	Date:			15/2/2022												   *
*	Reviewed by:	    						    					 	   *
*																			   *
*******************************************************************************/
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

#include "l_sort.h"

/******************************Helpers*****************************************/
static int ExtractDigitIMP(int num_, int digit_lsb_idx_, int num_bits_in_digit);
void InitArr1(size_t *arr, size_t size);

/**************************Implementation**************************************/


void CountSort( const int src_[],
                int dest_[],
                size_t size_, 
                int digit_lsb_idx_, 
                int num_bits_in_digit_, 
                size_t histogram_[])
{
    const int *src_curr = src_; /* curr pts to scan src */
    const int *src_last = src_ + size_ - 1; /* last valid element */

    size_t *hist_curr = histogram_ + 1; /* ptr to scan the histogram */
    size_t hist_size = 1lu << num_bits_in_digit_; /* 2^num_bits_in_digit */
    size_t *hist_end = histogram_ + hist_size; /* first invalid  after hist */

    int rel_digit = 0; /* hold the digit to be sorted by */

    assert(src_);
    assert(dest_);
    assert(histogram_);
    assert(digit_lsb_idx_ >= 0);
    assert(num_bits_in_digit_ > 0);
    assert(size_ > 0);
    
    /* initialize histogram to 0 */
    InitArr1(histogram_, hist_size);

    /* foreach number in src */
    while(src_curr <= src_last)
    {   
        /* extract the relevant digit from this number */
        rel_digit = ExtractDigitIMP(*src_curr, digit_lsb_idx_, num_bits_in_digit_);

        /* increment the extracted digit count in the histogram
            * (the rel_digit is used as histogram index) */
        ++histogram_[rel_digit];

        /* promote src_curr to the next value */
        ++src_curr;
    }
   
    /* foreach index in histogram */
    while(hist_curr < hist_end)
    {   
        /* sum curr value with his prev value */
        *hist_curr += *(hist_curr - 1);
        ++hist_curr;

    }
    
    /* init src-curr back to src_ start */
    src_curr = src_;
  
    /* foreach num in src, starting from the end */
    while( src_curr <= src_last)
    {
        /* extract the relevant digit from this number */
        rel_digit = ExtractDigitIMP(*src_last, digit_lsb_idx_, num_bits_in_digit_);

        /* place the at correct index in dest, (dest index is histogram[extr_dig] - 1)
         * copy backwards to preserve stability(from src right to left ) */
        *(dest_ + *(histogram_ + rel_digit) - 1) = *src_last;
        /* dest[histogram[rel_digit] - 1] = *src_last */

        /* decrement histogram count for this digit value, decrenment scr_last */
        --*(histogram_ + rel_digit);
        --src_last;
    }    
}

void RadixSort( int src_[],
                int dest_[],
                size_t size_,
                int lsb_idx_,
                int num_bits_in_digit_,
                int num_significant_bits_, 
                size_t histogram_[])
{
    int last_digit = lsb_idx_ + num_significant_bits_ - 1;

    assert(src_);
    assert(dest_);
    assert(histogram_);
    assert(lsb_idx_ >= 0);
    assert(num_bits_in_digit_ > 0);
    /* num_significant_bits should be between 0 to num of bits in int */
    assert(num_significant_bits_ > 0 &&
            (__CHAR_BIT__ * sizeof(int)) >= num_significant_bits_);
    assert(size_ > 0);

    /* foreach digit in a number */
    while(lsb_idx_ <= last_digit)
    {
        /* sort values in src by this digit */
        CountSort(src_, dest_, size_, lsb_idx_, num_bits_in_digit_, histogram_);

        /* copy the temporary sorted output back to src */
        memcpy(src_, dest_, size_ * sizeof(int));

        /* promote lsb_idx to the next digit to be sorted by */
        lsb_idx_ += num_bits_in_digit_;
    }
}   

/********************************Helpers********************************************/
static int ExtractDigitIMP(int num_, int digit_lsb_idx_, int num_bits_in_digit)
{   
    /* create mask with num_bits_in_digit 1's (from lsb)*/
    int mask = ~(~0 << num_bits_in_digit);

    return((num_ >> digit_lsb_idx_) & mask);
}

void InitArr1(size_t *arr, size_t size)
{
	size_t i = 0;

	for(i=0; i < size; ++i)
	{
		arr[i] = 0;
	}
}