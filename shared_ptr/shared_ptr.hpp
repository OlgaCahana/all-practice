/*******************************************************************************
*	Written by:		Olga Danielle Cahana									   *
*	Date:			26/5/2022												   *
*	Reviewed by:    Shulamit
*   Description:    SharedPtr header
*   Versions:	    1.0 before review						    					 	   *
*																			   *
*******************************************************************************/


#ifndef ILRD_HRD22_BITSET_HPP
#define ILRD_HRD22_BITSET_HPP

#include <iostream> // ostream
#include <cassert> // assert


#include "utils.h"

namespace hrd22
{

template<typename T>
class SharedPtr
{
    public:
        explicit SharedPtr(T* ptr = 0); //ctor
        ~SharedPtr() NOEXCEPT; //dtor
        SharedPtr(const SharedPtr& other); //cctor
        //this is a conversion ctor, not copy ctor, since its different type
        //Upcast cctor
        template<typename D>
        SharedPtr(const SharedPtr<D>& other); //overloading cctor for derived


        T& operator *() const;
        T* operator->() const;
       // template<typename D>
        SharedPtr<T>& operator=(const SharedPtr<T>& other);
        bool operator==(const SharedPtr& other) const;
        bool operator!=(const SharedPtr& other) const;
        bool operator!() const;

        T* Get() const;
       // std::size_t* GetRC() const;
    protected:

    private:
        template<typename D>
        friend class SharedPtr;
        T* m_ptr;
        std::size_t* m_rc;
};

//ctor - not good, since if new failes here, the m_ptr will not be freed
// template<typename T>
// SharedPtr<T>::SharedPtr(T* ptr)
// :m_ptr(ptr), m_rc(new std::size_t(1)){}

//ctor - use try-catch to solve the above issue
template<typename T>
SharedPtr<T>::SharedPtr(T* ptr)
:m_ptr(ptr)
{
    try
    {
         m_rc = new std::size_t(1);
    }
    catch(const std::bad_alloc& e)
    {
        std::cerr << e.what() << '\n';
        delete m_ptr;
        throw;
    }   
}

//copy ctor
template<typename T>
SharedPtr<T>::SharedPtr(const SharedPtr& other)
:m_ptr(other.m_ptr), m_rc(other.m_rc)
{
    assert(other.m_ptr);
    assert(other.m_rc);
    ++*m_rc;
}

//copy ctor
template<typename T>
template<typename D>
SharedPtr<T>::SharedPtr(const SharedPtr<D>& other)
:m_ptr(other.m_ptr), m_rc(other.m_rc)
{
    assert(other.m_ptr);
    assert(other.m_rc);
    ++*m_rc;
}

//dtor
template<typename T>
SharedPtr<T>::~SharedPtr() NOEXCEPT
{
    // when Dtor is called on already destructed object
    if(!m_ptr)
    {
        delete m_rc;
        return;
    }

    --*m_rc;

    // if this was the last reference to m_ptr
    if(*m_rc == 0)
    {
        delete m_ptr;
        delete m_rc;
    } 

    m_ptr = 0;
    m_rc = 0;

}

//copy assignment
template<typename T>
//template<typename D>
//TODO: can be implemented with copy & swap
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& other)
{
    assert(other.m_rc);
    assert(other.Get());

    //increment other counter
    ++*(other.m_rc);

    // decrement *this counter
    --*m_rc;
    if(*m_rc == 0)
    {
        delete m_ptr;
        delete m_rc;
    }

    //make *this point to the other m_ptr and counter
    m_ptr = other.Get();
    m_rc = other.m_rc;

    return *this;

}


//operator *
template<typename T>
T& SharedPtr<T>::operator*() const
{
    return *m_ptr;
}

//operator ->
template<typename T>
T* SharedPtr<T>::operator->() const
{
    return m_ptr;
}

template<typename T>
bool SharedPtr<T>::operator==(const SharedPtr& other) const
{
    return m_ptr == other.m_ptr;
}

template<typename T>
bool SharedPtr<T>::operator!=(const SharedPtr& other) const
{
    return m_ptr != other.m_ptr;
}

template<typename T>
bool SharedPtr<T>::operator!() const
{
    return !m_ptr;
}

template<typename T>
T* SharedPtr<T>::Get() const
{
    return m_ptr;
} 

// template<typename T>
// std::size_t* SharedPtr<T>::GetRC() const
// {
//     return m_rc;
// } 


}
#endif //ILRD_HRD22_BITSET_HPP