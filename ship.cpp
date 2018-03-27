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
   setOrientation(0);
   currentPoint.setX(0);
   currentPoint.setY(0);
   setPoint(currentPoint);
   draw();
}

/***********************************************************************
 * draws the ship
***********************************************************************/
void Ship :: draw()
{
   drawShip(currentPoint, 200);
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

//TODO: checks for if under 0 or over 360
void Ship :: moveLeft()
{
   orientation += ROTATE_AMOUNT;

}


void Ship :: moveRight()
{
   orientation -= ROTATE_AMOUNT;
   
}