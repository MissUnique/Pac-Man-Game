#include "Ghost.h"
#include <iostream>

Ghost::Ghost() {}

void Ghost::draw(SDL_Renderer* renderer) {
    // Set color to red
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    
    // Draw lower part of the ghost
    SDL_Rect lower_Shape = { position.x + 1, position.y + (CELL_SIZE / 2), CELL_SIZE - 1, CELL_SIZE / 2 };
    SDL_RenderFillRect(renderer, &lower_Shape);

    // Draw upper part of ghost
    const int radius = CELL_SIZE / 2;
    const int x0 = position.x + radius;
    const int y0 = position.y + radius;
    for (int y = -radius; y <= radius; ++y)
        for (int x = -radius; x <= radius; ++x)
            if (x * x + y * y <= radius * radius)
                SDL_RenderDrawPoint(renderer, x0 + x, y0 + y);
}

void Ghost::set_position(short x, short y) {
    position = { x, y };
}

void Ghost::update(std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& ghost_map) {

}
