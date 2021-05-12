/***********************************************************************
 * Header File:
 *    Point : The representation of a ship on the screen
 * Author:
 *    Jason Halverson
 * Summary:
 *    Everything we need to know about a ship on the screen
 ************************************************************************/

#ifndef ship_h
#define ship_h

#include "velocity.h"
#include "point.h"
#include "flyingObject.h"

#define SHIP_SIZE 10

#define ROTATE_AMOUNT 6
#define THRUST_AMOUNT 0.5

#define ANGLE_MAX 180
#define ANGLE_MIN -180
#define ANGLE_START 90



class Ship: public FlyingObject 
{
   public:

   // constructors
   Ship();
   
   void draw();
   void setOrientation(float orientation);
   float getOrientation();

   /*****************
    * Movement
    *****************/
   void moveLeft();
   void moveRight();
   void moveUp();

   protected:

private:

   Point point; // !! seems unused
   bool thrust;

      /**********************************************************
      * angle - The angle of the ship in degrees.
      *  Assumes that straight right is 0 degrees and up is 90.
      **********************************************************/
   float orientation;
};




#endif /* ship_h */
