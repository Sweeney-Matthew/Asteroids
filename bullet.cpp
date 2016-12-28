/*************************************************************
 * File: bullet.cpp
 * Author: Matthew Sweeney
 *
 * Description: Defines a the bullet fired from rifle, inherited from flyer class
 *
 *************************************************************/

#include "point.h"
#include "velocity.h"
#include "flyingObject.h"
#include "uiDraw.h"
#include "bullet.h"
#include <cmath>

#include <cassert>

/***********************************************************************
* Constructor
************************************************************************/
Bullet :: Bullet() : FlyingObject(0, 0, 0, 0)
{
   setLife(0);
}

/***********************************************************************
* Draw bullet
************************************************************************/
void Bullet :: draw() const
{
   drawDot(getPoint());
}

/***********************************************************************
* Fires bullet
************************************************************************/
void Bullet :: fire(const Point & p, float angle, const Velocity & v)
{
   point.setX(p.getX());   // Set bullet x to whatever was passed by rifle
   point.setY(p.getY());   // Set bullet y to whatever was passed by rifle
  
   velocity.setDy(v.getDy() + BULLET_SPEED * (cos(M_PI / 180.0 * angle))); // additional y component of velocity
   velocity.setDx(v.getDx() + BULLET_SPEED * (-sin(M_PI / 180.0 * angle)));  // additional x component of velocity
 
}

/***********************************************************************
* Advance the bullet for each frame
************************************************************************/
void Bullet :: advance()
{
   point.addX(velocity.getDx());
   point.addY(velocity.getDy());
   setLife(getLife() + 1);  // increments life tracker for each bullet

   // Screen wrapping
   if (point.getX() >= 200 || point.getX() <= -200)
      point.setX(point.getX() * -1);

   if (point.getY() >= 200 || point.getY() <= -200)
      point.setY(point.getY() * -1);

   if (getLife() >= BULLET_LIFE)
      kill();
} 
