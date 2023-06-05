#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>
#include <array>
class Pacman;

const int MAP_HEIGHT = 21;
const int MAP_WIDTH = 21;
const unsigned char CELL_SIZE = 26;

enum class Cell { Door, Empty, Energizer, Dot, Wall };

class Renderer {
    public:
        Renderer(const int screen_width, const int screen_height);
        ~Renderer();
        std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> map_init(Pacman& pacman);
        void render(Pacman& pacman, std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> map);

    private:
        SDL_Window* window = NULL;
        SDL_Renderer* sdl_renderer = NULL;
        const int screen_width;
        const int screen_height;
};

#endif