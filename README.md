# Pac-Man Game
 This is the capstone project for Udacity C++ Nanodegree. The code was inspired by [this](https://github.com/Kofybrek/Pacman) creative game repo and [this](https://github.com/udacity/CppND-Capstone-Snake-Game) Udacity 2D Snake game repo. I also found good guidelines from [this](https://lazyfoo.net/tutorials/SDL/) game programming with SDL tutorials and Udacity C++ Nanodegree lessons (especially A* search algorithm).

In this project, I built my own C++ application from scratch following the principles I learned throughout the Nanodegree Program. I chose to make a simple version of the classic arcade game (Pac-Man). Pac-Man is controlled by the player who directs him throughout the maze to eat all the dots while avoiding the ghost. If Pac-Man ate an energizer, the ghost turns blue for a short while and Pac-Man can eat the ghost during this period and earn bonus points. The player loses if the ghost eats Pac-Man. To win this game: use arrow keys to move your character, Don't get caught, and eat all the dots on the ground.

## Dependencies for Running Locally
* cmake: version 3.26.4
  - All OSes: [click here for installation instructions](https://cmake.org/install/)
* SDL2: version 2.26.5
  - All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
* gcc/g++: version 12.2.0
  - Windows: recommend using [MinGW](http://www.mingw.org/)
* IDE: Visual Studio 2019 Community Edition
  - Latest version can be found [here](https://visualstudio.microsoft.com/vs/community/)
* SDL_ttf Library: version 2.20.2
  - You can get it from [here](https://github.com/libsdl-org/SDL_ttf/releases)

## Basic Build Instructions
1. Clone this repo.
2. Open the Visual Studio Solution "Pac-Man.sln"
3. Make sure all the above-mentioned dependencies are set properly
4. Build the project (Ctrl + B)
5. Run the game (Ctrl + F5)

## Project Structure
* The source code consists of a main file called "Pac-Man.cpp" along with 4 other classes implemented in both .h and .cpp files.
  - Renderer files manages the GUI.
  - Game files controls the game flow.
  - Pacman files manages Pac-Man's movement and interactions.
  - Ghost files manages ghost's behaviour.
* Running this game excutes a game window with playground map and an external player controls for winning.

## Rubric Points Addressed
* The project demonstrates an understanding of C++ functions and control structures.
  - Functions:
    - File: Pac-Man.cpp ~ line: 8.
    - File: Renderer.h ~ lines: 21 -> 27.
    - File: Game.h ~ lines: 14 -> 17.
    - File: Pacman.h ~ lines: 16, 23 -> 27.
    - File: Ghost.h ~ lines: 22 -> 26.
  - Control structures:
    - File: Renderer.cpp ~ lines: 8, 11, 16, 19, 23, 29, 34, 75, 76, 77, 103, 104, 113, 120, 121, 122, 131, 132, 133, 161, 168, 180, 184, 215, 220, 253, 258.
    - File: Game.cpp ~ lines: 17, 20, 21, 29,, 30, 31, 35, 39, 43, 59, 71, 72, 79, 81, 82, 85, 87, 92.
    - File: Pacman.cpp ~ lines: 14, 15, 16, 34, 36, 38, 40, 44, 52, 54.
    - File: Ghost.cpp ~ lines: 8, 11, 23, 24, 25, 35, 44, 48, 54, 68, 69, 70, 73, 89, 103, 109, 110, 111, 122, 123, 125, 128, 129, 131, 146, 154, 156, 160, 171, 177, 183, 184, 193, 194, 203, 205, 210, 214, 220, 227, 230, 232, 233, 241, 249, 250.
* The project accepts user input and processes the input.
  - File: Pacman.cpp ~ lines: 34 -> 47.
* The project uses Object Oriented Programming techniques.
  - File: Renderer.h ~ lines: 19 -> 35.
  - File: Game.h ~ lines: 12 -> 27.
  - File: Pacman.h ~ lines: 21 -> 33.
  - File: Ghost.h ~ lines: 20 -> 40.
* Class constructors utilize member initialization lists.
  - File: Renderer.cpp ~ lines: 5 -> 6.
  - File: Game.cpp ~ lines: 3 -> 4.
  - File: Pacman.cpp ~ line: 4.
  - File: Ghost.cpp ~ lines: 4 -> 5.
* The project makes use of references in function declarations.
  - File: Renderer.h ~ lines: 23, 24, 26, 27.
  - File: Game.h ~ lines: 15, 16.
  - File: Pacman.h ~ lines: 16, 23, 26, 32.
  - File: Ghost.h ~ lines: 22, 25, 32.