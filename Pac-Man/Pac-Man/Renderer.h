#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>
#include <array>
class Pacman;

const unsigned char MAP_HEIGHT = 21;
const unsigned char MAP_WIDTH = 21;
const unsigned char CELL_SIZE = 26;

enum class Cell { Door, Empty, Energizer, Pellet, Wall };

class Renderer {
    public:
        Renderer(const int screen_width, const int screen_height);
        ~Renderer();
        void render(Pacman& pacman);

    private:
        SDL_Window* window = NULL;
        SDL_Renderer* sdl_renderer = NULL;
        const int screen_width;
        const int screen_height;
};

#endif