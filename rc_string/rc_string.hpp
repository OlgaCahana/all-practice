#ifndef __ILRD_HRD22_RC_STRING_HPP__
#define __ILRD_HRD22_RC_STRING_HPP__

#include <cstddef>
#include <iostream>	
#include "utils.h"


namespace ilrd
{

class RCString;   

bool operator==(const RCString& r_, const RCString& l_) NOEXCEPT;
bool operator>(const RCString& r_, const RCString& l_) NOEXCEPT;
bool operator<(const RCString& r_, const RCString& l_) NOEXCEPT;

std::ostream& operator<<(std::ostream& os_, const RCString& obj_);
std::istream& operator>>(std::istream& is_, RCString& obj_);



class RCString
{
    private:
        class CharProxy;

    public:
    
        RCString(const char str_[] = ""); //non-explicit on purpose
        ~RCString() NOEXCEPT;                      //Dtor
        RCString(const RCString& other_);   // Copy Ctor
        RCString& operator=(const RCString& other_); // assignment operator
        char operator[](std::size_t idx_) const;
        CharProxy operator[](std::size_t idx_); //operator []
        DEBUG_ONLY( size_t DBG_GetRefCount() const)
        
        std :: size_t Length() const;
        const char *Cstr() const; // return m_cstr

    private:
        char *m_cstr;
        std::size_t *m_cntr;
        //friend std::istream& operator>>(std::istream& is_, RCString& obj_) ;
        static char *AllocNCopyIMP(const char src_[]) throw(std::bad_alloc);
        void Unshare();



};

class RCString::CharProxy
{
    public:
        //generated Copy Ctor
        explicit CharProxy(RCString& rcstr_, size_t idx_ );
        operator char() const;
        char *operator&() const; 
        char& operator=(char ch_) const; 
        char& operator=(const CharProxy& other_) const;

    private:       
        RCString& m_prxy_rcs;
        const size_t m_idx;
};


}//namespace ilrd
#endif /* __ILRD_HRD22_RC_STRING_HPP__ */