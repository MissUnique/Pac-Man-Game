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

void Pacman::update() {
    // Control Pacman movement by keyboard
    const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);
    if (keyboardState[SDL_SCANCODE_RIGHT])
        direction = 0;
    if (keyboardState[SDL_SCANCODE_UP])
        direction = 1;
    if (keyboardState[SDL_SCANCODE_LEFT])
        direction = 2;
    if (keyboardState[SDL_SCANCODE_DOWN])
        direction = 3;

    std::cout << "Direction = " << direction << "\t position.x = " << position.x << '\n';

    // Move Pacman
    switch (direction) {
    case 0: position.x += PACMAN_SPEED; std::cout << "\tNew: " << position.x << '\n';     break;
        case 1: position.y -= PACMAN_SPEED;     break;
        case 2: position.x -= PACMAN_SPEED;     break;
        case 3: position.y += PACMAN_SPEED;     break;
    }
}