/*
v1.0 2 ptrs using proxy 
*/

#include <cstring>
#include <iostream>
#include <cassert>

#include "rc_string.hpp"
#include "utils.h"

using namespace std;
using namespace ilrd;

const int BUFSIZE = 200;

//*********************Helpers**********************************
//int Is_Shared(const RCString&) const;


//*******************RCString Class API IMP *****************************

//Ctor taking string literal as parameter
RCString::RCString(const char *str_)
:m_cstr(AllocNCopyIMP(str_)),m_cntr(new size_t(1))
{
    DEBUG_ONLY(cout << "RCString Ctor" << endl);

}

//Dtor
RCString::~RCString() NOEXCEPT
{
    assert(*m_cntr > 0);
    assert(m_cstr);
    DEBUG_ONLY(cout << "RCString Dtor" << endl);

    // when Dtor is called on already destructed object
    if(!m_cstr)
    {
        return;
    }

    --*m_cntr;

    // if this was the last reference to m_cstr 
    if(*m_cntr == 0)
    {
        delete[] m_cstr;
        delete m_cntr;
    }

    m_cstr = 0; //!do not forget! important since the dtor can be called multiple times
 //   m_cntr = 0;
}              

// Copy Ctor
RCString::RCString(const RCString &other_):m_cstr(other_.m_cstr), m_cntr(other_.m_cntr)
{
    assert(other_.m_cstr);
    assert(*other_.m_cntr > 0);
    DEBUG_ONLY(cout << "RCString Copy Ctor" << endl);

    ++*m_cntr;
} 

// assignment operator
RCString& RCString::operator= (const RCString &other_)
{
    //Handle assignment to self

    assert(other_.m_cstr);
    assert(other_.m_cntr);

    //increment other counter
    ++*other_.m_cntr;

    // decrement *this counter
    --*m_cntr;
    // delete if this was the last reference to m_cstr 
    if(*m_cntr == 0)
    {
        delete[] m_cstr;
        delete m_cntr;
    }

    //make *this point to the other_ m_str and counter
    m_cstr = other_.m_cstr;
    m_cntr = other_.m_cntr;
    
    return *this;
} 

RCString::CharProxy RCString::operator[](size_t idx_) //operator []
{
    DEBUG_ONLY(cout << "non const operator[]" << endl);
    assert(idx_ < strlen(m_cstr));

    //if shared, unshare(make a copy)
    if(*m_cntr > 1)
    {
        --*m_cntr;
        m_cstr = AllocNCopyIMP(m_cstr);
        m_cntr = new size_t(1);
    }
    
    return CharProxy(*this, idx_);
}

 char RCString::operator[](size_t idx_) const //operator []
{
    DEBUG_ONLY(cout << "const operator[]" << endl);
    assert(idx_ < strlen(m_cstr));

    return m_cstr[idx_];
}

size_t RCString::Length() const
{
    return strlen(m_cstr);
}

const char *RCString::Cstr() const
{
    return m_cstr;
}


/* Global operators IMP */

bool ilrd::operator==(const RCString& l_, const RCString& r_) NOEXCEPT
{
    return !strcmp(l_.Cstr(), r_.Cstr());
}


bool ilrd::operator< (const RCString& l_, const RCString& r_) NOEXCEPT
{
    return strcmp(l_.Cstr(), r_.Cstr()) < 0;
}


bool ilrd::operator> (const RCString& l_, const RCString& r_) NOEXCEPT
{
    return strcmp(l_.Cstr(), r_.Cstr()) > 0;
}


std::ostream& ilrd::operator<<(std::ostream& os_, const RCString& o_) 
{
    return os_ << o_.Cstr();
}

std::istream& ilrd::operator>>(std::istream& is_, RCString& obj_) 
{
    assert(!is_.fail());
    char buffer[BUFSIZE];

    is_.get(buffer, BUFSIZE);

    obj_ = buffer;

    return is_;

}

/************************Char Proxy Imp*************************/
RCString::CharProxy::CharProxy(RCString& rcstr_, size_t idx_ ): m_prxy_rcs(rcstr_), m_idx(idx_)
{ }

RCString::CharProxy::operator char() const
{
    return m_prxy_rcs.m_cstr[m_idx];
}
char *RCString::CharProxy::operator&() const
{
    m_prxy_rcs.Unshare();
    return &m_prxy_rcs.m_cstr[m_idx];
}

// Q1: why const? how come it compiles?? ans:
char& RCString::CharProxy::operator=(char ch_) const
{
    m_prxy_rcs.Unshare();
    
    return  m_prxy_rcs.m_cstr[m_idx] = ch_;  
}

// Q1: why returns char& ? ans: conversion from proxy to char
char& RCString::CharProxy::operator=(const CharProxy& other_) const
{
    m_prxy_rcs.Unshare();
    return m_prxy_rcs.m_cstr[m_idx] = other_.m_prxy_rcs.m_cstr[other_.m_idx];
    
}


//*********************Helpers IMP ********************************

char *RCString::AllocNCopyIMP(const char str_[]) throw(std::bad_alloc)
{
    assert(str_);

    int len = strlen(str_) + 1;
    char *newstr = new char[len];

    memcpy(newstr, str_, len);

    return newstr;
}

void RCString::Unshare()
{
    if(*m_cntr > 1) //if shared
    {
        --*m_cntr;
        m_cstr = AllocNCopyIMP(m_cstr);
        m_cntr = new size_t(1);
    }
}

size_t RCString::DBG_GetRefCount() const
{
    return *m_cntr;
}
