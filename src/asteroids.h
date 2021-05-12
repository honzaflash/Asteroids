/***********************************************************************
 * Header File:
 *    Point : The representation of an asteroid on the screen
 * Author:
 *    Jason Halverson
 * Summary:
 *    Everything we need to know about an asteroid on the screen
 ************************************************************************/

#ifndef asteroids_h
#define asteroids_h

#include "flyingObject.h"
#include "point.h"
#include "uiDraw/uiDraw.h"

#define BIG_ROCK_SIZE 16
#define MEDIUM_ROCK_SIZE 8
#define SMALL_ROCK_SIZE 4

#define BIG_ROCK_SPIN 2
#define MEDIUM_ROCK_SPIN 5
#define SMALL_ROCK_SPIN 10

class Asteroid: public FlyingObject
{
   public:
      Asteroid();
      // accept a starting point and velocity
      Asteroid(Point point, Velocity velocity);
      float getAngle();
      void setAngle(float angle);


      //TODO: return richer data
      bool getHit();
      void setHit(bool hit);

      virtual void split(bool hit);

   protected:
      float angle;
      int rotation;
      bool hit;

   private:
};

/***********************************************************************
 * LargeAsteroid declarations
***********************************************************************/
class LargeAsteroid: public Asteroid
{
   public:
      LargeAsteroid();
      LargeAsteroid(Point point, Velocity velocity);
      // accept a random initial point and velocity
      void split(bool hit);
      void draw();
      

   protected:

   private:
      void setStartingDx();
      void setStartingDy();

};

/***********************************************************************
 * MediumAsteroid declarations
***********************************************************************/
class MediumAsteroid: public Asteroid
{
   public:
      MediumAsteroid();
      MediumAsteroid(Point point, Velocity Velocity);
      void split(bool hit);
      void draw();

   protected:

   private:

};

/***********************************************************************
 * SmallAsteroid declarations
***********************************************************************/
class SmallAsteroid: public Asteroid
{
   public:
      SmallAsteroid();
      SmallAsteroid(Point point, Velocity Velocity);
      void split(bool hit);
      void draw();
      
   protected:

   private:

};


#endif /* asteroids_h */
