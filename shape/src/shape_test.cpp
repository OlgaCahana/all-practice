/*******************************************************************************
*	Written by:		Olga Danielle Cahana									   *
*	Date:			3/2/2022												   *
*	Reviewed by:    Tal Cohen
*   Description:    Grouped Shape class implementation
*   Versions: 
*   v1.0 - ready for review	    						    					 	   *
*																			   *
*******************************************************************************/

#include <cassert>
#include <iostream>
#include <vector> /* vector */ 


#include "glut_utils.h"
#include "point.hpp"
#include  "shape.hpp"  /*  */ 
#include "g_shape.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
#include "line.hpp"
#include "utils.h"

using namespace std;
using namespace hrd22;

static void DrawFunction();
static int KeyboardFunction(unsigned char key, int x, int y);
static int MouseFunction(int button, int state, int x, int y);
static int MotionFunction(int x, int y);
static int TimerFunction();

/**********************Globals**************************************************/
int drawCircle = 1;
ilrd::Point pcenter(500,500);
Circle c1(ilrd::Point(500,500));
Circle c2(ilrd::Point(500,500));
Circle c3(ilrd::Point(500,500));
Circle c4(ilrd::Point(500,500));

Circle c11(ilrd::Point(500,500));
Circle c21(ilrd::Point(500,500));
Circle c31(ilrd::Point(500,500));
Circle c41(ilrd::Point(500,500));

Line l1(ilrd::Point(100,500), 90, 0.5);

Rectangle r1(ilrd::Point(400,200), 100, 50, 0, COLOR_MAGENTA);
Rectangle r2(ilrd::Point(500,500), 50, 50, 0, COLOR_CYAN);

Circle c5(ilrd::Point(250,250), 50,0,COLOR_GREEN);
Rectangle r3(ilrd::Point(200,200), 100, 100, 0, COLOR_CYAN);

Circle c6(ilrd::Point(700,400), 50,0,COLOR_CYAN);
Circle c7(ilrd::Point(700,330), 50,0,COLOR_CYAN);

Rectangle r4(ilrd::Point(500,800), 100, 100, 0, COLOR_CYAN);
Rectangle r5(ilrd::Point(500,900), 100, 100, 0, COLOR_CYAN);
 Circle *cc7 = c7.Clone(); 
        



GroupShape g1(c5);
GroupShape g2(c6);
GroupShape g3(r4);



/*****************************Test*********************************************/
int main(int argc, char** argv)
{
    cout << "Start testing shapes" << endl;
    g1.AddShape(r3);
    g2.AddShape(c7);
    g3.AddShape(r5);
    DrawInit(argc, argv, 1000, 1000, DrawFunction);

    /* advanced: extra functionality */
    DrawSetKeyboardFunc(KeyboardFunction);
  //  DrawSetMouseFunc(MouseFunction);
    DrawSetMotionFunc(MotionFunction);
    DrawSetTimerFunc(TimerFunction, 70);
    
    DrawMainLoop();

    printf("exit\n");

    cout << "end" << endl;
    delete cc7;
    return 0;
}

static void DrawFunction()
{
    static int st = 0;
    ++st;
    cout << "st: " << st << endl;
  //  g1.Draw();
    g2.Draw();
    g3.Draw();
    (*cc7).Draw();

    l1.Draw();

    /* draw rectangle */
    r1.Draw();
    r2.Draw();
    if (drawCircle)
    {
        c1.Draw();
        c2.Draw();
        c3.Draw();
        c4.Draw();

        c11.Draw();
        c21.Draw();
        c31.Draw();
        c41.Draw();
    }

}

static int KeyboardFunction(unsigned char key, int x, int y)
{
    printf("Keyboard: %02x,%d,%d\n", key, x, y);

    if (key == 0x1b /* ESC */)
        return -1;

    return 0;
}


static int MouseFunction(int button, int state, int x, int y)
{


    return 0;
}


static int MotionFunction(int x, int y)
{
    cout << "Mouse:" << x << "," << y << endl;

    return 0;
}


static int TimerFunction()
{
    static bool action = false;
    static int tm = 0;
    static int add_shape = 0;
    ++tm;

   // g1.Move(1,1);
    //g1.Rotate(0.4);
    g2.Rotate(0.2);
    //g3.Rotate(0.1);
    //g1.Revolve(ilrd::Point(500,500), 0.1);
    l1.Rotate(0.1);

    g3.Revolve(pcenter, 0.1);
    if(tm < 100)
    {
        c1.Move(-1,-1);
        c2.Move(1,-1);
        c3.Move(-1,1);
        c4.Move(1,1);

        c11.Move(-1,-1);
        c21.Move(1,-1);
        c31.Move(-1,1);
        c41.Move(1,1);

        // c11.Move(1,1);
        // c21.Move(-1,1);
        // c31.Move(1,-1);
        // c41.Move(-1,-1);
    }
    else
    {
        c1.Move(1,1);
        c2.Move(-1,1);
        c3.Move(1,-1);
        c4.Move(-1,-1);

        c11.Move(-1,-1);
        c21.Move(1,-1);
        c31.Move(-1,1);
        c41.Move(1,1);

    }

    if(add_shape == 100)
    {
        g3.AddShape(*cc7);
      //  add_shape = 101;
    }
    else if(add_shape == 165)
    {
       g3.RemoveShape(*cc7);
    }
    if(add_shape < 165)  
    {
        ++add_shape;
    }
    DEBUG_ONLY(
    cout << "cc7"<<(*cc7).GetAngle() << endl;
    cout << "r5" << r5.GetAngle() << endl;)

    if((*cc7).GetAngle() == 1.0)
    {
        g3.RemoveShape((*cc7));
    }

    if(tm == 200)
    {
        tm = 0;
        r1.SetColor(COLOR_BLACK);
    }
    else
    {
        
    }
   // tm = (tm==200 ? 0 : tm);
    r1.Revolve(ilrd::Point(500,500), 0.5);
    r2.Rotate(0.5);
    // if(action == 1)
    // {
    //     c1.SetColor(COLOR_BLACK);
    //     c2.SetColor(COLOR_BLACK);
    //     c3.SetColor(COLOR_BLACK);
    //     c4.SetColor(COLOR_BLACK);
        
    // }
    // else if(action == 0)
    // {
    //     c1.SetColor(COLOR_WHITE);
    //     c2.SetColor(COLOR_WHITE);
    //     c3.SetColor(COLOR_WHITE);
    //     c4.SetColor(COLOR_WHITE);  
    // }

    action ^= 1;
   
    return 1;  /* draw */
}

//compile from src:
//gcpp shape.cpp g_shape.cpp shape_test.cpp circle.cpp line.cpp rectangle.cpp ../lib/libpoint.a -I ../include -Wl,-rpath=. ../lib/libglut_utils.so 