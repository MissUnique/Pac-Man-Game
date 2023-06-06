#include "Game.h"
#include <iostream>

Game::Game() : pacman_(*this) {}

void Game::Run(Renderer& renderer, std::size_t target_frame_duration) {
    Uint32 title_timestamp = SDL_GetTicks();
    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;
    int frame_count = 0;
    bool running = true;

    // Initialize the map
    std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> map = renderer.map_init(pacman_, ghost_);

    while (running) {
        // Game loop
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            }
        }

        frame_start = SDL_GetTicks();

        // Move pacman
        pacman_.update(map);
        // Render map + pacman + score tag
        renderer.render(pacman_, map, score, ghost_);

        frame_end = SDL_GetTicks();

        // Keep track of how long each loop through the input/update/render cycle takes.
        frame_count++;
        frame_duration = frame_end - frame_start;

        // If the time for this frame is too small (i.e. frame_duration is smaller than 
        // the target ms_per_frame), delay the loop to achieve the correct frame rate.
        if (frame_duration < target_frame_duration) {
            SDL_Delay(target_frame_duration - frame_duration);
        }
    }
}

bool Game::collision(short x, short y, std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& game_map, bool eat_dots) {
    // Detect the collision with a wall
	short xf = floor(x / static_cast<float>(CELL_SIZE));
	short xc = ceil(x / static_cast<float>(CELL_SIZE));
	short yf = floor(y / static_cast<float>(CELL_SIZE));
	short yc = ceil(y / static_cast<float>(CELL_SIZE));
	for (int i = 0; i < 4; ++i) {
		switch (i) {
			case 0:     x = xf;		y = yf;		break;
			case 1:     x = xc;		y = yf;		break;
			case 2:     x = xf;		y = yc;		break;
			case 3:     x = xc;		y = yc;		break;
		}

        if (x >= 0 && y >= 0 && x < MAP_WIDTH && y < MAP_HEIGHT) {
            if (eat_dots == 0) { // Collide with a wall
                if (Cell::Wall == game_map[x][y])
                    return true;
            }
            else { 
                if (game_map[x][y] == Cell::Dot) { // Collide with a dot
                    game_map[x][y] = Cell::Empty;
                    score += 100;
                }
            }
        }
	}
	return false;
}


int Game::GetScore() const {
    return score;
}