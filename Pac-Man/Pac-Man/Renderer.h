#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>

class Renderer {
public:
    Renderer(const int screen_width, const int screen_height);
    ~Renderer();

private:
    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;
    const int screen_width;
    const int screen_height;
};

#endif