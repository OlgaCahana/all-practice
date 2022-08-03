#include <cstring>
#include <iostream>

#include "complex.hpp"

using namespace std;
using namespace ilrd;


/**************************Helpers**********************************/



/************************Class API IMP *****************************/
// methods
void Complex::SetRe(double re_)
{
    m_re = re_;
}

void Complex::SetIm(double im_)
{
    m_im = im_;
}

double Complex::GetRe() const
{
    return m_re;
}

double Complex::GetIm() const
{
    return m_im;
}

//assignment operators
Complex& Complex::operator+=(const Complex& op2_)
{
    *this = *this + op2_;
    return *this;
}

Complex& Complex::operator-=(const Complex& op2_)
{
    *this = *this - op2_;
    return *this;   
}

Complex& Complex::operator*=(const Complex& op2_)
{
    *this = *this * op2_;
    return *this;
}

Complex& Complex::operator/=(const Complex& op2_)
{
    *this = *this / op2_;
    return *this;
}


/******************** Global operators IMP *************************/
// math operators
Complex ilrd::operator+(const Complex& op1_, const Complex& op2_)
{
    Complex ret(op1_.GetRe() + op2_.GetRe(), op1_.GetIm() + op2_.GetIm());
    return ret;
}

Complex ilrd::operator-(const Complex& op1_, const Complex& op2_)
{
    Complex ret(op1_.GetRe() - op2_.GetRe(), op1_.GetIm() - op2_.GetIm());
    return ret;
    
}

Complex ilrd::operator*(const Complex& op1_, const Complex& op2_)
{
    Complex ret;

    ret.SetRe(op1_.GetRe() * op2_.GetRe() - op1_.GetIm() * op2_.GetIm());
    ret.SetIm(op1_.GetRe() * op2_.GetIm() + op1_.GetIm() * op2_.GetRe());

    return ret;
}

Complex ilrd::operator/(const Complex& op1_, const Complex& op2_)
{
    Complex ret;

    double denom = op2_.GetRe() * op2_.GetRe() + op2_.GetIm() * op2_.GetIm();
    ret.SetRe((op1_.GetRe() * op2_.GetRe() + op1_.GetIm() * op2_.GetIm()) / denom);
    ret.SetIm((op1_.GetIm() * op2_.GetRe() - op1_.GetRe() * op2_.GetIm()) / denom);

    return ret;
}


// cmp operators
bool ilrd::operator==(const Complex& op1_, const Complex& op2_)
{
    return (op1_.GetRe() == op2_.GetRe()) && (op1_.GetIm() == op2_.GetIm());
}

bool ilrd::operator!=(const Complex& op1_, const Complex& op2_)
{
    return !((op1_.GetRe() == op2_.GetRe()) && (op1_.GetIm() == op2_.GetIm()));
}

// io operators
std::ostream& ilrd::operator<<(std::ostream& os_, const Complex& op2_)
{
    return os_ << op2_.GetRe() << "+" << op2_.GetIm() << "i" << endl;
}

std::istream& ilrd::operator>>(std::istream& is_, Complex& op2_)
{
    double r;
    double im;

    cout << "enter: real imaginary" << endl;
    is_ >> r >> im;

    op2_.SetRe(r);
    op2_.SetIm(im);

    return is_; 
}


/************************Helpers IMP ********************************/

