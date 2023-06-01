#include <SDL.h>
#include <iostream>

#include "Renderer.h"

int main(int argc, char* args[]) {
	constexpr int SCREEN_WIDTH = 640;
	constexpr int SCREEN_HEIGHT = 640;

	Renderer renderer(SCREEN_WIDTH, SCREEN_HEIGHT);
	std::cout << "Game has terminated successfully!\n";
	return 0;
}
