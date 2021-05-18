# Asteroids

this is the benchmarking branch

it contains an altered version of the upstream Asteroids clone by Jason Halverson

100 asteroids is spawned, ship spins and shoots a bullet per frame

F1 can be pressed to print current ellapsed time and frames rendered so far
(the glutMainLoop never returns, therfore
I decided for this quick hack that kinda solves it)

`BEGGINNING_ASTEROID_COUNT` in game.cpp constant can be changed to any other number than 100

