#include "Pacman.h"
#include <iostream>

void Pacman::draw(SDL_Renderer* renderer) {
    const int radius = CELL_SIZE / 2;
    const int x0 = position.x + radius;
    const int y0 = position.y + radius;

    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    for (int y = -radius; y <= radius; ++y) {
        for (int x = -radius; x <= radius; ++x) {
            if (x * x + y * y <= radius * radius) {
                SDL_RenderDrawPoint(renderer, x0 + x, y0 + y);
            }
        }
    }
}

void Pacman::set_position(short i_x, short i_y) {
	position = {i_x, i_y};
}
