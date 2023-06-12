#ifndef GHOST_H
#define GHOST_H

#include <SDL.h>
#include <chrono>
#include <time.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#include "Pacman.h"

class Game;

const int GHOST_SPEED = 1.75;

enum class State { kClosed, kEmpty, kPath, kWall };

class Ghost {
    public:
        Ghost(Game& g);
        void draw(SDL_Renderer* renderer);
        void set_position(int x, int y);
        void update(std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& ghost_map, Position pacman_pos);
        bool collide_with_pacman(Position pacman_pos);

    private:
        Position position;
        int direction;
        int prev_direction;
        Game& game_;
        const int delta[4][2]{ {-1, 0}, {0, -1}, {1, 0}, {0, 1} };
        bool canBeEaten;
        unsigned seed = static_cast<unsigned>(time(NULL)); // using the system clock
        int random_direction = rand() % 4;
        bool canMove;
        Position init_pos;
        bool isEaten;
};

#endif