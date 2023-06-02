#include <SDL.h>
#include <iostream>

#include "Renderer.h"
#include "Game.h"

int main(int argc, char* args[]) {
	constexpr int SCREEN_WIDTH = 545;
	constexpr int SCREEN_HEIGHT = 640;
	constexpr std::size_t kFramesPerSecond{ 60 };
	constexpr std::size_t kMsPerFrame{ 1000 / kFramesPerSecond };

	Renderer renderer(SCREEN_WIDTH, SCREEN_HEIGHT);
	Game game;
	game.Run(renderer, kMsPerFrame);
	std::cout << "Game has terminated successfully!\n";
	return 0;
}
