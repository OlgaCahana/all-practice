/*******************************************************************************
*	Written by:		Olga Danielle Cahana									   *
*	Date:			3/2/2022												   *
*	Reviewed by:    Tal Cohen
*   Description:    Circle class implementation
*   Versions:	    						    					 	   *
*																			   *
*******************************************************************************/
#ifndef ILRD_HRD22_RECTANGLE_H
#define ILRD_HRD22_RECTANGLE_H


#include  "shape.hpp"  

namespace hrd22
{

class Rectangle : public Shape
{
public:
    explicit Rectangle(const ilrd::Point& center, double base = 10, double height = 5, 
                        double angle = 0, COLORS = COLOR_YELLOW);
    // using generated Dtor
    // CCtor and assignment blocked

    virtual void Draw() const;
    virtual Rectangle* Clone() const;

private:
    double m_base;
    double m_height;
    Rectangle(const Rectangle&);
};


}// namespace ilrd

#endif /* ILRD_HRD22_RECTANGLE_H */