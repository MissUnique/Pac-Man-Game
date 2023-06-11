#include "Game.h"

#include <iostream>

Game::Game() : pacman_(*this), ghost_(*this) {}

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

        // Check if ghost killed Pacman
        if (ghost_.collide_with_pacman(pacman_.GetPosition()))
            renderer.render_gameover(pacman_, score);

        // else check if Pacman won
        else if (dots == 0)
                renderer.render_win(pacman_);

        // else keep the game going
        else {
            // Move pacman + ghost
            pacman_.update(map);
            ghost_.update(map, pacman_.GetPosition());

            // Render map + Pacman + score tag
            renderer.render(pacman_, map, score, ghost_);
        }
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

bool Game::collision(int x, int y, std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& game_map, bool eat_dots) {
    // Detect the collision with a wall
	int xf = floor(x / static_cast<float>(CELL_SIZE));
	int xc = ceil(x / static_cast<float>(CELL_SIZE));
	int yf = floor(y / static_cast<float>(CELL_SIZE));
	int yc = ceil(y / static_cast<float>(CELL_SIZE));
	for (int i = 0; i < 4; ++i) {
		switch (i) {
			case 0:     x = xf;		y = yf;		break;
			case 1:     x = xc;		y = yf;		break;
			case 2:     x = xf;		y = yc;		break;
			case 3:     x = xc;		y = yc;		break;
		}

        if (x >= 0 && y >= 0 && x < MAP_WIDTH && y < MAP_HEIGHT) {
            // Collide with a wall
            if (eat_dots == 0) { 
                if (Cell::Wall == game_map[x][y])
                    return true;
            }
            // Collide with a dot
            else { 
                if (game_map[x][y] == Cell::Dot) { 
                    game_map[x][y] = Cell::Empty;
                    score += 100;
                    dots--;
                }
            }
        }
	}
	return false;
}
