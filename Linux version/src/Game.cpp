#include "Game.h"

Game::Game() : isEnergized(false), t1(std::chrono::high_resolution_clock::now()), pacman_(*this), score(0), 
    Blinky_(*this), Clyde_(*this), dots(0) {}

void Game::Run(Renderer& renderer, std::size_t target_frame_duration) {
    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;
    int frame_count = 0;
    bool running = true;

    // Initialize the map
    std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> map = renderer.map_init(pacman_, Blinky_, Clyde_);

    while (running) {
        // Game loop
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            }
        }

        frame_start = SDL_GetTicks();

        dots = 0;
        for (int i = 0; i < MAP_WIDTH; ++i)
            for (int j = 0; j < MAP_HEIGHT; j++)
                if (map[i][j] == Cell::Dot)
                    dots++;

        // Check if ghost killed Pacman
        if ((Blinky_.collide_with_pacman(pacman_.GetPosition()) && !isEnergized)
            || (Clyde_.collide_with_pacman(pacman_.GetPosition()) && !isEnergized))
            renderer.render_gameover(pacman_, score);

        // else check if Pacman won
        else if (dots == 0)
                renderer.render_win(pacman_);

        // else keep the game going
        else {
            // Move pacman + ghost
            pacman_.update(map);
            Blinky_.update(map, pacman_.GetPosition(), 1);
            Clyde_.update(map, pacman_.GetPosition(), 2);

            // Render map + Pacman + score tag + ghost
            renderer.render(pacman_, map, score, Blinky_, Clyde_);

            // Return ghosts to normal state if game is not energized
            if (!isEnergized) {
                Blinky_.set_canBeEaten(false);
                Clyde_.set_canBeEaten(false);
            }
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
            else {
                // Collide with a dot
                if (game_map[x][y] == Cell::Dot) { 
                    game_map[x][y] = Cell::Empty;
                    score += 100;
                }
                // Collide with an energizer
                else if (game_map[x][y] == Cell::Energizer) {
                    game_map[x][y] = Cell::Empty;
                    isEnergized = true;
                    t1 = std::chrono::high_resolution_clock::now();
                }
            }
        }
	}
	return false;
}

void Game::add_score(int s) {
    score += s;
}
