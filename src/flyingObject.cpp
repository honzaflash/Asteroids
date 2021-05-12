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
   isWrapX = false; //!! unnecessary
   isWrapY = false; //!! unnecessary
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

void FlyingObject :: setPoint(float x, float y)
{
   currentPoint.setX(x);
   currentPoint.setY(y);
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

// !! wraps the object, isWrap should become unnecessary if
// if '=' is omitted from comparisons
void FlyingObject :: advance()
{
   //TODO: clean up logic
   // Checks if the flyingObject needs to wrap around 
   // the screen
   if (!isWrapX && (currentPoint.getX() >= 200))
   {
      currentPoint.setX(-200);
      currentPoint.addX(velocity.getDx());
      currentPoint.addY(velocity.getDy());
      isWrapX = true;
   }
   else if (!isWrapX && currentPoint.getX() <= -200)
   {
      currentPoint.setX(200);
      currentPoint.addX(velocity.getDx());
      currentPoint.addY(velocity.getDy());
      isWrapX = true;
   }
   else if (!isWrapY && currentPoint.getY() >= 200)
   {
      currentPoint.setY(-200);
      currentPoint.addX(velocity.getDx());
      currentPoint.addY(velocity.getDy());
      isWrapY = true;
   }
   else if (!isWrapY && currentPoint.getY() <= -200)
   {
      currentPoint.setY(200);
      currentPoint.addX(velocity.getDx());
      currentPoint.addY(velocity.getDy());
      isWrapY = true;
   }
   else
   {
      currentPoint.addX(velocity.getDx());
      currentPoint.addY(velocity.getDy());
      isWrapX = false;
      isWrapY = false;
   }
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
