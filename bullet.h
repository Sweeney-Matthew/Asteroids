#ifndef bullet_h
#define bullet_h

#define BULLET_SPEED 5
#define BULLET_LIFE 40

#include "point.h"
#include "flyingObject.h"
#include "velocity.h"

class Bullet : public FlyingObject
{
private:
   int life;   // How long the bullet lives

public:
   // Constructor
   Bullet();

   // Draws bullet
   virtual void draw() const;

   // Fires rifle
   void fire(const Point & p, float angle, const Velocity & v);

   // Life getter and setter
   int getLife() const { return life; }
   void setLife(int life) { this->life = life; }

   virtual void advance();
};


#endif /* bullet_h */
