/*********************************************************************
 * File: game.cpp
 * Description: Contains the implementaiton of the game class
 *  methods.
 *
 *********************************************************************/

#include "game.h"

// These are needed for the getClosestDistance function...
#include <limits>
#include <algorithm>

#include "uiDraw.h"
#include "uiInteract.h"
#include "point.h"

#define OFF_SCREEN_BORDER_AMOUNT 5

using namespace std;


/***************************************
 * GAME CONSTRUCTOR
 ***************************************/
Game :: Game(Point tl, Point br)
 : topLeft(tl), bottomRight(br)
{
   // Create 5 rocks at the start
   for (int i = 0; i < 5; i++)
   {
      rocks.push_back(createRock());   
   }

   // Create a ship
   ship = new Ship();

   // Space for power up to appear
   powerUp = NULL;
}

/****************************************
 * GAME DESTRUCTOR
 ****************************************/
Game :: ~Game()
{
   // Delete ship
   if (ship != NULL)
   {
      delete ship;
      ship = NULL;
   }

   // Delete non destroyed rocks
   vector<Rocks *>::iterator rockIt = rocks.begin();
   while (rockIt != rocks.end())
   {
      Rocks* pRock = *rockIt;

      delete pRock;
      pRock = NULL;
      rockIt = rocks.erase(rockIt);
   }

   // Delete power up
   if (powerUp != NULL)
   {
      delete powerUp;
      powerUp = NULL;
   }

}

/**************************************************************************
 * GAME :: CREATE ROCK
 * Create a rock
 **************************************************************************/
Rocks* Game :: createRock()
{
   Rocks* newRock = new LargeRock();  // Creates new large rock
  
   return newRock;
}

/**************************************************************************
 * GAME :: CREATE POWERUP
 * Create a power up for the ship.
 **************************************************************************/
PowerUp* Game :: createPowerUp()
{
   PowerUp* newPowerUp = NULL;   // set to NULL 

   newPowerUp = new PowerUp();   // Create new power up
   
   return newPowerUp;
}

/***************************************
 * GAME :: ADVANCE
 * advance the game one unit of time
 ***************************************/
void Game :: advance()
{
   // Advance the game elements
   advanceBullets();
   advanceRocks();
   advancePowerUp();

   if (ship->isAlive())
   {
      ship->advance();   // Only advance ship it it's alive
   }

   handleCollisions();
   cleanUpZombies();
}

/***************************************
 * GAME :: ADVANCE BULLETS
 * Go through each bullet and advance it.
 ***************************************/
void Game :: advanceBullets()
{
   // Move each of the bullets forward if it is alive
   for (int i = 0; i < bullets.size(); i++)
   {
      if (bullets[i].isAlive())
      {
         // this bullet is alive, so tell it to move forward
         bullets[i].advance();
      }
   }
}

/**************************************************************************
 * GAME :: ADVANCE ROCKS
 * Move rocks
 **************************************************************************/
void Game :: advanceRocks()
{
   for (int i = 0; i < rocks.size(); i++)
      if (rocks[i]->isAlive())
      {
         // move it forward
         rocks[i]->advance();         
      }
}

/**************************************************************************
 * GAME :: ADVANCE POWERUPS
 * Move rocks
 **************************************************************************/
void Game :: advancePowerUp()
{
   if (powerUp == NULL)  // If no power up currently
   {  
      if (random(0, 200) == 0) // Randomly appear. We don't want it always there
      {
         // create a new powerup
         powerUp = createPowerUp();
      }
   }
}

/**************************************************************************
 * GAME :: HANDLE COLLISIONS
 * Check for a collision between a asteroid and a bullet.
 **************************************************************************/
void Game :: handleCollisions()
{
   for (int i = 0; i < bullets.size(); i++)
   {
      if (bullets[i].isAlive())  // If bullet is alive
      {
         for (int j = 0; j < rocks.size(); j++)
         {
            if (rocks[j] != NULL && rocks[j]->isAlive())  // if rock is alive
            {
               if (getClosestDistance(bullets[i], *rocks[j]) < (2 + rocks[j]->getSize()))  // see if they collided
               {
               //we have a hit!
               
               // rock collision
               rocks[j]->collision(rocks);
               
               // the bullet is dead as well
               bullets[i].kill();
               }
            }
         }
      }
   }

   if (ship->isAlive())  // if ship is alive
   {
      for (int i = 0; i < rocks.size(); i++)
      {
         if (rocks[i] != NULL && rocks[i]->isAlive())  // if rock is alive
         {
            if (getClosestDistance(*ship, *rocks[i]) < (rocks[i]->getSize() + 10))  // see if ship hit rock
            {   
               rocks[i]->collision(rocks);  // Rock collision 

               ship->kill();  // Kill the ship also
            }
         }  
      }
   }

   if (ship->isAlive() && powerUp != NULL)  // If ship is alive and power up is allocated
   {
      if (getClosestDistance(*ship, *powerUp) < 20)   // Did ship hit power up
      {
         powerUp->kill();  // Kill power up
         ship->setIsPowered(true);  // and power up the ship
      }
   }
}

/**************************************************************************
 * GAME :: CLEAN UP ZOMBIES
 * Remove any dead objects (take bullets out of the list, deallocate asteroid)
 **************************************************************************/
void Game :: cleanUpZombies()
{
   // Look for dead bullets
   vector<Bullet>::iterator bulletIt = bullets.begin();
   while (bulletIt != bullets.end())
   {
      Bullet bullet = *bulletIt;
      
      if (!bullet.isAlive())
      {    
         // remove from list and advance
         bulletIt = bullets.erase(bulletIt);
      }
      else
      {
         bulletIt++; // advance
      }
   }

   // Look for dead rocks
   vector<Rocks *>::iterator rockIt = rocks.begin();
   while (rockIt != rocks.end())
   {
      Rocks* pRock = *rockIt;

      if (!pRock->isAlive())
      {
         delete pRock;
         pRock = NULL;
         rockIt = rocks.erase(rockIt);
      }
      else
      {
         rockIt++;
      }
   }

   if (powerUp != NULL && !powerUp->isAlive())
   {  
      // Clean up the memory used by the power up
      powerUp = NULL;  
   }
}

/***************************************
 * GAME :: HANDLE INPUT
 * accept input from the user
 ***************************************/
void Game :: handleInput(const Interface & ui)
{
   // Handles all keyboard input for ship movement. Only respond if ship is alive
   if (ship->isAlive())
   {
      if (ui.isLeft())
      {
         ship->moveLeft();
      }
   
      if (ui.isRight())
      {
         ship->moveRight();
      }

      if (ui.isUp())
      {
         ship->moveForward();
      }
      else if (!ui.isUp())
      {
         ship->setThrust(false);
      }
   
      // Check for spacebar
      if (ui.isSpace())
      {
         // Check to see if the ship is powered. If it's powered it will fire three bullets in a spray formation
         if (ship->getIsPowered())
         {
            int powerAngleLeft = ship->getAngle() + 25;  // This is the left spray
            int powerAngleRight = ship->getAngle() - 25; // This is the right spray
            
            // Make sure the angle numbers are ok
            if (powerAngleLeft > 360)
            {
               powerAngleLeft -= 360;
            }

            if (powerAngleRight < 0)
            {
               powerAngleRight += 360;
            }

            // Fire first bullet straight
            Bullet newBullet1;
            newBullet1.fire(ship->getPoint(), ship->getAngle(), ship->getVelocity());     
            bullets.push_back(newBullet1);

            // Fire second bullet to left
            Bullet newBullet2;
            newBullet2.fire(ship->getPoint(), powerAngleLeft, ship->getVelocity());     
            bullets.push_back(newBullet2);

            // Fire third bullet right
            Bullet newBullet3;
            newBullet3.fire(ship->getPoint(), powerAngleRight, ship->getVelocity());     
            bullets.push_back(newBullet3);
         }
         else
         {
            // If not powered, just fire one bullet straight
            Bullet newBullet;
            newBullet.fire(ship->getPoint(), ship->getAngle(), ship->getVelocity());     
            bullets.push_back(newBullet);
         }        
      }
   } 
}

/*********************************************
 * GAME :: DRAW
 * Draw everything on the screen
 *********************************************/
void Game :: draw(const Interface & ui)
{
   // Draw the rocks
   for (int i = 0; i < rocks.size(); i++)
      if (rocks[i]->isAlive())
      {
         rocks[i]->draw();
      }

   // draw the ship
   if (ship->isAlive())
      ship->draw();

   // draw the bullets, if they are alive
   for (int i = 0; i < bullets.size(); i++)
   {
      if (bullets[i].isAlive())
      {
         bullets[i].draw();
      }
   }

   // Draw the power up if it exists
   if (powerUp != NULL && powerUp->isAlive())
      powerUp->draw();
}

/**********************************************************
 * Function: getClosestDistance
 * Description: Determine how close these two objects will
 *   get in between the frames.
 **********************************************************/

float Game :: getClosestDistance(const FlyingObject &obj1, const FlyingObject &obj2) const
{
   // find the maximum distance traveled
   float dMax = max(abs(obj1.getVelocity().getDx()), abs(obj1.getVelocity().getDy()));
   dMax = max(dMax, abs(obj2.getVelocity().getDx()));
   dMax = max(dMax, abs(obj2.getVelocity().getDy()));
   dMax = max(dMax, 0.1f); // when dx and dy are 0.0. Go through the loop once.
   
   float distMin = std::numeric_limits<float>::max();
   for (float i = 0.0; i <= dMax; i++)
   {
      Point point1(obj1.getPoint().getX() + (obj1.getVelocity().getDx() * i / dMax),
                     obj1.getPoint().getY() + (obj1.getVelocity().getDy() * i / dMax));
      Point point2(obj2.getPoint().getX() + (obj2.getVelocity().getDx() * i / dMax),
                     obj2.getPoint().getY() + (obj2.getVelocity().getDy() * i / dMax));
      
      float xDiff = point1.getX() - point2.getX();
      float yDiff = point1.getY() - point2.getY();
      
      float distSquared = (xDiff * xDiff) +(yDiff * yDiff);
      
      distMin = min(distMin, distSquared);
   }
   
   return sqrt(distMin);
}


