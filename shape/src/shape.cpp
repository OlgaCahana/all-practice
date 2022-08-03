/*******************************************************************************
*	Written by:		Olga Danielle Cahana									   *
*	Date:			3/2/2022												   *
*	Reviewed by:    Tal Cohen
*   Description:    Shape abstract class implementation
*   Versions:	    						    					 	   *
*																			   *
*******************************************************************************/

#include <cassert>
#include <iostream>


#include  "shape.hpp"  /*  */ 
#include "utils.h"

using namespace std;
using namespace hrd22;

/*							API Implementaion			     				   */
/*******************************************************************************/
namespace hrd22
{

Shape::Shape(const ilrd::Point& center_, double angle_, COLORS color_) //Ctor
:m_center(center_), m_angle(angle_), m_color(color_)
{
    DEBUG_ONLY(cout << "Shape Ctor" << endl);
}

Shape::~Shape() //Dtor
{
    DEBUG_ONLY(cout << "Shape Dtor" << endl);
}

Shape& Shape::Move(double xShift_, double yShift_) // moves according to last location
{
    ilrd::Point p(xShift_, yShift_);
    m_center+= p;

    return *this;
}

Shape& Shape::Rotate(double angle_) // positive value rotates clockwise (unit - rad)
{
    m_angle += angle_;
    return *this;
}

Shape& Shape::Revolve(const ilrd::Point& pivot_, double angle_)
{
    m_center.Revolve(pivot_, angle_);
    m_angle += angle_; //TODO:handles overflow??

    return *this;
}

Shape& Shape::SetColor(COLORS color_)
{
    m_color = color_;
    return *this;
}

const ilrd::Point& Shape::GetCenter() const
{
    return m_center;
}
double Shape::GetAngle() const
{
    return m_angle;
} 
COLORS Shape::GetColor() const
{
    return m_color;
}
}//namespace hrd22