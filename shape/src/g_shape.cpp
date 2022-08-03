/*******************************************************************************
*	Written by:		Olga Danielle Cahana									   *
*	Date:			3/2/2022												   *
*	Reviewed by:    Tal Cohen
*   Description:    Grouped Shape class implementation
*   Versions:	    						    					 	   *
*																			   *
*******************************************************************************/

#include <cassert>
#include <iostream>
#include <vector> 


#include  "shape.hpp"  
#include "g_shape.hpp"
#include "utils.h"

using namespace std;
using namespace hrd22;



/*							API Implementaion			     				   */
/*******************************************************************************/

GroupShape::GroupShape(Shape& shape_):
        Shape(shape_.GetCenter(),shape_.GetAngle(), shape_.GetColor()), m_shapes(1, &shape_)
{
  //  m_shapes.push_back(&shape_);
}

GroupShape& GroupShape::Move(double xShift_, double yShift_)
{
    vector<Shape *>::iterator iter_cur = m_shapes.begin();
    vector<Shape *>::iterator iter_end = m_shapes.end();

    //Update group center
    Shape::Move(xShift_,yShift_);

    //move each shape in the group
    while(iter_cur < iter_end)
    {
        (*iter_cur)->Move(xShift_,yShift_);
        ++iter_cur;
    }

    return *this;
}

GroupShape& GroupShape::Rotate(double angle_)
{
    vector<Shape *>::const_iterator iter_cur = m_shapes.begin();
    vector<Shape *>::const_iterator iter_end = m_shapes.end();

    //iterate through vector and revolve each shape, while the group center is the pivot
    while(iter_cur < iter_end)
    {
        (*iter_cur)->Revolve(GetCenter(), angle_);
        ++iter_cur;
    }

    return *this;

}

void GroupShape::Draw() const
{
    vector<Shape *>::const_iterator iter_cur = m_shapes.begin();
    vector<Shape *>::const_iterator iter_end = m_shapes.end();

    //iterate through vector and draw each shape
    while(iter_cur < iter_end)
    {
        (*iter_cur)->Draw();
        ++iter_cur;
    }
}

GroupShape& GroupShape::Revolve(const ilrd::Point& pivot_, double angle_)
{
    vector<Shape *>::iterator iter_cur = m_shapes.begin();
    vector<Shape *>::iterator iter_end = m_shapes.end();

    // ilrd::Point center = GetCenter();
    // Shape::Move(center.Revolve(pivot_,angle_).GetX(), center.Revolve(pivot_,angle_).GetY());

    Shape::Revolve(pivot_,angle_);

    //iterate through vector and draw each shape
    while(iter_cur < iter_end)
    {
        (*iter_cur)->Revolve(pivot_, angle_);
        ++iter_cur;
    }

    return *this;
}

// adding the same shape twice - undefined behaviour
GroupShape& GroupShape::AddShape(Shape& shape_)
{

    //calculate and update new center
    UpdateGroupCenter(shape_, 1);
    
    //add new shape to shapes vector
    m_shapes.push_back(&shape_);

    return *this;
}

GroupShape& GroupShape::RemoveShape(const Shape& shape_)
{
    vector<Shape *>::iterator iter_cur = m_shapes.begin();
    vector<Shape *>::iterator iter_end = m_shapes.end();

    //iterate through vector and find the shape to remove
    while(iter_cur < iter_end)
    {
        if(*iter_cur == &shape_)
        {
            UpdateGroupCenter(shape_, -1);

            //erase the shape 
            m_shapes.erase(iter_cur);

            return(*this);
        }
        ++iter_cur;
    }
    return *this;
}

GroupShape& GroupShape::SetColor(COLORS color_)
{
    vector<Shape*>:: iterator iter_curr = m_shapes.begin();
    vector<Shape*>:: iterator iter_end = m_shapes.end();

    
    while(iter_curr < iter_end)
    {
        (*iter_curr)->SetColor(color_);
    }
    return *this;
} 

//cctor
GroupShape::GroupShape(const GroupShape& other_):Shape(other_.GetCenter(), other_.GetAngle(), other_.GetColor())
{
    //not implemented
}

GroupShape* GroupShape::Clone() const
{
    return new GroupShape(*this);
}

/***************************Private IMP**************************************/
void GroupShape::UpdateGroupCenter(const Shape& shape_, int to_add_)
{
    int vec_old_size = m_shapes.size(); 
    int vec_new_size = vec_old_size + to_add_; // new vec size
    
    ilrd::Point new_center = (GetCenter() * vec_old_size +  shape_.GetCenter() * to_add_) / 
                vec_new_size;

    new_center -= GetCenter();
    Shape::Move(new_center.GetX(), new_center.GetY());
}



//TODO: when return type is const Point&, getting segfault - investigate- temporary object??
// ilrd::Point GroupShape::CalcGroupCenter(const Shape& shape_, int to_add_) const
// {
//     int vec_old_size = m_shapes.size(); 
//     int vec_new_size = vec_old_size + to_add_; // new vec size
    
//     return (GetCenter() * vec_old_size +  shape_.GetCenter() * to_add_) / 
//                 vec_new_size;
// }


// not used function
// const ilrd::Point& GroupShape::CalcGroupCenterIMP() const
// {
//     vector<Shape *>::const_iterator iter_cur = m_shapes.begin();
//     vector<Shape *>::const_iterator iter_end = m_shapes.end();

//     int vec_size = m_shapes.size();
//     ilrd::Point new_center(0,0);


//     while(iter_cur < iter_end)
//     {
//         new_center += (*iter_cur)->GetCenter();
//         ++iter_cur;
//     }
    
//      cout << new_center.GetX() <<endl;
//     cout << new_center.GetY() <<endl;
//     return new_center /= vec_size;
// }



