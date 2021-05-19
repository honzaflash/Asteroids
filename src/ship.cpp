/*************************************************************
 * File: ship.cpp
 * Author: Jason Halverson
 *
 * Description: Contains the implementations of the
 *  method bodies for the ship class.
 *
 *************************************************************/

#include "ship.h"
#include "uiDraw/uiDraw.h"

// Put your ship methods here
/***********************************************************************
 * Default constructor for the ship class
***********************************************************************/
Ship ::Ship()
{
    //TODO: clean up initiliazation of location
    setOrientation(0);
    currentPoint.setX(0);
    currentPoint.setY(0);
    // setPoint(currentPoint); !! setting currentPoint to currentPoint
    draw();
}

/***********************************************************************
 * draws the ship
***********************************************************************/
void Ship ::draw()
{
    drawShip(currentPoint, orientation, thrust);
    thrust = false;
}

/***********************************************************************
 * sets the ships orientation
***********************************************************************/
void Ship ::setOrientation(float orientation)
{
    this->orientation = orientation;
}

/***********************************************************************
 * gets the ships orientation
************************************************************************/
float Ship ::getOrientation()
{
    return orientation;
}

void Ship ::moveLeft()
{
    if (orientation < 0)
    {
        orientation = 359;
    }
    else if (orientation > 360)
    {
        orientation = 0;
    }
    else
    {
        orientation += ROTATE_AMOUNT;
    }
}

void Ship ::moveRight()
{
    if (orientation < 0)
    {
        orientation = 359;
    }
    else if (orientation > 360)
    {
        orientation = 0;
    }
    else
    {
        orientation -= ROTATE_AMOUNT;
    }
}

void Ship ::moveUp()
{
    thrust = true;
    float angle = getOrientation();
    float dx = velocity.getDx() + (0.1 * (cos(M_PI / 180.0 * (angle + 90))));
    float dy = velocity.getDy() + (0.1 * (sin(M_PI / 180.0 * (angle + 90))));
    velocity.setDx(dx);
    velocity.setDy(dy);
}
