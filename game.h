/*********************************************************************
 * File: game.h
 * Description: Defines the game class for Asteroids
 *
 *********************************************************************/

#ifndef GAME_H
#define GAME_H

#include <vector>

#include "uiDraw.h"
#include "uiInteract.h"
#include "point.h"
#include "rocks.h"
#include "bullet.h"
#include "velocity.h"
#include "ship.h"
#include "powerUp.h"


/*****************************************
 * GAME
 * The main game class containing all the state
 *****************************************/
class Game
{
public:
   /*********************************************
    * Constructor
    * Initializes the game
    *********************************************/
   Game(Point tl, Point br);
   ~Game();

   /*********************************************
    * Function: handleInput
    * Description: Takes actions according to whatever
    *  keys the user has pressed.
    *********************************************/
   void handleInput(const Interface & ui);

   /*********************************************
    * Function: advance
    * Description: Move everything forward one
    *  step in time.
    *********************************************/
   void advance();
   
   /*********************************************
    * Function: draw
    * Description: draws everything for the game.
    *********************************************/
   void draw(const Interface & ui);

private:
   // The coordinates of the screen
   Point topLeft;
   Point bottomRight;

   std::vector<Rocks *> rocks;   // Vector for rocks
   std::vector<Bullet> bullets;  // Vector for bullets
   Ship * ship;
   PowerUp * powerUp;

   /*************************************************
    * Private methods to help with the game logic.
    *************************************************/
   bool isOnScreen(const Point & point);
   void advanceBullets();
   void advanceShip();
   void advanceRocks();
   void advancePowerUp();
   PowerUp* createPowerUp();
   Rocks* createRock();
   
   void handleCollisions();
   void cleanUpZombies();
   float getClosestDistance(const FlyingObject &obj1, const FlyingObject &obj2) const;
};

#endif /* GAME_H */
