/*********************************************************************
 * File: game.cpp
 * Description: Contains the implementaiton of the game class
 *  methods.
 *
 *********************************************************************/

#include "game.h"
#include <string>
#include <cstdio>
#include "uiDraw.h"
#include "uiInteract.h"
#include "point.h"
#include <vector>

// These are needed for the getClosestDistance function...
#include <limits>
#include <algorithm>
using namespace std;


#define OFF_SCREEN_BORDER_AMOUNT 5
#define BEGGINNING_ASTEROID_COUNT 100

// You may find this function helpful...


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


/***************************************
 * GAME CONSTRUCTOR
 ***************************************/
Game :: Game(Point tl, Point br)
 : topLeft(tl), bottomRight(br), benchmark()
{
   // Set up the initial conditions of the game
   bStartGame = false;

   ship = NULL;
   ship = createShip();

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

   for (vector<Bullet*>::iterator it = bullets.begin();
        it != bullets.end();)
   {
      if (*it) // DO NOT dereference NULL
         delete (*it);
      it = bullets.erase(it);
   }

   if (ship) // ensures not dereferencing NULL
      {
         delete ship;
         ship = NULL;
   }

}

/***************************************
 * GAME :: ADVANCE
 * advance the game one unit of time
 ***************************************/
void Game :: advance()
{
   //TODO: remove this for production
   bStartGame = true;
   if (bStartGame)
   {
   advanceBullets();
   advanceAsteroid();
   advanceShip();

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
      if (bullets[i]->isAlive())
      {
         // this bullet is alive, so tell it to move forward
         bullets[i]->advance();
         
         if (!isOnScreen(bullets[i]->getPoint()))
         {
            // the bullet has left the screen
            bullets[i]->kill();
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
 * 3. Check if the ship has gone of the screen, and if so, wrap it
 **************************************************************************/
void Game :: advanceShip()
{ 
   if (ship != NULL) // if ship exists advance
   {

      // we have a ship, make sure it's alive
      if (ship->isAlive())
      {
         // move it forward
         ship->advance();

      }
      //TODO: Should there be an else here???
              
   }

}

/**************************************************************************
 * GAME :: CREATE Asteroid
 * Create an Asteroid according to the rules of the game.
 **************************************************************************/
void Game :: createAsteroid()
{
    for (int i = 0; i < BEGGINNING_ASTEROID_COUNT; i++)
   {
      asteroids.push_back(new LargeAsteroid());
   }
   
}

void Game :: createMediumAsteroid(Point point, Velocity velocity)
{
   Velocity posVelocity, negVelocity, neutralVelocity;
   posVelocity = velocity;
   negVelocity = velocity;
   neutralVelocity = velocity;

   //TODO: more elegant solution , If positive or negative make positive or negative???
   posVelocity.setDy(posVelocity.getDy() + 1.0);
   negVelocity.setDy(posVelocity.getDy() - 1.0);
   neutralVelocity.setDx(neutralVelocity.getDx() + 1);

   asteroids.push_back(new MediumAsteroid(point, posVelocity));
   asteroids.push_back(new MediumAsteroid(point, negVelocity));
   asteroids.push_back(new SmallAsteroid(point, neutralVelocity));
}

void Game :: createSmallAsteroid(Point point, Velocity velocity)
{
   asteroids.push_back(new SmallAsteroid(point, velocity));
}
/**************************************************************************
 * GAME :: CREATE Ship
 * Create an ship according to the rules of the game.
 **************************************************************************/
Ship* Game :: createShip()
{

   Ship* ship = NULL;
   ship = new Ship();

   return ship;
   
}

/**************************************************************************
 * GAME :: CREATE Bullet
 * Create an bullet according to the rules of the game.
 **************************************************************************/
void Game :: createBullet()
{
   bullets.push_back(new Bullet(ship->getPoint(), ship->getOrientation(), ship->getVelocity()));
}

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
 * GAME :: GETCOLLISION
 * Determines if a 2 given points have collided
 **************************************************************************/
bool Game :: getCollision(const FlyingObject &obj1, const FlyingObject &obj2, int radius)
{
   bool isHit = false;
   //TODO: change 20.0 to a non magic number (radius of large asteroid)
   if (getClosestDistance(obj1, obj2) < radius)
   {
      isHit = true;
   }

   return isHit;
}

/**************************************************************************
 * GAME :: HANDLE COLLISIONS
 * Check for a collision between an asteroid and a bullet / ship
 **************************************************************************/
void Game :: handleCollisions()
{
   // loop through asteroids
   for (list<Asteroid *>::iterator it = asteroids.begin();
         it != asteroids.end(); it++)
   {
      // check if asteroid has been hit by bullet

      for (vector<Bullet *>::iterator it2 = bullets.begin() ; it2 != bullets.end(); ++it2)
      {
         // check if hit
         //TODO: change 10 to radius of rock
         if (getCollision(**it, **it2, (*it)->radius))
         {
            //check what type of rock is hit, by radius LRG = 16 MED = 8 SMLL = 4
            switch ((*it)->radius)
            {
               case 16:
                  explodeLarge(*it, *it2);
                  break;
               case 8:
                  explodeMedium(*it, *it2);
                  break;
               case 4:
                  explodeSmall(*it, *it2);
                  break;
            }             
         }
      }

      // check if ship has been hit
      if(ship != NULL && ship->isAlive())
      {
         if (getCollision(**it, *ship, (*it)->radius))
         {
            //ship->kill();
         }
      }

   }
   // get locations of objects
   //compare points and if closetDistance is less than .04 destroy
}

//If large asteroid call create meduim asteroids delete large asteroid
//If medium asteroid call create small asteroids delete medium asteroid
//If small asteroid delete

/**************************************************************************
 * GAME :: explodeLarge
 * Kills a large asteroid and creates 2 medium and 1 small asteroids
 **************************************************************************/
void Game :: explodeLarge(Asteroid *asteroid, Bullet *bullet)
{
   createMediumAsteroid(asteroid->getPoint(), asteroid->getVelocity());
   bullet->kill();
   asteroid->kill();
}

/**************************************************************************
 * GAME :: explodeMedium
 * Kills a mediuim asteroid and creates 2 small asteroids
 **************************************************************************/
void Game :: explodeMedium(Asteroid *asteroid, Bullet *bullet)
{
   Velocity posVelocity, negVelocity;
   posVelocity = asteroid->getVelocity();
   negVelocity = posVelocity;

   //TODO: more elegant solution , If positive or negative make positive or negative???
   posVelocity.setDy(posVelocity.getDy() + 3);
   negVelocity.setDy(negVelocity.getDy() - 3);

   createSmallAsteroid(asteroid->getPoint() , posVelocity);
   createSmallAsteroid(asteroid->getPoint() , negVelocity);

   bullet->kill();
   asteroid->kill();

}

/**************************************************************************
 * GAME :: explodeSmall
 * Kills a small asteroid and deletes the asteroid / bullet
 **************************************************************************/
void Game :: explodeSmall(Asteroid *asteroid, Bullet *bullet)
{
   bullet->kill();
   asteroid->kill();
}

/**************************************************************************
 * GAME :: CLEAN UP ZOMBIES
 * Remove any dead objects (take bullets out of the list, deallocate asteroids)
 **************************************************************************/
void Game :: cleanUpZombies()
{
   // Look for dead ship
    if (ship != NULL && !ship->isAlive())
   {
      // the ship is dead, but the memory is not freed up yet

      delete ship;
      ship = NULL;

   }

   // Look for dead bullets
   vector<Bullet *>::iterator bulletIt = bullets.begin();
   while (bulletIt != bullets.end())
   {
      Bullet* pBullet = *bulletIt;
      // Asteroids Hint:
      // If we had a list of pointers, we would need this line instead:
      //Bullet* pBullet = *bulletIt;
      
      if (!pBullet->isAlive())
      {
         // If we had a list of pointers, we would need to delete the memory here...
         delete pBullet;
         pBullet = NULL;
         
         // remove from list and advance
         bulletIt = bullets.erase(bulletIt);
      }
      else
      {
         bulletIt++; // advance
      }
   }

   //look for dead asteroids
   list<Asteroid *>::iterator asteroidIt = asteroids.begin();
   while (asteroidIt != asteroids.end())
   {
      Asteroid* pAsteroid = *asteroidIt;
    
      if (!pAsteroid->isAlive())
      {
         // If we had a list of pointers, we would need to delete the memory here...
         delete pAsteroid;
         pAsteroid = NULL;
         
         // remove from list and advance
         asteroidIt = asteroids.erase(asteroidIt);
      }
      else
      {
         asteroidIt++; // advance
      }
   }
}

/***************************************
 * GAME :: HANDLE INPUT
 * accept input from the user
 ***************************************/
void Game :: handleInput(const Interface & ui)
{
   if (ship != NULL && ship->isAlive())
   {
      // Change the direction of the ship left
      // if (ui.isLeft())
      // {
         ship->moveLeft();
      // }
      
      // Change the direction of the ship right
      if (ui.isRight())
      {
         ship->moveRight();
      }

      // Check for "up" key
      if (ui.isUp())
      {
         ship->moveUp();
      }

      // Check for "Spacebar"
      // if (ui.isSpace())
      // {
         createBullet();
      // }

      // Check for "Y" press
      if (ui.isY())
      {
         bStartGame = true;
   	 std::cout
            << "time ellapsed: "
      	    << this->benchmark.ellapsedReal << "ms"
	    << " (cpu time:" 
	    << this->benchmark.ellapsedCpu << "ms)"
            << "\nframes rendered: "
            << this->benchmark.frameCount
	    << std::endl;
      }
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
           {
              if ((*it)->isAlive())
              {
                 (*it)->draw();
              }
           }
         

   // draw the ship
   if (ship != NULL && ship->isAlive()) 
   {
      ship->draw();
   }
   
   // draw the bullets, if they are alive
   for (int i = 0; i < bullets.size(); i++)
   {
      if (bullets[i]->isAlive())
      {
         bullets[i]->draw();
         bullets[i]->setHealth();
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
