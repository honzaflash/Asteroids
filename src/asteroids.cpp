/*************************************************************
 * File: asteroids.cpp
 * Author: Jason Halverson
 *
 * Description: Contains the implementations of the
 *  method bodies for the asteroids classes.
 *
 *************************************************************/

#include "asteroids.h"

#define RANDOM_Y_MIN -180
#define RANDOM_Y_MAX 180
#define RANDOM_DX_MIN 3.0
#define RANDOM_DX_MAX 6.0
#define RANDOM_DY_MIN -3.0
#define RANDOM_DY_MAX 3.0

/***********************************************************************
 * Asteroid class definitions
***********************************************************************/
// constructors

Asteroid :: Asteroid()
{
   //TODO: set function for random starting points
   currentPoint.setX(random(-180,180));
   currentPoint.setY(random(-180,180));
   setPoint(currentPoint);

//TODO: change random angle , and ensure asteroid is moving at 1px per
//frame per the instructions
   velocity.setDx(random(-1.0,1.0));
   velocity.setDy(random(-1.0,1.0));
   setRotation(random(-180,180));

}


// Put your Asteroid methods here

/***********************************************************************
 * this will get the asteroids angle
***********************************************************************/
float Asteroid :: getAngle()
{
   return angle;
}

/***********************************************************************
 * this will set the asteroids angle
***********************************************************************/
void Asteroid :: setAngle(float angle)
{
   this->angle = angle;
}


/***********************************************************************
 * this will get if an asteroid is hit by bullet
***********************************************************************/
bool Asteroid :: getHit()
{
   return hit;
}

/***********************************************************************
 * this will set if an asteroid is hit by bullet
***********************************************************************/
void Asteroid :: setHit(bool hit)
{
   this->hit = hit;
}

/***********************************************************************
 * virtual function for the split method
 * this will create new asteroid when hit
***********************************************************************/
void Asteroid :: split(bool hit)
{

}

/***********************************************************************
 * LargeAsteroid class definitions
***********************************************************************/

/***********************************************************************
 * 
***********************************************************************/
LargeAsteroid :: LargeAsteroid()
{
   //TODO set function for random rotation
   setRotation(2);
   radius = 16;
}

void LargeAsteroid :: setStartingDx()
{
   startingDx = random(RANDOM_DX_MIN, RANDOM_DX_MAX);
}

void LargeAsteroid :: setStartingDy()
{
   startingDy = random(RANDOM_DY_MIN, RANDOM_DY_MAX);
}
/***********************************************************************
 * 
***********************************************************************/
void LargeAsteroid :: split(bool hit)
{
   
}

/***********************************************************************
 * 
***********************************************************************/
void LargeAsteroid :: draw()
{
   drawLargeAsteroid(currentPoint, rotation);
   rotation += BIG_ROCK_SPIN;
}

/***********************************************************************
 * MediumAsteroid class definitions
***********************************************************************/

/***********************************************************************
 * 
***********************************************************************/
MediumAsteroid :: MediumAsteroid()
{
   setRotation(5);
   radius = 8;
}

MediumAsteroid :: MediumAsteroid(Point point, Velocity Velocity)
{
   radius = 8;
   setPoint(point);
   setVelocity(velocity);
}
/***********************************************************************
 * 
***********************************************************************/
void MediumAsteroid :: split(bool hit)
{

}

/***********************************************************************
 * 
***********************************************************************/
void MediumAsteroid :: draw()
{
   rotation += MEDIUM_ROCK_SPIN;
   drawMediumAsteroid(currentPoint, rotation);
   
}

/***********************************************************************
 * SmallAsteroid class definitions
***********************************************************************/

/***********************************************************************
 * 
***********************************************************************/
SmallAsteroid :: SmallAsteroid()
{

}

SmallAsteroid :: SmallAsteroid(Point point, Velocity Velocity)
{
   radius = 4;
   setPoint(point);
   setVelocity(velocity);
}
/***********************************************************************
 * 
***********************************************************************/
void SmallAsteroid :: split(bool hit)
{

}

/***********************************************************************
 * 
***********************************************************************/
void SmallAsteroid :: draw()
{
   rotation += SMALL_ROCK_SPIN;
   drawSmallAsteroid(currentPoint, rotation);
}
