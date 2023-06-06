#include "Pacman.h"
#include "Game.h"
#include <iostream>

Pacman::Pacman(Game& g) : game_(g) {}

void Pacman::draw(SDL_Renderer* renderer) {
    // Circle (Pacman) dimentions
    const int radius = CELL_SIZE / 2;
    const int x0 = position.x + radius;
    const int y0 = position.y + radius;

    // Draw yellow Pacman on screen
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    for (int y = -radius; y <= radius; ++y)
        for (int x = -radius; x <= radius; ++x)
            if (x * x + y * y <= radius * radius)
                SDL_RenderDrawPoint(renderer, x0 + x, y0 + y);
}

void Pacman::set_position(short i_x, short i_y) {
	position = {i_x, i_y};
}

void Pacman::update(std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& pacman_map) {
    // Collision detection with walls
    bool walls[4];
    walls[0] = game_.collision(PACMAN_SPEED + position.x, position.y, pacman_map, 0);
    walls[1] = game_.collision(position.x, position.y - PACMAN_SPEED, pacman_map, 0);
    walls[2] = game_.collision(position.x - PACMAN_SPEED, position.y, pacman_map, 0);
    walls[3] = game_.collision(position.x, PACMAN_SPEED + position.y, pacman_map, 0);

    // Control Pacman movement by keyboard
    const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);
    if (keyboardState[SDL_SCANCODE_RIGHT])
        if (walls[0] == 0)
            direction = 0;
    if (keyboardState[SDL_SCANCODE_UP])
        if (walls[1] == 0)
            direction = 1;
    if (keyboardState[SDL_SCANCODE_LEFT])
        if (walls[2] == 0)
            direction = 2;
    if (keyboardState[SDL_SCANCODE_DOWN])
        if (walls[3] == 0)
            direction = 3;

    // Move Pacman
    switch (direction) {
        case 0: position.x += PACMAN_SPEED;     break;
        case 1: position.y -= PACMAN_SPEED;     break;
        case 2: position.x -= PACMAN_SPEED;     break;
        case 3: position.y += PACMAN_SPEED;     break;
    }

    // Check map edges and move to the opposite direction
    if (-CELL_SIZE >= position.x)
        position.x = CELL_SIZE * MAP_WIDTH - PACMAN_SPEED;
    
    else if (CELL_SIZE * MAP_WIDTH <= position.x)
        position.x = PACMAN_SPEED - CELL_SIZE;

    // Eat the dots and get score points
    game_.collision(position.x, position.y, pacman_map, 1);

    // Stop Pacman
    direction = -1;
}