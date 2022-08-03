/*******************************************************************************
*	Written by:		Olga Danielle Cahana									   *
*	Date:			3/2/2022												   *
*	Reviewed by:    Tal Cohen
*   Description:    Circle class implementation
*   Versions:	    						    					 	   *
*	v1 - before review																		   *
*******************************************************************************/
#ifndef ILRD_HRD22_LINE_H
#define ILRD_HRD22_LINE_H


#include  "shape.hpp"  /*  */ 

namespace hrd22
{

class Line : public Shape
{
public:
    explicit Line(const ilrd::Point& center , double length = 1, double angle = 0, COLORS = COLOR_WHITE);
    void Draw() const;
    Line* Clone() const;

private:
    double m_lengh;
    Line(const Line&);

};


}// namespace ilrd



#endif /* ILRD_HRD22_LINE_H */