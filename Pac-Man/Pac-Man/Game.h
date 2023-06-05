#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include "Renderer.h"
#include "Pacman.h"

class Game {
    public:
        void Run(Renderer& renderer, std::size_t target_frame_duration);
        bool collision(short x, short y, std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& game_map, bool eat_dots);

    private:
        Pacman pacman_;
};

#endif