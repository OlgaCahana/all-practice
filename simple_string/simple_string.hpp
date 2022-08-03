#ifndef __SIMPLE_STRING__
#define __SIMPLE_STRING__

#include <cstddef>
#include <iostream>	


namespace ilrd
{

class String;   

bool operator==(const String& l_, const String& r_);
bool operator==(const char *l_, const String& r_);
bool operator==(const String& l_, const char *r_);

bool operator< (const String& r_, const String& l_);
bool operator> (const String& r_, const String& l_);


std::ostream& operator<<(std::ostream& os_, const String& o_);



class String
{
    public:
    
         String(const char * str_ = "");  // Ctor taking string literal as parameter
        ~String();                      //Dtor
        String(const String &other_);   // Copy Ctor
        String& operator = (const String &other_); // assignment operator
        char operator[](int); //operator []
        


        std :: size_t Length() const;
        const char *Cstr() const; // return m_cstr
        //friend bool operator==(const char *l_, const String& r_);
        //friend std::ostream& operator<<(std::ostream& os_, const String& o_);


    private:
        char *m_cstr;
    
};



}
#endif // __SIMPLE_STRING__