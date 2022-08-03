/*******************************************************************************
*	Written by:		Olga Danielle Cahana									   *
*	Date:			3/2/2022												   *
*	Reviewed by:    Tal Cohen
*   Description:    Circle class implementation
*   Versions:	    						    					 	   *
*																			   *
*******************************************************************************/

#include <cassert>
#include <iostream>

#include "circle.hpp"
#include  "shape.hpp"  /*  */ 
#include "utils.h"

using namespace std;
using namespace hrd22;


/*							Members Implementaion			     				   */
/*******************************************************************************/

namespace hrd22
{
Circle::Circle(const ilrd::Point& center_, double radius_, double angle_, COLORS color_):
Shape(center_, angle_, color_), m_radius(radius_)
{
    DEBUG_ONLY(cout << "Circle Ctor" << endl);
}

void Circle::Draw() const
{
    DrawCircle(GetColor(), GetCenter().GetX(), GetCenter().GetY(), m_radius);
}

Circle::Circle(const Circle& other_): Shape(other_.GetCenter(), other_.GetAngle(), other_.GetColor()),
m_radius(other_.m_radius)
{

}


Circle* Circle::Clone() const
{
    return new Circle(*this);
}

}//namespace hrd22





