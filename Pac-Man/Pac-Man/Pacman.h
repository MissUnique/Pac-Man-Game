#ifndef PACMAN_H
#define PACMAN_H

#include <SDL.h>
#include "Renderer.h"

struct Position {
	short x;
	short y;
	bool operator==(const Position& i_position) {
		return this->x == i_position.x && this->y == i_position.y;
	}
};

class Pacman {
	public:
		void draw(SDL_Renderer* renderer);
		void set_position(short i_x, short i_y);

	private:
		Position position;
};

#endif