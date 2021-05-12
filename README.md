# Asteroids Organized

This is a "read-only" branch with file structure reorganization
and subtle refactoring for better understandability.
It might not compile.

# Original readme

## Asteroids

Introduced by Atari in 1979, Asteroids was one of the most successful of the first generation of arcade games and was highly influential on the video game landscape for the next decade. The basic premise of the game is that a ship moves around the screen shooting asteroids while trying not to get hit by them.
This program is written using simplified OpenGL libraries . OpenGL will have to be installed and enabled on your machine for this program to work.

### Game Rules and Specification

<ol>
  <li>Ship</li>
    <ul>
      <li>The ship obeys the laws of motion. When in motion, the ship will tend to stay in motion.</li>
      <li>Note that the angle or orientation of the ship can be different than the direction it is traveling.</li>
      <li>The right and left arrows rotate the ship 6 degrees to either direction.</li>
      <li>The up arrow will increase the velocity in the direction the ship is pointed by 0.5 pixels/frame.</li>
      <li>For collision detection, the ship is a circle of radius 10.</li>
    </ul>
  
  <li>Bullets</li>
    <ul>
      <li>Pressing space bar will shoot a bullet.</li>
      <li>Bullets start with the same velocity of the ship (speed and direction) plus 5 pixels per frame in the direction the ship is pointed. This means if the ship is traveling straight up, but pointed directly to the right, the bullet will have a velocity that is at an angle up and to the right (starting with an upward velocity from the ship, and adding to it a velocity to the right because of the direction the ship is pointed).</li>
      <li>There is no limit to the number of bullets that can be fired.</li>
      <li>Bullets only live for 40 frames, after which they "die" and are removed from the game.</li>
    </ul>
  
  <li>Asteroids - There are 3 types of asteroids in the game:</li>
    <ol>
      <li>Large Asteroids</li>
        <ul>
          <li>Moves at 1 pixel per frame, with a random initial angle.</li>
          <li>Rotates at 2 degrees per frame.</li>
          <li>For collision detection, they have a circle with radius 16.</li>
          <li>If a large asteroid gets hit, it breaks apart and becomes two medium asteroids and one small one.</li>
          <li>The first medium asteroid has the same velocity as the original large one plus 1 pixel/frame in the up direction.</li>
          <li>The second medium asteroid has the same velocity as the original large one plus 1 pixel/frame in the down direction.</li>
          <li>The small asteroid has the original velocity plus 2 pixels/frame to the right.</li>
        </ul>  
      <li>Medium Asteroid</li>
        <ul>
          <li>Rotates at 5 degrees per frame.</li>
          <li>For collision detection, they have a circle with radius 8.</li>
          <li>If hit, it breaks apart and becomes two small asteroids.</li>
          <li>The small asteroid has the same velocity as the original medium one plus 3 pixel/frame to the right.</li>
          <li>The second, 3 pixels/frame to the left.</li>
        </ul>
      <li>Small Asteroid</li>
        <ul>
          <li>Rotates at 10 degrees per frame.</li>
          <li>For collision detection, they have a circle with radius 4.</li>
          <li>If a small asteroid is hit, it is destroyed and removed from the game.</li>
        </ul>
    </ol>
    
    
  <li>Other game rules</li>
    <ul>
      <li>The game begins with 5 large asteroids.</li>
      <li>All elements (ship, bullets, asteroids) "wrap" around the edges of the screen. In other words, if an object goes off the right edge of the screen, it should appear on the left edge.</li>
      <li>The dimensions of the window are: (-200, -200) to (200, 200).</li>
    </ul>
</ol>

### Architectural Design
The entire program is implemented using the principles of encapsulation. The principles of inheritance and polymorphism. 
