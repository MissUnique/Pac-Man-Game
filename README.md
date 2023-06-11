# Pac-Man Game
 This is the capstone project for Udacity C++ Nanodegree. The code was inspired by [this](https://github.com/Kofybrek/Pacman) creative game repo, [this](https://github.com/udacity/CppND-Capstone-Snake-Game) Udacity 2D Snake game repo, [this](https://lazyfoo.net/tutorials/SDL/) game programming with SDL tutorials, and Udacity C++ Nanodegree lessons (especially A* search algorithm).

In this project, I built my own C++ application following the principles I learned throughout the Nanodegree Program. I chose to make a simple version of the classic arcade game (Pac-Man). Pac-Man is controlled by the player who directs him throughout the maze to eat all the dots while avoiding the ghost. If Pac-Man ate an energizer, the ghost turns blue for a short while and Pac-Man can eat the ghost during this period and earn bonus points. The player loses if the ghost eats Pac-Man. To win this game: use arrow keys to move your character, Don't get caught, and eat all the dots on the ground.

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
  - Pacman files manages Pac-Man.
  - Ghost files manages ghost behaviour.
* Running this game excutes a game window with playground map and an external player controls for winning.

## Rubric Points Addressed
