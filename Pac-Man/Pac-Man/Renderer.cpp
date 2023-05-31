#include "Renderer.h"
#include <iostream>

Renderer::Renderer(const int screen_width, const int screen_height) : screen_width(screen_width), screen_height(screen_height) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }
    else {
        // Create window
        window = SDL_CreateWindow("Pac-Man Game --> Azza", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_width, 
            screen_height, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        }
        else {
            screenSurface = SDL_GetWindowSurface(window);
            SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0x0, 0x0, 0x0));
            SDL_UpdateWindowSurface(window);
            SDL_Event e; bool quit = false; while (quit == false) { while (SDL_PollEvent(&e)) { if (e.type == SDL_QUIT) quit = true; } }
        }
    }
}

Renderer::~Renderer() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}
