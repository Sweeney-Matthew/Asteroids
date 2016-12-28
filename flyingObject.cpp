/*************************************************************
 * File: flyingObject.cpp
 * Author: Matthew Sweeney
 *
 * Description: Defines a flying object.
 *
 *************************************************************/

#include "point.h"
#include "velocity.h"
#include "uiDraw.h"
#include "flyingObject.h"

#include <cassert>

/**************************************************************************
 * Constructor. Takes 4 values for point and velocity, then sets them.
 **************************************************************************/
FlyingObject :: FlyingObject(int x, int y, int Dx, int Dy)
{
   setAlive(true);  // default to object being alive

   // Set the x and y for point and the x and y for velocity
   point.setX(x);
   point.setY(y);

   velocity.setDx(Dx);
   velocity.setDy(Dy);
}

/**************************************************************************
 * Kill the object by setting alive to false
 **************************************************************************/
void FlyingObject :: kill()
{
   this->alive = false;
}

/**************************************************************************
 * Set the point
 **************************************************************************/
void FlyingObject :: setPoint(Point & point)
{
   this->point = point;
}

/**************************************************************************
 * Set the velocity
 **************************************************************************/
void FlyingObject :: setVelocity(Velocity & velocity)
{
   this->velocity = velocity;
}

/**************************************************************************
 * Move the object by adding to velocity values
 **************************************************************************/
void FlyingObject :: advance()
{
   point.addX(velocity.getDx());
   point.addY(velocity.getDy());
}  

/**************************************************************************
 * Set the alive value
 **************************************************************************/
void FlyingObject :: setAlive(bool alive)
{
   this->alive = alive;
} 
