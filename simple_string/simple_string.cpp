#include <cstring>
#include <iostream>

#include "simple_string.hpp"

using namespace std;
using namespace ilrd;

//*********************Helpers**********************************
// returns pointer to string holding str_
static char *CreateStrImp(const char * str_);



//*******************Class API IMP *****************************

//Ctor taking string literal as parameter
String::String(const char *str_):m_cstr(CreateStrImp(str_))
{}

//Dtor
String::~String()
{
    delete[] m_cstr;
    m_cstr = 0; //!do not forget! important since the dtor can be called multiple times
}              

// Copy Ctor
String::String(const String &other_):m_cstr(CreateStrImp(other_.m_cstr))
{} 

// assignment operator
String& String::operator= (const String &other_)
{
// Handles assignment to self!!!!!!!!!!!!!!
    char *new_str = CreateStrImp(other_.m_cstr);
    delete[] m_cstr;
    m_cstr = new_str;

    return *this;
} 

char String::operator[](int i) //operator []
{
    return m_cstr[i];
}

size_t String::Length() const
{
    return strlen(m_cstr);
}

const char *String::Cstr() const
{
    return m_cstr;
}


/* Global operators IMP */

bool ilrd::operator==(const String& l_, const String& r_)
{
    return !strcmp(l_.Cstr(), r_.Cstr());
}

bool ilrd::operator==(const String& l_, const char *r_)
{
    return !strcmp(l_.Cstr(), r_);
}
bool ilrd::operator==(const char *l_, const String& r_)
{
    return !strcmp(l_, r_.Cstr());
}

bool ilrd::operator< (const String& l_, const String& r_)
{
    if(strcmp(l_.Cstr(), r_.Cstr()) < 0)
    {
        return true;
    }
    return false;
}

bool ilrd::operator> (const String& l_, const String& r_)
{
    if(strcmp(l_.Cstr(), r_.Cstr()) > 0)
    {
        return true;
    }
    return false;
}

std::ostream& ilrd::operator<<(std::ostream& os_, const String& o_)
{
    return os_ << o_.Cstr();
}


//*********************Helpers IMP ********************************

static char *CreateStrImp(const char * str_)
{
   // assert(str_);
    //int len = strlen(str_) + 1;
    //char *newstr = new char[len];

    //memcpy(newstr, str_, len);
    char *newstr = new char[strlen(str_) + 1];
    strcpy(newstr, str_);
    return newstr;
}