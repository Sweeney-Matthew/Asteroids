/***********************************************************************
 * Source File:
 *    Velocity : The speed and direction of the object
 * Author:
 *    Matthew Sweeney
 * Summary:
 *    Everything we need to know about speed of the object.
 ************************************************************************/

#include "velocity.h"

/*********************************************
 * Default Constructor. Sets velocity dimensions to zero.
 *********************************************/
Velocity :: Velocity()
{
   setDx(0.0);
   setDy(0.0);
}

/*********************************************
 * Non default constructor. Assigns parameters to variables.
 *********************************************/
Velocity :: Velocity(float x, float y)
{
   setDx(x);
   setDy(y);
}

/*********************************************
 * Set x coordinate for velocity
 *********************************************/
void Velocity :: setDx(float x)
{
   Dx = x;
   
}

/*********************************************
 * Set y coordinate for velocity
 *********************************************/
void Velocity :: setDy(float y)
{
   Dy = y;
}
