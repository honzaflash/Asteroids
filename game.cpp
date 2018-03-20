/*********************************************************************
 * File: game.cpp
 * Description: Contains the implementaiton of the game class
 *  methods.
 *
 *********************************************************************/

#include "game.h"
#include <string>
#include "uiDraw.h"
#include "uiInteract.h"
#include "point.h"
#include <vector>

// These are needed for the getClosestDistance function...
#include <limits>
#include <algorithm>
using namespace std;

//TODO: possibly remove this.

#define OFF_SCREEN_BORDER_AMOUNT 5
#define BEGGINNING_ASTEROID_COUNT 5

// You may find this function helpful...

/**********************************************************
 * Function: getClosestDistance
 * Description: Determine how close these two objects will
 *   get in between the frames.
 **********************************************************/
/*
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
*/

/***************************************
 * GAME CONSTRUCTOR
 ***************************************/
Game :: Game(Point tl, Point br)
 : topLeft(tl), bottomRight(br)
{
   // Set up the initial conditions of the game
   bStartGame = false;

   // ship = NULL;

}

/****************************************
 * GAME DESTRUCTOR
 ****************************************/
Game :: ~Game()
{
   //Check to see if there is currently an asteroid allocated
   //       and if so, delete it.

   for (list<Asteroid*>::iterator it = asteroids.begin();
        it != asteroids.end();)
   {
      if (*it) // DO NOT dereference NULL
         delete (*it);
      it = asteroids.erase(it);
   }

// if (ship) // ensures not dereferencing NULL
//    {
//       delete ship;
//       ship = NULL;
//    }

}

/***************************************
 * GAME :: ADVANCE
 * advance the game one unit of time
 ***************************************/
void Game :: advance()
{
   if (bStartGame)
   {
   advanceBullets();
   advanceAsteroid();
   // advanceShip();

   handleCollisions();
   cleanUpZombies();
   }

   else
   {
      startGame();
   }
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
         
         if (!isOnScreen(bullets[i].getPoint()))
         {
            // the bullet has left the screen
            bullets[i].kill();
         }
         
      }
   }
}

/**************************************************************************
 * GAME :: ADVANCE Asteroid
 *
 * 1. If there are no Asteroids, create them
 * 2. If there is an Asteroid, and it's alive, advance it
 * 3. Check if the Asteroid has gone of the screen, and if so, wrap it
 **************************************************************************/
void Game :: advanceAsteroid()
{ 
   if (!asteroids.size()) // create asteroids if none
   {
      createAsteroid();
   }
   else
   {
      // advance asteroids
      for (list<Asteroid*>::iterator it = asteroids.begin();
            it != asteroids.end(); it++)
            {
               (*it)->advance();
            }
         
   }

}

/**************************************************************************
 * GAME :: ADVANCE Ship
 *
 * 1. If there are no ship, create it
 * 2. If there is an ship and it's alive, advance it
 * 3. Check if the shiphas gone of the screen, and if so, wrap it
 **************************************************************************/
void Game :: advanceShip()
{ 
   // if (ship == NULL) // create asteroids if none
   // {
   //    createShip();
   // }
   // else
   // {
   //    // we have a ship, make sure it's alive
   //    if (ship->isAlive())
   //    {
   //       // move it forward
   //       ship->advance();

   //    }

   //    //TODO: Should there be an else here???
              
   // }

}

/**************************************************************************
 * GAME :: CREATE Asteroid
 * Create an Asteroid according to the rules of the game.
 **************************************************************************/
void Game :: createAsteroid()
{
   //TODO: get rid of magic number
    for (int i = 0; i < 5; i++)
   {
      asteroids.push_back(new LargeAsteroid());
   }
   
}

/**************************************************************************
 * GAME :: CREATE Ship
 * Create an ship according to the rules of the game.
 **************************************************************************/
// void Game :: createShip()
// {

//    ship = new Ship();
   
// }

/**************************************************************************
 * GAME :: IS ON SCREEN
 * Determines if a given point is on the screen.
 **************************************************************************/
bool Game :: isOnScreen(const Point & point)
{
   return (point.getX() >= topLeft.getX() - OFF_SCREEN_BORDER_AMOUNT
      && point.getX() <= bottomRight.getX() + OFF_SCREEN_BORDER_AMOUNT
      && point.getY() >= bottomRight.getY() - OFF_SCREEN_BORDER_AMOUNT
      && point.getY() <= topLeft.getY() + OFF_SCREEN_BORDER_AMOUNT);
}

/**************************************************************************
 * GAME :: HANDLE COLLISIONS
 * Check for a collision between a bird and a bullet.
 **************************************************************************/
void Game :: handleCollisions()
{

}

/**************************************************************************
 * GAME :: CLEAN UP ZOMBIES
 * Remove any dead objects (take bullets out of the list, deallocate bird)
 **************************************************************************/
void Game :: cleanUpZombies()
{
  
}

/***************************************
 * GAME :: HANDLE INPUT
 * accept input from the user
 ***************************************/
void Game :: handleInput(const Interface & ui)
{
   // Change the direction of the ship
   if (ui.isLeft())
   {
      ship->moveLeft();
   }
   
   if (ui.isRight())
   {
      ship->moveRight();
   }

   // Check for "Spacebar
   if (ui.isSpace())
   {
      Bullet newBullet;

      //change to get ship angle and fire from there
      newBullet.fire(ship->getPoint(), ship->getOrientation());
      
      bullets.push_back(newBullet);
   }

   // Check for "Y" press
   if (ui.isY())
   {
      bStartGame = true;
   }
}

/*********************************************
 * GAME :: DRAW
 * Draw everything on the screen
 *********************************************/
void Game :: draw(const Interface & ui)
{

   // draw the asteroids
  for (list<Asteroid *> :: iterator it = asteroids.begin();
           it != asteroids.end(); ++it)
         (*it)->draw();

   // draw the ship
   // ship->draw();
   
   // draw the bullets, if they are alive
   for (int i = 0; i < bullets.size(); i++)
   {
      if (bullets[i].isAlive())
      {
         bullets[i].draw();
      }
   }

}

/*************************************************
 * Prompt user if they want to start game
 *************************************************/
void Game :: startGame()
{
   Point center;
   char userPrompt[] = "Press 'F1' to start";
   center.setX(-50);
   center.setY(0);
   drawText(center, userPrompt);

}