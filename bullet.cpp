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

#define BULLET_SPEED 10.0
#define M_PI 3.14159265358979323846

/***********************************************************************
 * 
***********************************************************************/
Bullet :: Bullet()
{

}

/***********************************************************************
 * 
***********************************************************************/
void Bullet :: draw()
{
   drawDot(currentPoint);
}

/***********************************************************************
 * 
***********************************************************************/
void Bullet :: fire(Point point, float angle)
{
   float dx = BULLET_SPEED * (-cos(M_PI / 180.0 * angle));
   float dy = BULLET_SPEED * (sin(M_PI / 180.0 * angle));
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
void Bullet :: setHealth(int health)
{
   this->health = health;
}