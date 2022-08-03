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

#include "line.hpp"
#include  "shape.hpp"  /*  */ 
#include "utils.h"

using namespace std;
using namespace hrd22;

namespace hrd22
{

/*							API Implementaion			     				   */
/*******************************************************************************/
Line::Line(const ilrd::Point& center_ , double length_, double angle_, COLORS color_)
:Shape(center_, angle_, color_), m_lengh(length_) 
{}

void Line::Draw() const
{
    ilrd::Point center = GetCenter();
    ilrd::Point p1(center.GetX() - m_lengh/2, center.GetY());
    ilrd::Point p2(center.GetX() + m_lengh/2, center.GetY());

    p1.Revolve(center, GetAngle());
    p2.Revolve(center, GetAngle());

     DrawPolygon(GetColor(), 2,
                int(p1.GetX()), int(p1.GetY()),
                int(p2.GetX()), int(p2.GetY()));
}

Line::Line(const Line& other_)
:Shape(other_.GetCenter(), other_.GetAngle(), other_.GetColor()), m_lengh(other_.m_lengh)
{}


Line* Line::Clone() const
{
    return new Line(*this);
}


}// namespace hrd22


