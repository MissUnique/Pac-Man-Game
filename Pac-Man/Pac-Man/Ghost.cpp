#include "Ghost.h"
#include "Game.h"
#include <iostream>

Ghost::Ghost(Game& g) : game_(g) { srand(seed); }

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
    // Collision detection with walls
    bool walls[4];
    walls[0] = game_.collision(GHOST_SPEED + position.x, position.y, ghost_map, 0);
    walls[1] = game_.collision(position.x, position.y - GHOST_SPEED, ghost_map, 0);
    walls[2] = game_.collision(position.x - GHOST_SPEED, position.y, ghost_map, 0);
    walls[3] = game_.collision(position.x, GHOST_SPEED + position.y, ghost_map, 0);

    // If the ghost hits a wall, generate a new random direction
    if (walls[random_direction]) {
        // Generate new random direction (integer between 0 and 3)
        int new_direction = rand() % 4;
        // Check if the new direction is not blocked by a wall
        while (walls[new_direction])
            new_direction = rand() % 4;
        random_direction = new_direction;
    }

    // Move the ghost
    switch (random_direction) {
        case 0: position.x += GHOST_SPEED;     break;
        case 1: position.y -= GHOST_SPEED;     break;
        case 2: position.x -= GHOST_SPEED;     break;
        case 3: position.y += GHOST_SPEED;     break;
    }
    // Check map edges and move to the opposite direction
    if (-CELL_SIZE >= position.x)
        position.x = CELL_SIZE * MAP_WIDTH - GHOST_SPEED;
    else if (CELL_SIZE * MAP_WIDTH <= position.x)
        position.x = GHOST_SPEED - CELL_SIZE;
}
