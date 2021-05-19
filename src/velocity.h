/***********************************************************************
 * Header File:
 *    Velocity : Lander Velocity
 * Author:
 *    Jason Halverson
 * Summary:
 *    Everything we need to know about game velocity
 ************************************************************************/

#ifndef VELOCITY_H
#define VELOCITY_H

class Velocity
{
private:
    float velocity;
    float dX;
    float dY;

public:
    float getDx() const;
    float getDy() const;
    void setDx(float dX);
    void setDy(float dY);

    // constructors
    Velocity();
    Velocity(float dX, float dY);
};

#endif