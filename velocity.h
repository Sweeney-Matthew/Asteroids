/***********************************************************************
 * Header File:
 *    Velocity : Contains speed in which craft is moving and direction
 * Author:
 *    Matthew Sweeney
 * Summary:
 *    Has everything for speed of craft and provides information to move the point for the craft
 ************************************************************************/

#ifndef VELOCITY_H
#define VELOCITY_H

// Velocity class
class Velocity
{
public:
   Velocity();    // Default constructor
   Velocity(float x, float y);   // Non default constructor

   // Getters
   float getDx() const { return Dx; }
   float getDy() const { return Dy; }

   // Setters
   void setDx(float x);
   void setDy(float y);

// Private variables are just coordinates
private:
   float Dx;
   float Dy;

};

#endif // VELOCITY_H
