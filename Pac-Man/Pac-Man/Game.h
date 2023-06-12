#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <chrono>
#include <iostream>

#include "Renderer.h"
#include "Pacman.h"
#include "Ghost.h"

class Game {
    public:
        Game();
        void Run(Renderer& renderer, std::size_t target_frame_duration);
        bool collision(int x, int y, std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& game_map, bool eat_dots);
        void add_score(int s);

        bool isEnergized;
        std::chrono::high_resolution_clock::time_point t1;

    private:
        Pacman pacman_;
        int score;
        Ghost Blinky_, Clyde_;
        int dots;
};

#endif