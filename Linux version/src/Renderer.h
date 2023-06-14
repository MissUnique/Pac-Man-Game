#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>
#include <array>
#include <SDL_ttf.h>
#include <iostream>
#include <string>

class Pacman;
class Ghost;

const int MAP_HEIGHT = 21;
const int MAP_WIDTH = 21;
const int CELL_SIZE = 26;

enum class Cell { Empty, Dot, Wall, Door, Energizer };

class Renderer {
    public:
        Renderer(const int screen_width, const int screen_height);
        ~Renderer();
        std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> map_init(Pacman& pacman, Ghost& Blinky, Ghost& Clyde);
        void render(Pacman& pacman, std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> map, int score, Ghost& Blinky, Ghost& Clyde);
        void render_score(int score, bool gameover);
        void render_gameover(Pacman& pacman, int score);
        void render_win(Pacman& pacman);

    private:
        SDL_Window* window;
        SDL_Renderer* sdl_renderer;
        const int screen_width;
        const int screen_height;
        TTF_Font* font;
};

#endif