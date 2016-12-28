#ifndef ship_h
#define ship_h

#define SHIP_SIZE 10

#define ROTATE_AMOUNT 6
#define THRUST_AMOUNT 0.5

#define ANGLE_MIN 0
#define ANGLE_MAX 360

#include "point.h"
#include "flyingObject.h"
#include "velocity.h"

// Put your Ship class here
class Ship : public FlyingObject
{
private:
   int angle;       // Angle of ship
   bool thrust;     // Draw fire?
   bool isPowered;  // Is it powered up?
   int power;       // Length of power up

public:
   // Constructor
   Ship();

   // Angle getter and setter
   int getAngle() const { return angle; }
   void setAngle(int angle) { this->angle = angle; }

   // Thrust getter and setter
   bool getThrust() const { return thrust; }
   void setThrust(bool thrust) { this->thrust = thrust; }

   // Powered getter and setter
   bool getIsPowered() const { return isPowered; }
   void setIsPowered(bool isPowered) { this->isPowered = isPowered; }

   // Draws ship
   virtual void draw() const;

   // Movement functions
   void moveLeft();
   void moveRight();
   void moveForward();

   virtual void advance();
};

#endif /* ship_h */
