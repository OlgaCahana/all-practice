/*******************************************************************************
*	Written by:		Olga Danielle Cahana									   *
*	Date:			3/2/2022												   *
*	Reviewed by:    Tal Cohen
*   Description:    Circle class implementation
*   Versions:	    						    					 	   *
*																			   *
*******************************************************************************/
#ifndef ILRD_HRD22_GSHAPE_H
#define ILRD_HRD22_GSHAPE_H
#include <vector> /* vector */ 


#include  "point.hpp"  /* glut utils */ 
#include  "shape.hpp"  /* class Shape  */ 
namespace hrd22
{


class GroupShape : public Shape
{
public: 
    explicit GroupShape(Shape& shape);
    //~GroupShape();

    virtual GroupShape& Move(double xShift, double yShift);
    virtual GroupShape& Rotate(double angle);
    virtual void Draw() const;
    virtual GroupShape& Revolve(const ilrd::Point& pivot, double angle);
    virtual GroupShape& SetColor(COLORS color); 
    virtual GroupShape* Clone() const;
    GroupShape& AddShape(Shape& shape);
    GroupShape& RemoveShape(const Shape& shape);


private:
    std::vector<Shape *> m_shapes;

    GroupShape& operator=(GroupShape& other); //blocked do not implement
    GroupShape(const GroupShape& other); //to be used by clone

    void UpdateGroupCenter(const Shape& shape, int to_add);
    //const ilrd::Point& CalcGroupCenterIMP() const;
    //ilrd::Point CalcGroupCenter(const Shape& shape, int to_add) const;

};

}// namespace hrd22
#endif /* ILRD_HRD22_GSHAPE_H */


