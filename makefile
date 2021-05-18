###############################################################
# Program:
#     Milestone 12, Asteroids
#     Brother Alvey, CS165
# Author:
#     Jason Halverson
# Summary:
#     For this milestone you should have:
#	Collisions between bullets and rocks
#	Collisions between the ship and rocks
#	Rocks correctly breaking apart when hit
#Memory correctly cleaned up when rocks and/or bullets are destroyed
#
# Above and Beyond
#     When you submit your final project (not for milestones),
#     list anything here that you did to go above and beyond
#     the base requirements for your project.
###############################################################


LFLAGS = -lglut -lGLU -lGL

###############################################################
# Build the main game
###############################################################
a.out: driver.o game.o uiInteract.o uiDraw.o point.o velocity.o flyingObject.o ship.o bullet.o asteroids.o
	g++ -pg driver.o game.o uiInteract.o uiDraw.o point.o velocity.o flyingObject.o ship.o bullet.o asteroids.o $(LFLAGS)

###############################################################
# Individual files
#    uiDraw.o       Draw polygons on the screen and do all OpenGL graphics
#    uiInteract.o   Handles input events
#    point.o        The position on the screen
#    game.o         Handles the game interaction
#    velocity.o     Velocity (speed and direction)
#    flyingObject.o Base class for all flying objects
#    ship.o         The player's ship
#    bullet.o       The bullets fired from the ship
#    asteroids.o        Contains all of the Asteroid classes
###############################################################
uiDraw.o: uiDraw.cpp uiDraw.h
	g++ -pg -c uiDraw.cpp

uiInteract.o: uiInteract.cpp uiInteract.h
	g++ -pg -c uiInteract.cpp

point.o: point.cpp point.h
	g++ -c point.cpp

driver.o: driver.cpp game.h
	g++ -pg -c driver.cpp

game.o: game.cpp game.h uiDraw.h uiInteract.h point.h velocity.h flyingObject.h bullet.h asteroids.h ship.h
	g++ -pg -c game.cpp

velocity.o: velocity.cpp velocity.h point.h
	g++ -c velocity.cpp

flyingObject.o: flyingObject.cpp flyingObject.h point.h velocity.h uiDraw.h
	g++ -pg -c flyingObject.cpp

ship.o: ship.cpp ship.h flyingObject.h point.h velocity.h uiDraw.h
	g++ -pg -c ship.cpp

bullet.o: bullet.cpp bullet.h flyingObject.h point.h velocity.h uiDraw.h
	g++ -pg -c bullet.cpp

asteroids.o: asteroids.cpp asteroids.h flyingObject.h point.h velocity.h uiDraw.h
	g++ -pg -c asteroids.cpp


###############################################################
# General rules
###############################################################
clean:
	rm a.out *.o
