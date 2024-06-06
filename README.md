# Space Rocket Game

## Overview
The Space Rocket Game is an engaging 2D game built using GLUT (OpenGL Utility Toolkit) and OpenGL. Players navigate a rocket using their mouse, shooting laser beams to destroy asteroids of matching colors. The game includes a scoring system, a timer, and a restart option for replayability.

## Features
- **Mouse Controls**: Navigate the rocket by moving the mouse.
- **Laser Beams**: Shoot laser beams with different colors by pressing the space bar.
- **Asteroids**: Destroy 25 randomly spawning asteroids with matching color laser beams to earn points.
- **Timer**: A 20-second countdown timer.
- **Score Display**: Keep track of your score.
- **Restart Option**: Restart the game by pressing the F1 key.

## Requirements
- OpenGL
- GLUT

## Installation
1. Ensure you have OpenGL and GLUT installed on your system.
2. Download the source code files.

## Running the Game
1. Compile the source code using a compatible C++ compiler with OpenGL and GLUT support.
2. Run the compiled executable.

## Controls
- **Mouse**: Move the rocket.
- **Space Bar**: Change the color of the laser beam.
- **F1**: Restart the game.

## Code Structure
- **LaserBeam Class**: Manages the properties and behavior of the laser beam.
- **SpaceRocket Class**: Manages the properties and behavior of the space rocket.
- **Asteroid Class**: Manages the properties and behavior of the asteroids.

## Functions
- **void keyboard(unsigned char key, int x, int y)**: Handles keyboard inputs to change the laser color.
- **void timer(int value)**: Manages the countdown timer.
- **void reset()**: Resets the game state for a new game.
- **void specialKeyboard(int key, int x, int y)**: Handles special keyboard inputs for restarting the game.
- **void mouse(int x, int y)**: Updates the rocket and laser positions based on mouse movements.
- **void moveAsteroids(int value)**: Updates the positions of the asteroids.
- **void checkCollision(Asteroid& asteroid, LaserBeam& laser)**: Checks and handles collisions between laser beams and asteroids.
- **void drawStars()**: Draws the background stars.
- **void drawText()**: Displays the timer and final score text.
- **void drawScore()**: Displays the current score.
- **void asteroidTimer(int value)**: Spawns asteroids at intervals.
- **void display()**: Renders all game elements on the screen.

## Example Code Snippet
```cpp
void mouse(int x, int y) {
    mouseX = x;
    mouseY = y;

    float newX = -1.0f + (2.0f * mouseX) / windowWidth;
    float newY = -1.0f + (2.0f * mouseY) / windowWidth;

    rocket.updatePosition(newX, newY);
    laser.updatePosition(newX, newY);

    glutPostRedisplay();
}
```

## Acknowledgements
- Developed using OpenGL and GLUT.
