#include "rocks.h"
#include "point.h"
#include "velocity.h"
#include "uiDraw.h"
#include "flyingObject.h"

#include <cmath> 

/*========================================================================
// ROCK PARENT CLASS
=========================================================================*/

/***********************************************************************
* This is the overall class for rocks. All rocks will inherit from this
************************************************************************/
Rocks :: Rocks() : FlyingObject(0, 0, 0, 0)
{
   float angle = random(ANGLE_MIN, ANGLE_MAX);

   point.setX(random(-190, 190));
   point.setY(random(-190, 190));

   velocity.setDx(1 * (-cos(M_PI / 180.0 * angle))); // x component of velocity
   velocity.setDy(1 * (sin(M_PI / 180.0 * angle)));  // y component of velocity
   rotation = 0;
}

/*=========================================================================
// LARGE ROCK
==========================================================================*/

/***********************************************************************
* The large rock constructor
************************************************************************/
LargeRock :: LargeRock()
{
   size = BIG_ROCK_SIZE;
} 

/***********************************************************************
* Hit: Determine if the rock has been hit
************************************************************************/
void LargeRock :: collision(std::vector<Rocks*> & rocks)
{
   kill();
   Point p = getPoint();
   Velocity v1 = getVelocity();
   Velocity v2 = getVelocity();
   Velocity v3 = getVelocity();

   v1.setDy(v1.getDy() + 1);
   v2.setDy(v2.getDy() - 1);
   v3.setDx(v3.getDx() + 3);


   Rocks* newRock1 = new MediumRock();
   newRock1->setPoint(p);
   newRock1->setVelocity(v1);
   rocks.push_back(newRock1);

   Rocks* newRock2 = new MediumRock();
   newRock2->setPoint(p);
   newRock2->setVelocity(v2);
   rocks.push_back(newRock2);

   Rocks* newRock3 = new SmallRock();
   newRock3->setPoint(p);
   newRock3->setVelocity(v3);
   rocks.push_back(newRock3);
}

/***********************************************************************
* Draw: draw the large rock at the point
************************************************************************/
void LargeRock :: draw() const
{
   drawLargeAsteroid(getPoint(), getRotation());
}

/***********************************************************************
* Advance: move the large rock. Here the rotation is added 
* and the velocity is added. 
************************************************************************/
void LargeRock :: advance()
{
   setRotation(getRotation() + BIG_ROCK_SPIN); 
   point.addX(velocity.getDx());
   point.addY(velocity.getDy());

   if (point.getX() >= 210 || point.getX() <= -210)
      point.setX(point.getX() * -1);

   if (point.getY() >= 210 || point.getY() <= -210)
      point.setY(point.getY() * -1); 
}


/*=========================================================================
// MEDIUM ROCK
==========================================================================*/

/***********************************************************************
* The medium rock constructor
************************************************************************/
MediumRock :: MediumRock() 
{
   size = MEDIUM_ROCK_SIZE;   
} 

/***********************************************************************
* Hit: Determine if the rock has been hit
************************************************************************/
void MediumRock :: collision(std::vector<Rocks*> & rocks)
{
   kill();

   Point p = getPoint();
   Velocity v1 = getVelocity();
   Velocity v2 = getVelocity();

   v1.setDx(v1.getDx() + 3);
   v2.setDx(v2.getDx() - 3);

   Rocks* newRock1 = new SmallRock();
   newRock1->setPoint(p);
   newRock1->setVelocity(v1);
   rocks.push_back(newRock1);

   Rocks* newRock2 = new SmallRock();
   newRock2->setPoint(p);
   newRock2->setVelocity(v2);
   rocks.push_back(newRock2);
}

/***********************************************************************
* Draw: draw the medium rock at the point
************************************************************************/
void MediumRock :: draw() const
{
   drawMediumAsteroid(getPoint(), getRotation());
}

/***********************************************************************
* Advance: move the medium rock. Here the rotation is added 
* and the velocity is added. 
************************************************************************/
void MediumRock :: advance()
{
   setRotation(getRotation() + MEDIUM_ROCK_SPIN);
   point.addX(velocity.getDx());
   point.addY(velocity.getDy());
   

   if (point.getX() >= 210 || point.getX() <= -210)
      point.setX(point.getX() * -1);

   if (point.getY() >= 210 || point.getY() <= -210)
      point.setY(point.getY() * -1); 
}


/*=========================================================================
// SMALL ROCK
==========================================================================*/

/***********************************************************************
* The small rock constructor
************************************************************************/
SmallRock :: SmallRock()
{
   size = SMALL_ROCK_SIZE;   
} 

/***********************************************************************
* Hit: Determine if the rock has been hit
************************************************************************/
void SmallRock :: collision(std::vector<Rocks*> & rocks)
{
   kill();
}

/***********************************************************************
* Draw: draw the small rock at the point
************************************************************************/
void SmallRock :: draw() const
{
   drawSmallAsteroid(getPoint(), getRotation());
}

/***********************************************************************
* Advance: move the small rock. Here the rotation is added 
* and the velocity is added. 
************************************************************************/
void SmallRock :: advance()
{
   setRotation(getRotation() + SMALL_ROCK_SPIN);
   point.addX(velocity.getDx());
   point.addY(velocity.getDy());
   

   if (point.getX() >= 210 || point.getX() <= -210)
      point.setX(point.getX() * -1);

   if (point.getY() >= 210 || point.getY() <= -210)
      point.setY(point.getY() * -1); 
}
