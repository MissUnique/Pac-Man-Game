#ifndef PACMAN_H
#define PACMAN_H

#include <SDL.h>
#include <iostream>

#include "Renderer.h"

class Game;

const int PACMAN_SPEED = 2;

struct Position {
	int x;
	int y;
	bool operator==(const Position& i_position) {
		return this->x == i_position.x && this->y == i_position.y;
	}
};

class Pacman {
	public:
		Pacman(Game& g);
		void draw(SDL_Renderer* renderer);
		void set_position(int x, int y);
		void update(std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& pacman_map);
		Position GetPosition();

	private:
		Position position;
		int direction;
		Game& game_;
};

#endif