#include <SDL.h>
#include <iostream>

#include "Renderer.h"
#include "Game.h"
#include "Pacman.h"

int main(int argc, char* args[]) {
	constexpr int SCREEN_WIDTH = 545;
	constexpr int SCREEN_HEIGHT = 600;
	constexpr Uint32 kFramesPerSecond{ 60 };
	constexpr Uint32 kMsPerFrame{ 1000 / kFramesPerSecond };

	Renderer renderer(SCREEN_WIDTH, SCREEN_HEIGHT);
	Game game;
	game.Run(renderer, kMsPerFrame);
	std::cout << "Game has terminated successfully!" << '\n';
	std::cout << "Score: " << game.GetScore() << "\n";
	return 0;
}
