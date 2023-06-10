#ifndef GHOST_H
#define GHOST_H

#include <SDL.h>

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

    private:
        Position position = { 0, 0 };
        int direction = -1;
        int prev_direction = -1;
        Game& game_;
        const int delta[4][2]{ {-1, 0}, {0, -1}, {1, 0}, {0, 1} };
};

#endif