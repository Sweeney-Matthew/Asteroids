#include "velocity.h"
#include "flyingObject.h"
#include "uiDraw.h"
#include "point.h"
#include "powerUp.h"

/**************************************************************************
 * Default constructor
 **************************************************************************/
PowerUp :: PowerUp() : FlyingObject(random(-190, 190), random(-190, 190), 0, 0)
{
   // This makes the power up appear at a random location
}

/**************************************************************************
 * Draw the power up using the tough bird design but with a P
 **************************************************************************/
void PowerUp :: draw() const
{
   drawToughBird(getPoint(), 10);
}

/**************************************************************************
 * Move the object by adding to velocity values
 **************************************************************************/
void PowerUp :: advance()
{
   // The power up just sits there, so don't advance it.
} 
