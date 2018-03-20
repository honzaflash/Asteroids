/*************************************************************
 * File: ship.cpp
 * Author: Jason Halverson
 *
 * Description: Contains the implementations of the
 *  method bodies for the ship class.
 *
 *************************************************************/

#include "ship.h"
#include "uiDraw.h"

// Put your ship methods here
/***********************************************************************
 * Default constructor for the ship class
***********************************************************************/
Ship :: Ship()
{
   //TODO: clean up initiliazation of location
   currentPoint.setX(0);
   currentPoint.setY(0);
   setPoint(currentPoint);
}

/***********************************************************************
 * draws the ship
***********************************************************************/
void Ship :: draw()
{
   drawShip(currentPoint, rotation);
}

/***********************************************************************
 * sets the ships orientation
***********************************************************************/
void Ship :: setOrientation(float orientation)
{
   this->orientation = orientation;
}

/***********************************************************************
 * gets the ships orientation
************************************************************************/
float Ship :: getOrientation()
{
   return orientation;
}

void Ship :: moveLeft()
{
   angle -= ROTATE_AMOUNT;

   if (angle < ANGLE_MIN)
   {
      angle = ANGLE_MIN;
   }
}


void Ship :: moveRight()
{
   angle += ROTATE_AMOUNT;
   
   if (angle > ANGLE_MAX)
   {
      angle = ANGLE_MAX;
   }
}