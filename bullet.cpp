/*************************************************************
 * File: bullet.cpp
 * Author: Jason Halverson
 *
 * Description: Contains the implementations of the
 *  method bodies for the bullet class.
 *
 *************************************************************/
#include <cmath> // used for sin, cos, and M_PI
#include "bullet.h" 
#include "uiDraw.h"

#define BULLET_SPEED 5.0
#define M_PI 3.14159265358979323846

/***********************************************************************
 * 
***********************************************************************/
Bullet :: Bullet()
{
   health = 40;
}

Bullet :: Bullet(Point shipPoint, float shipOrientation, Velocity shipVelocity)
{
   health = 40;
   fire(shipPoint, shipOrientation, shipVelocity);
}

/***********************************************************************
 * 
***********************************************************************/
void Bullet :: draw()
{
   drawDot(currentPoint);
}

/***********************************************************************
 * Fire the bullet
***********************************************************************/
void Bullet :: fire(Point point, float angle, Velocity velocity)
{
   float dx = BULLET_SPEED * (cos(M_PI / 180.0 * (angle + 90))) + velocity.getDx();
   float dy = BULLET_SPEED * (sin(M_PI / 180.0 * (angle  + 90))) + velocity.getDy();

   setPoint(point);
   setVelocity(dx, dy);
}

/***********************************************************************
 * 
***********************************************************************/
void Bullet :: setStartingDx()
{}

/***********************************************************************
 * gets the current health of bullet
***********************************************************************/
int Bullet :: getHealth()
{
   return health;
}

/***********************************************************************
 * sets the current health of bullet
***********************************************************************/
void Bullet :: setHealth()
{
   if (health > 0)
   {
      health -= 1;
   }
   else
   {
      kill();
   }
   

}