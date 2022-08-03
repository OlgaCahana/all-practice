/*******************************************************************************
*	Written by:		Olga Danielle Cahana									   *
*	Date:			10/5/2022												   *
*	Reviewed by:    Tal Cohen
*   Description:    Circle class implementation
*   Versions:	    						    					 	   *
*																			   *
*******************************************************************************/

#ifndef ILRD_HRD22_SHAPE_H
#define ILRD_HRD22_SHAPE_H


#include  "glut_utils.h"  /* glut utils */ 
#include  "point.hpp"  /* glut utils */ 
namespace hrd22
{

//abstract class
class Shape
{
public:
    explicit Shape(const ilrd::Point& center, double angle = 0, COLORS = COLOR_WHITE);
    virtual ~Shape();

    virtual Shape& Move(double xShift, double yShift); // moves according to last location
    virtual void Draw() const = 0;
    virtual Shape& Rotate(double angle); // positive value rotates clockwise (unit - rad)
    virtual Shape& Revolve(const ilrd::Point& pivot, double angle);
    virtual Shape& SetColor(COLORS color); // RGB
    virtual Shape* Clone() const = 0;

//protected:
    const ilrd::Point& GetCenter() const;
    double GetAngle() const; 
    COLORS GetColor() const;
    
    //how to get color? - protected or GetColor()?


private:
    ilrd::Point m_center;
    double m_angle;
    COLORS m_color;

    Shape(const Shape& other); //blocked do not implement
    Shape& operator=(const Shape& other); //blocked do not implement
};



}//namespace hrd22
#endif /* ILRD_HRD22_SHAPE_H */