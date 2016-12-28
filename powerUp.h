#ifndef powerUp_h
#define powerUp_h

#include "point.h"
#include "flyingObject.h"
#include "velocity.h"

class PowerUp : public FlyingObject
{

public:
   // Constructor
   PowerUp();

   // Draws power up
   virtual void draw() const;

   // Advance
   virtual void advance();
};

#endif
