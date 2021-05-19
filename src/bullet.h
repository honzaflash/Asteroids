/***********************************************************************
 * Header File:
 *    Point : The representation of a bullet on the screen
 * Author:
 *    Jason Halverson
 * Summary:
 *    Everything we need to know about a bullet on the screen
 ************************************************************************/

#ifndef BULLET_H
#define BULLET_H

#include "velocity.h"
#include "uiDraw/point.h"
#include "flyingObject.h"

class Bullet : public FlyingObject
{
public:
    // constructors
    Bullet();
    Bullet(Point shipPoint, float shipOrientation, Velocity shipVelocity);
    void draw();
    void fire(Point point, float angle, Velocity velocity);
    void setStartingDx();
    int getHealth();
    void setHealth();

private:
    int health;
};

#endif