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

#include "rectangle.hpp"
#include  "shape.hpp"  /*  */ 
#include "utils.h"

using namespace std;
using namespace hrd22;

namespace hrd22
{
Rectangle::Rectangle(const ilrd::Point& center_, double base_, double height_, double angle_, COLORS color_):
Shape(center_, angle_, color_), m_base(base_), m_height(height_)
{
    DEBUG_ONLY(cout << "Circle Ctor" << endl);
}
// using generated Dtor
// CCtor and assignment blocked

void Rectangle::Draw() const
{
    ilrd::Point center = GetCenter();

    ilrd::Point p1(center.GetX() - m_base/2,center.GetY() - m_height/2);
    ilrd::Point p2(center.GetX() - m_base/2,center.GetY() + m_height/2);
    ilrd::Point p3(center.GetX() + m_base/2,center.GetY() + m_height/2);
    ilrd::Point p4(center.GetX() + m_base/2,center.GetY() - m_height/2);

    p1.Revolve(center, GetAngle());
    p2.Revolve(center, GetAngle());
    p3.Revolve(center, GetAngle());
    p4.Revolve(center, GetAngle());

    DrawPolygon(GetColor(), 4,
                int(p1.GetX()), int(p1.GetY()),
                int(p2.GetX()), int(p2.GetY()),
                int(p3.GetX()), int(p3.GetY()),
                int(p4.GetX()), int(p4.GetY()));
}



Rectangle::Rectangle(const Rectangle& other_): Shape(other_.GetCenter(), other_.GetAngle(), other_.GetColor()),
m_base(other_.m_base), m_height(other_.m_height)
{}


Rectangle* Rectangle::Clone() const
{
    return new Rectangle(*this);
}

}//namespace hrd22

/************************Helpers Implementatios********************************/