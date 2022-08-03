/*******************************************************************************
*	Written by:		Olga Danielle Cahana									   *
*	Date:			10/5/2022												   *
*	Reviewed by:    Tal Cohen
*   Description:    Circle class implementation
*   Versions:	    						    					 	   *
*																			   *
*******************************************************************************/
#ifndef ILRD_HRD22_CIRCLE_H
#define ILRD_HRD22_CIRCLE_H

#include  "shape.hpp"  /*  */ 
namespace hrd22
{
class Circle : public Shape
{
public:
    explicit Circle(const ilrd::Point& center, double radius = 2, double angle = 0, COLORS = COLOR_WHITE);
    // using generated Dtor
    // CCtor and assignment blocked
    
    virtual void Draw() const;
    Circle* Clone() const;

private:
    double m_radius;
    Circle(const Circle&);
};



}// namespace hrd22
#endif /* ILRD_HRD22_CIRCLE_H */