/*******************************************************************************
*	Written by:		Olga Danielle Cahana									   *
*	Date:			22/5/2022												   *
*	Reviewed by:    Maoz
*   Description:    Bitset template header
*   Versions:	    1.0 before rview						    					 	   *
*																			   *
*******************************************************************************/


#ifndef ILRD_HRD22_BITSET_HPP
#define ILRD_HRD22_BITSET_HPP

#include <iostream> // ostream
#include <climits> // CHAR_BIT
#include <cstddef> // size_t
#include <cassert> // assert
#include <vector>
#include <algorithm>
#include <functional>

static const int WORDBIT = sizeof(std::size_t) * __CHAR_BIT__;

namespace hrd22
{

template<std::size_t Size>
class BitSet;

template<std::size_t Size>
std::ostream& operator<<(std::ostream& os_ ,const BitSet<Size>& bitset_);


template<std::size_t Size>
class BitSet
{
    
private:
    class BitProxy;
    
public:
    explicit BitSet();

    //Using generated CCTOR,DTOR and copy assignment

    BitSet& operator&=(const BitSet& other_);
    BitSet& operator|=(const BitSet& other_);
    BitSet& operator^=(const BitSet& other_);
    BitSet& operator<<=(const BitSet& other_); //opt

    bool operator==(const BitSet& other_) const;

    BitProxy operator[](std::size_t idx_);
    bool operator[](std::size_t idx_) const;

    std::size_t CountSetBits() const;

private:
    std::vector<std::size_t> m_bitarray;

    void SetBit(bool value_, std::size_t idx_);
    bool GetBit(std::size_t idx_) const;
    friend std::ostream& operator<<<Size>(std::ostream& os_, const BitSet& bitset_);

};

template<std::size_t Size>
class BitSet<Size>::BitProxy
{
public:
    explicit BitProxy(BitSet& bitset_, std::size_t idx_);

    // Auto generated Copy assignment CCtor and Dtor

    operator bool() const; //convert bit to bool

    BitProxy& operator=(bool value_);
    BitProxy& operator=(const BitProxy& other_);

private:
    BitSet& m_set;
    std::size_t m_idx;
};


/********************************Implementation**********************************/
//helper
static std::size_t BitArrayCountOn(std::size_t data)
{
	std::size_t count = 0;
	
	/* (data - 1) sets all the tailing zeros to 1 and set first 1 to 0 and */
	while(data)
	{
		data &= (data - 1);
		++count;
	}
	return count;
}

/**********************************BitProxy**************************************/
//ctor
template<std::size_t Size>
BitSet<Size>::BitProxy::BitProxy(BitSet& bitset_, std::size_t idx_)
: m_set(bitset_), m_idx(idx_) {}

//operator bool()
template<std::size_t Size>
BitSet<Size>::BitProxy::operator bool() const
{
    return m_set.GetBit(m_idx);
}

//operator=(bool) 
template<std::size_t Size>
typename BitSet<Size>::BitProxy& BitSet<Size>::BitProxy::operator=(bool value_)
{
    m_set.SetBit(value_, m_idx);
    return *this;
}

//operator=(BitProxy&)
template<std::size_t Size>
typename BitSet<Size>::BitProxy& BitSet<Size>::BitProxy::operator=(const BitProxy& other_)
{
    m_set.SetBit(other_.m_set.GetBit(other_.m_idx), m_idx);
    return *this;
}



/**************************Functors***********************************************/
class BinaryAnd : public std::binary_function<std::size_t, std::size_t, std::size_t>
{
    public:
    std::size_t operator() (std::size_t op1, std::size_t op2)
    {
        return op1 & op2;
    }
};

std::size_t BinaryOr(std::size_t op1, std::size_t op2)
{
    return op1 | op2;
} 

std::size_t BinaryXor(std::size_t op1, std::size_t op2)
{
    return op1 ^ op2;
} 

class CoundSetBitsF : public std::unary_function<std::size_t, std::size_t>
{
    public:
    CoundSetBitsF(std::size_t& num):m_setCtr(num){}
    void operator() (std::size_t elem)
    {
        m_setCtr += BitArrayCountOn(elem);
    }

    private:
    std::size_t& m_setCtr;
};

/**********************BitSet Methods********************************************/
//ctor
template<std::size_t Size>
BitSet<Size>::BitSet()
:m_bitarray(Size / WORDBIT + 
                !!(Size % WORDBIT), 0 ){}

//operator&=
template<std::size_t Size>
BitSet<Size>& BitSet<Size>::operator&=(const BitSet<Size>& other_)
{
    transform(m_bitarray.begin(), m_bitarray.end(), other_.m_bitarray.begin(), 
                m_bitarray.begin(), BinaryAnd());
    return *this;
}

//operator|=
template<std::size_t Size>
BitSet<Size>& BitSet<Size>::operator|=(const BitSet<Size>& other_)
{
    transform(m_bitarray.begin(), m_bitarray.end(), other_.m_bitarray.begin(), 
                m_bitarray.begin(), BinaryOr);
    return *this;
}

//operator^=
template<std::size_t Size>
BitSet<Size>& BitSet<Size>::operator^=(const BitSet<Size>& other_)
{
    transform(m_bitarray.begin(), m_bitarray.end(), other_.m_bitarray.begin(), 
                m_bitarray.begin(), BinaryXor);
    return *this;
}

//operator==
template<std::size_t Size>
bool BitSet<Size>::operator==(const BitSet<Size>& other_) const
{
    return equal(m_bitarray.begin(), m_bitarray.end(), other_.m_bitarray.begin());
}

//operator [] - return type BitProxy
template<std::size_t Size>
typename BitSet<Size>::BitProxy BitSet<Size>::operator[](std::size_t idx_)
{
    assert(idx_ < Size);
    
    return BitSet<Size>::BitProxy(*this, idx_); 
}

//operator [] - return type bool
template<std::size_t Size>
bool BitSet<Size>::operator[](std::size_t idx_) const
{
    assert(idx_ < Size);

    return GetBit(idx_);
}

//SetBit
template<std::size_t Size>
void BitSet<Size>::SetBit(bool value_, std::size_t idx_)
{
    assert(idx_ < Size);
    std::size_t wordNum = idx_ / WORDBIT;
    int bitNum = idx_ % WORDBIT;

    std::size_t mask = 1LU << bitNum;
    std::size_t maskVal = std::size_t(value_) << bitNum;

    m_bitarray[wordNum] = ((m_bitarray[wordNum] & ~mask) | maskVal);

}

//GetBit
template<std::size_t Size>
bool BitSet<Size>::GetBit(std::size_t idx_) const
{
    assert(idx_ < Size);

    std::size_t wordNum = idx_ / WORDBIT;
    int bitNum = idx_ % WORDBIT;

    return !!(m_bitarray[wordNum] & (1LU << bitNum));

}

//Count set bits
template<std::size_t Size>
std::size_t BitSet<Size>::CountSetBits() const
{
    //count for size_t chunks
    std::size_t b_cntr = 0;
    std::for_each(m_bitarray.begin(), (m_bitarray.end() - 1), CoundSetBitsF(b_cntr));

    // count for remaining bits
    std::size_t idx = Size % WORDBIT;
    for(std::size_t i = Size - idx; i < Size; ++i)
    {
        b_cntr += GetBit(i);
    }
    return b_cntr;
}

//Friend: operator<<
template<std::size_t Size>
std::ostream& operator<<(std::ostream& os_ ,const BitSet<Size>& bitset_)
{
    for(int i = Size - 1; i >= 0; --i)
    {
       // os_ << bitset_[i];
       os_ << bitset_.GetBit(i);
    }
    return os_;
}


}
#endif //ILRD_HRD22_BITSET_HPP