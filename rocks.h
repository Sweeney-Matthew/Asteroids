/*********************************************************************
 * File: rocks.h
 * Description: Defines the rocks class for Asteroids
 *
 *********************************************************************/

#ifndef rocks_h
#define rocks_h

#define BIG_ROCK_SIZE 16
#define MEDIUM_ROCK_SIZE 8
#define SMALL_ROCK_SIZE 4

#define BIG_ROCK_SPIN 2
#define MEDIUM_ROCK_SPIN 5
#define SMALL_ROCK_SPIN 10

#define ANGLE_MIN 0
#define ANGLE_MAX 360

#include "point.h"
#include "flyingObject.h"
#include "velocity.h"

#include <vector>

/***********************************************************************
* This is the overall class for rocks. All rocks will inherit from this
************************************************************************/
class Rocks : public FlyingObject
{
protected:

   int rotation;
   int size;

public:
   Rocks();  // Constructor
   
   // Pur virtual functions
   virtual void draw() const = 0;
   virtual void advance() = 0;

   // What to do when hit
   virtual void collision(std::vector<Rocks*> & rocks) { }
   
   // Rotation getter and setter
   int getRotation() const { return rotation; }
   void setRotation(int rotation) { this->rotation = rotation; }

   // Gets size
   int getSize() const { return size; }
};

/***********************************************************************
* Large Rock
************************************************************************/
class LargeRock : public Rocks
{
public:
   LargeRock();

   virtual void draw() const;

   virtual void advance();

   virtual void collision(std::vector<Rocks*> & rocks);
};

/***********************************************************************
* Medium Rock
************************************************************************/
class MediumRock : public Rocks
{
public:
   MediumRock();

   virtual void draw() const;

   virtual void advance();

   virtual void collision(std::vector<Rocks*> & rocks);
};

/***********************************************************************
* Small Rock
************************************************************************/
class SmallRock : public Rocks
{
public:
   SmallRock();

   virtual void draw() const;

   virtual void advance();

   virtual void collision(std::vector<Rocks*> & rocks);
};

#endif /* rocks_h */
