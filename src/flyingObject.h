/***********************************************************************
 * Header File:
 *    Point : Base clase for all flying objects
 * Author:
 *    Jason Halverson
 * Summary:
 *    Everything we need to know about flying objects on the screen
 ************************************************************************/

#ifndef flyingObject_H
#define flyingObject_H

#include "uiDraw/point.h"
#include "velocity.h"

class FlyingObject
{
public:
    // Constructor
    FlyingObject();

    Point getPoint() const;
    Velocity getVelocity() const;
    bool isAlive() const;
    void setPoint(Point point);
    void setPoint(float x, float y);
    void setVelocity(Velocity velocity);
    void setVelocity(float dx, float dy);
    void advance();
    void kill();
    virtual void draw();
    virtual void setStartingDx();
    virtual void setStartingDy();
    int getRotation();
    void setRotation(int rotation);
    int radius;

protected:
    bool alive;
    Point currentPoint;
    Velocity velocity;
    Point startingPoint;
    // gets random number for starting point
    float startingX;
    float startingDx;
    float startingDy;
    int rotation;
    bool isWrapX;
    bool isWrapY;
};

#endif