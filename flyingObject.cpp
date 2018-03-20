/*************************************************************
 * File: FlyingObject.cpp
 * Author: Jason Halverson
 *
 * Description: Contains the implementations of the
 *  method bodies for the FlyingObject class.
 *
 *************************************************************/

#include "flyingObject.h"

/***********************************************************************
 * default constructo
***********************************************************************/
FlyingObject :: FlyingObject()
{
   // Set alive and default rotation to 0
   alive = true;
   setRotation(0);
}

Point FlyingObject :: getPoint() const
{
   return currentPoint;
}

Velocity FlyingObject:: getVelocity() const
{
   return velocity;
}

bool FlyingObject :: isAlive() const
{
   return alive;
}

void FlyingObject :: setPoint(Point point)
{
   this->currentPoint = point;
}

void FlyingObject :: setVelocity(Velocity velocity)
{
   this->velocity = velocity;
}

void FlyingObject :: setVelocity(float dx, float dy)
{
   velocity.setDx(dx);
   velocity.setDy(dy);
}

void FlyingObject :: advance()
{
   currentPoint.addX(velocity.getDx());
   currentPoint.addY(velocity.getDy());
}

void FlyingObject :: kill()
{
   alive = false;
}

void FlyingObject :: draw()
{

}

void FlyingObject :: setStartingDx()
{

}

void FlyingObject :: setStartingDy()
{

}

/***********************************************************************
 * this will get the FlyingObjects rotation
***********************************************************************/
int FlyingObject :: getRotation()
{
   return rotation;
}

/***********************************************************************
 * this will set the FlyingObjects rotation
***********************************************************************/
void FlyingObject :: setRotation(int rotation)
{
   this->rotation = rotation;
}
