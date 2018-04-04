/*********************************************************************
 * File: game.h
 * Description: Defines the game class for Asteroids
 *
 *********************************************************************/

#ifndef GAME_H
#define GAME_H

#include <vector>
#include <list>

#include "uiDraw.h"
#include "uiInteract.h"
#include "point.h"
#include "velocity.h"

#include "asteroids.h"
#include "ship.h"
#include "bullet.h"

using namespace std;

#define CLOSE_ENOUGH 15
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
   // function provided for collision distance
   float getClosestDistance(const FlyingObject &obj1, const FlyingObject &obj2) const;
   // The coordinates of the screen
   Point topLeft;
   Point bottomRight;
   

   // declare Ship and bullets
   Ship* ship;
   vector<Bullet*> bullets;

   //declare asteroids here ex Asteroid * asteroid;
   list<Asteroid*> asteroids; // list for all asteroids

   /*************************************************
    * Private methods to help with the game logic.
    *************************************************/

   bool isOnScreen(const Point & point);
   void advanceBullets();
   void advanceAsteroid();
   void advanceShip();
   void createAsteroid();
   Ship* createShip();
   void createBullet();
   
   void handleCollisions();
   bool getCollision(const FlyingObject &obj1, const FlyingObject &obj2, int radius);
   void cleanUpZombies();
   void explodeLarge(Asteroid *asteroid, Bullet *bullet);
   void createMediumAsteroid(Point point, Velocity velocity);
   void explodeSmall(Asteroid *asteroid, Bullet *bullet);
   void explodeMedium(Asteroid *asteroid, Bullet *bullet);
   void createSmallAsteroid(Point point, Velocity velocity);

   /*************************************************
    * Private value to check if user want to play
    *************************************************/
   bool bStartGame;

   void startGame();
};

#endif
