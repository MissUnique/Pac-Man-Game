#ifndef GHOST_H
#define GHOST_H

#include <SDL.h>
#include <time.h>
#include "Pacman.h"
class Game;

const int GHOST_SPEED = 1.5;

class Ghost {
    public:
        Ghost(Game& g);
        void draw(SDL_Renderer* renderer);
        void set_position(short x, short y);
        void update(std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& ghost_map);

    private:
        Position position = { 0, 0 };
        int direction = -1;
        Game& game_;
        unsigned seed = static_cast<unsigned>(time(NULL)); // using the system clock
        int random_direction = rand() % 4;
};

#endif