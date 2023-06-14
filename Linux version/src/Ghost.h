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
        void draw(SDL_Renderer* renderer, int id);
        void set_position(int x, int y);
        void update(std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& ghost_map, Position pacman_pos, int id);
        bool collide_with_pacman(Position pacman_pos);
        void set_canBeEaten(bool can);

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
        Position target;
        std::chrono::high_resolution_clock::time_point t1_Clyde;
        bool status;
};

#endif