#ifndef PACMAN_H
#define PACMAN_H

#include <SDL.h>
#include "Renderer.h"

const unsigned char PACMAN_SPEED = 2;

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
		void update();

	private:
		Position position;
		int direction = -1;
};

#endif