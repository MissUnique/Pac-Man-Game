#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>
#include <array>
#include <SDL_ttf.h>
class Pacman;
class Ghost;

const int MAP_HEIGHT = 21;
const int MAP_WIDTH = 21;
const int CELL_SIZE = 26;

enum class Cell { Empty, Dot, Wall };

class Renderer {
    public:
        Renderer(const int screen_width, const int screen_height);
        ~Renderer();
        std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> map_init(Pacman& pacman, Ghost& ghost);
        void render(Pacman& pacman, std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> map, int score, Ghost& ghost);
        void render_score(int score, bool gameover);
        void render_gameover(Pacman& pacman, int score);
        void render_win(Pacman& pacman);

    private:
        SDL_Window* window = NULL;
        SDL_Renderer* sdl_renderer = NULL;
        const int screen_width;
        const int screen_height;
        TTF_Font* font = NULL;
};

#endif