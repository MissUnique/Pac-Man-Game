#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include "Renderer.h"
#include "Pacman.h"

class Game {
    public:
        void Run(Renderer& renderer, std::size_t target_frame_duration);

    private:
        Pacman pacman_;
};

#endif