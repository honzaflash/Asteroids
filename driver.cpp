/*****************************************************
 * File: Driver.cpp
 * Author: Br. Burton
 *
 * Description: This file contains the main function
 *  that starts the game and the callback function
 *  that specifies what methods of the game class are
 *  called each time through the game loop.
 ******************************************************/
#include <iostream>
#include <ctime>
#include "game.h"
#include "uiInteract.h"



long timeDiff( struct timespec start, struct timespec end ) {
   long s = start.tv_sec * 1000 + start.tv_nsec / 1000000;
   long e = end.tv_sec * 1000 + end.tv_nsec / 1000000;
   return e - s;
}


/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(const Interface *pUI, void *p)
{
   Game *pGame = (Game *)p;
   

   pGame->advance();
   pGame->handleInput(*pUI);
   pGame->draw(*pUI);
   
   struct timespec now;
   clock_gettime(CLOCK_REALTIME, &now);
   long ellapsedReal = timeDiff(pGame->benchmark.realStart, now);
   clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &now);
   long ellapsedCpu = timeDiff(pGame->benchmark.cpuStart, now);

   pGame->benchmark.incr(ellapsedReal, ellapsedCpu);
}


/*********************************
 * Main is pretty sparse.  Just initialize
 * the game and call the display engine.
 * That is all!
 *********************************/
int main(int argc, char ** argv)
{
   Point topLeft(-200, 200);
   Point bottomRight(200, -200);
   
   Interface ui(argc, argv, "Asteroids", topLeft, bottomRight);
   Game game(topLeft, bottomRight);
   
   clock_gettime(CLOCK_REALTIME, &(game.benchmark.realStart));
   clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &(game.benchmark.cpuStart));

   ui.run(callBack, &game);
   
   return 0;
}
