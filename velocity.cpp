/*************************************************************
 * File: velocity.cpp
 * Author: Jason Halverson
 *
 * Description: Contains the implementations of the
 *  method bodies for the velocity class.
 *
 *************************************************************/
#include "velocity.h"

// constructors
Velocity :: Velocity()
{

}
Velocity :: Velocity(float dX, float dY)
{

}

float Velocity :: getDx() const
{
   return dX;
}

float Velocity :: getDy() const
{
   return dY;
}

void Velocity :: setDx(float dX)
{
   this->dX = dX;
}

void Velocity :: setDy(float dY)
{
   this->dY = dY;
}