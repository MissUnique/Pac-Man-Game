#ifndef GHOST_H
#define GHOST_H

#include <SDL.h>
#include "Pacman.h"

class Ghost {
    public:
        Ghost();
        void draw(SDL_Renderer* renderer);
        void set_position(short x, short y);
        void update(std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& ghost_map);

    private:
        Position position;
        int direction;
};

#endif