#include "ship.h"
#include "velocity.h"
#include "flyingObject.h"
#include "uiDraw.h"
#include "point.h"

/***********************************************************************
* Ship Constructor
************************************************************************/
Ship :: Ship() : FlyingObject(0, 0, 0, 0)
{
   setAngle(0);
   power = 0;
}

/***********************************************************************
* Draws ship
************************************************************************/
void Ship :: draw() const
{
   drawShip(getPoint(), getAngle(), getThrust()); 
}

/***********************************************************************
* Moves the ship left
************************************************************************/
void Ship :: moveLeft()
{
   setAngle(getAngle() + ROTATE_AMOUNT);

   if (getAngle() > ANGLE_MAX)
   {
      setAngle(getAngle() - ANGLE_MAX);
   }
}

/***********************************************************************
* Moves the ship right
************************************************************************/
void Ship :: moveRight()
{
   setAngle(getAngle() - ROTATE_AMOUNT);
   
   if (angle < ANGLE_MIN)
   {
      setAngle(getAngle() + ANGLE_MAX);
   }
}

/***********************************************************************
* Move the ship forward
************************************************************************/
void Ship :: moveForward()
{
   velocity.setDy(velocity.getDy() + 0.5 * (cos(M_PI / 180.0 * angle))); // y component of velocity
   velocity.setDx(velocity.getDx() + 0.5 * (-sin(M_PI / 180.0 * angle)));  // x component of velocity
   setThrust(true);
}

/***********************************************************************
* Advances the ship one frame
************************************************************************/
void Ship :: advance()
{
   // Move point according to velocity
   point.addX(velocity.getDx()); 
   point.addY(velocity.getDy());

   // If powered, add to variable as a timer
   if (getIsPowered())
   {
      power++;
   }

   // If timer runs out, reset and unpower
   if (power >= 200)
   {
      power = 0;
      setIsPowered(false);
   }

   // Screen wrapping parts
   if (point.getX() >= 210 || point.getX() <= -210)
      point.setX(point.getX() * -1);

   if (point.getY() >= 210 || point.getY() <= -210)
      point.setY(point.getY() * -1); 
}
