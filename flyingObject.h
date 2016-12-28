/*************************************************************
 * File: flyingObject.h
 * Author: Matthew Sweeney
 *
 * Description: Defines a flying object.
 *
 *************************************************************/

#ifndef FLYINGOBJECT_H
#define FLYINGOBJECT_H

#include "point.h"
#include "velocity.h"

#include <vector>

using namespace std;

class FlyingObject
{
private:
   bool alive;  // is object alive?

// I want to be able to change this within derived classes, so protected
protected:
   Point point;
   Velocity velocity;

public:
   // Constructor, takes values to set starting point and velocity
   FlyingObject(int x, int y, int dX, int Dy);

   // Alive getter
   bool isAlive() const { return alive; }

   // Object getters
   Point getPoint() const { return point; }
   Velocity getVelocity() const { return velocity; }

   // Setters
   void setAlive(bool alive);
   void kill();
   void setPoint(Point & point);
   void setVelocity(Velocity & velocity);

   // Misc methods
   virtual void draw() const = 0;
   virtual void advance();
   
};

#endif /* flyingObject_h */
