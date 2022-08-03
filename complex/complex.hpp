#ifndef __ILRD_COMPLEX__
#define __ILRD_COMPLEX__

#include <cstddef>
#include <iostream>	


namespace ilrd
{

class Complex;

// math operators
Complex operator+(const Complex& op1_, const Complex& op2_);
Complex operator-(const Complex& op1_, const Complex& op2_);
Complex operator*(const Complex& op1_, const Complex& op2_);
Complex operator/(const Complex& op1_, const Complex& op2_);


// cmp operators
bool operator==(const Complex& op1_, const Complex& op2_);
bool operator!=(const Complex& op1_, const Complex& op2_);

// io operators
std::ostream& operator<<(std::ostream& os_, const Complex& op2_);
std::istream& operator>>(std::istream& is_,   Complex& op2_);


class Complex
{
    // using generated cctor, dtor and assignment
    public:
        Complex(double re_ = 0.0, double im_ = 0.0); //non explicit to allow casting

        // methods
        void SetRe(double re_);
        void SetIm(double im_);
        double GetRe() const;
        double GetIm() const;

        //assignment operators
        Complex& operator+=(const Complex& op2_);
        Complex& operator-=(const Complex& op2_);
        Complex& operator*=(const Complex& op2_);
        Complex& operator/=(const Complex& op2_);


    private:
        double m_re;
        double m_im;
};


inline Complex::Complex(double re_, double im_): m_re(re_), m_im(im_)
{}



}
#endif // __ILRD_COMPLEX__