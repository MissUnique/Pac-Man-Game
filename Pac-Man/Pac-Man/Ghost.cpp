#include "Ghost.h"
#include "Game.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

Ghost::Ghost(Game& g) : game_(g) { srand(seed); }

void Ghost::draw(SDL_Renderer* renderer) {
    if (!canBeEaten)
        // Set color to red
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    else
        // Set color to blue
        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
    
    // Draw lower part of the ghost
    SDL_Rect lower_Shape = { position.x + 1, position.y + (CELL_SIZE / 2), CELL_SIZE - 1, CELL_SIZE / 2 };
    SDL_RenderFillRect(renderer, &lower_Shape);

    // Draw upper part of ghost
    const int radius = CELL_SIZE / 2;
    const int x0 = position.x + radius;
    const int y0 = position.y + radius;
    for (int y = -radius; y <= radius; ++y)
        for (int x = -radius; x <= radius; ++x)
            if (x * x + y * y <= radius * radius)
                SDL_RenderDrawPoint(renderer, x0 + x, y0 + y);
}

void Ghost::set_position(int x, int y) {
    position = { x, y };
    init_pos = { x, y };
}

void Ghost::update(std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& ghost_map, Position pacman_pos) {
    if (canMove) {
        // Collision detection with walls
        bool walls[4] = {};
        walls[0] = game_.collision(GHOST_SPEED + position.x, position.y, ghost_map, 0);
        walls[1] = game_.collision(position.x, position.y - GHOST_SPEED, ghost_map, 0);
        walls[2] = game_.collision(position.x - GHOST_SPEED, position.y, ghost_map, 0);
        walls[3] = game_.collision(position.x, GHOST_SPEED + position.y, ghost_map, 0);

        // If the ghost hits a wall, generate a new random direction
        if (walls[random_direction]) {
            // Generate new random direction (integer between 0 and 3)
            int new_direction = rand() % 4;
            // Check if the new direction is not blocked by a wall
            while (walls[new_direction])
                new_direction = rand() % 4;
            random_direction = new_direction;
        }

        // If ghost in normal state
        if (!canBeEaten) {
            // Using A* search algorithm to hunt Pacman
            std::vector<std::vector<int>> openlist{};
            int ghost_x = position.x / CELL_SIZE;
            int ghost_y = position.y / CELL_SIZE;

            // Initialize the starting node
            int x = position.y / CELL_SIZE;
            int y = position.x / CELL_SIZE;
            int g = 0; // Cost
            int Heuristic = abs(pacman_pos.x / CELL_SIZE - x) + abs(pacman_pos.y / CELL_SIZE - y); // Calculate the manhattan distance

            // Create a new grid with cell states
            std::array<std::array<State, MAP_HEIGHT>, MAP_WIDTH> grid{};
            for (int a = 0; a < MAP_HEIGHT; ++a)
                for (int b = 0; b < MAP_WIDTH; ++b)
                    if (ghost_map[b][a] == Cell::Wall) {
                        grid[a][b] = State::kWall;
                    }
                    else {
                        grid[a][b] = State::kEmpty;
                    }

            // Because the map is flipped, pacman position coordinates are exchanged
            int pacmanX = pacman_pos.y / CELL_SIZE;
            int pacmanY = pacman_pos.x / CELL_SIZE;

            // Add node to open vector, and mark grid cell as closed
            openlist.emplace_back(std::vector<int>{x, y, g, Heuristic, x, y});
            grid[x][y] = State::kClosed;

            // Initialize a vector holding all steps possible in the search for pacman
            std::vector<std::vector<int>> all_steps;

            // A* main Loop
            while (openlist.size() > 0) {
                // Sort the vector of ints in descending order
                std::sort(openlist.begin(), openlist.end(), [](std::vector<int> a, std::vector<int> b) {
                    return a[2] + a[3] > b[2] + b[3];});

                // Get the next node
                all_steps.emplace_back(openlist.back());
                std::vector<int> current = openlist.back();
                openlist.pop_back();
                x = current[0];
                y = current[1];
                grid[x][y] = State::kPath;

                // Check if we're done
                if (x == pacmanX && y == pacmanY) {
                    // Trace back through the path to get the correct path from ghost to Pacman
                    std::vector<Position> Path;
                    Path.push_back({ pacman_pos.x, pacman_pos.y }); // Add Pacman's position to the path
                    int xCurrent = x;
                    int yCurrent = y;
                    while (xCurrent != position.y / CELL_SIZE || yCurrent != position.x / CELL_SIZE)
                        for (auto& node : all_steps)
                            if (node[0] == xCurrent && node[1] == yCurrent) {
                                xCurrent = node[4]; // Set xCurrent to parent node's x index
                                yCurrent = node[5]; // Set yCurrent to parent node's y index
                                Path.push_back({ yCurrent, xCurrent }); // Add parent node to path
                                break;
                            }

                    // Reverse the path to get the correct order
                    std::reverse(Path.begin(), Path.end());

                    // Select direction based on current and next step coordinates
                    if (ghost_x == Path[1].x) {
                        if (ghost_y > Path[1].y)
                            direction = 1;
                        else
                            direction = 3;
                    }
                    else if (ghost_y == Path[1].y) {
                        if (ghost_x > Path[1].x)
                            direction = 2;
                        else
                            direction = 0;
                    }

                    break;
                }

                // If we're not done 
                // Get current node's data
                int xCurrent = current[0];
                int yCurrent = current[1];
                int gCurrent = current[2];

                // Expand search to current node's neighbors. Loop through potential neighbors
                int cant_go = 0;
                for (int i = 0; i < 4; i++) {
                    int x2 = xCurrent + delta[i][0];
                    int y2 = yCurrent + delta[i][1];

                    // Check that a cell is valid: on the map, not a wall, and empty
                    bool on_grid_x = (x2 >= 0 && x2 < grid.size());
                    bool on_grid_y = (y2 >= 0 && y2 < grid[0].size());
                    bool validCell = false;
                    if (on_grid_x && on_grid_y)
                        validCell = grid[x2][y2] == State::kEmpty;
                    if (!validCell)
                        cant_go++;

                    // Check that the potential neighbor's x2 and y2 values are on the grid and not closed.
                    if (validCell) {
                        // Increment g value and update h value
                        int g2 = gCurrent + 1;
                        int Heuristic2 = abs(pacmanX - x2) + abs(pacmanY - y2);

                        // Add neighbor to open list, and mark grid cell as closed.
                        openlist.emplace_back(std::vector<int>{x2, y2, g2, Heuristic2, xCurrent, yCurrent});
                        grid[x2][y2] = State::kClosed;
                    }
                }

                if (cant_go == 4)
                    grid[xCurrent][yCurrent] = State::kClosed;
            }
        }

        // else if ghost is frightened
        else {
            direction = random_direction;
        }

        // If the ghost doesn't hit a wall, move the ghost in the new direction
        // [Directions: (0 = right) (1 = up) (2 = Left) (3 = down)]
        if (!walls[direction]) {
            switch (direction) {
            case 0: position.x += GHOST_SPEED;     break;
            case 1: position.y -= GHOST_SPEED;     break;
            case 2: position.x -= GHOST_SPEED;     break;
            case 3: position.y += GHOST_SPEED;     break;
            }
            prev_direction = direction;
        }
        // If ghost hits a wall, move in last saved direction
        else {
            switch (prev_direction) {
            case 0: position.x += GHOST_SPEED;     break;
            case 1: position.y -= GHOST_SPEED;     break;
            case 2: position.x -= GHOST_SPEED;     break;
            case 3: position.y += GHOST_SPEED;     break;
            }
        }

        // Check map edges and move to the opposite direction
        if (-CELL_SIZE >= position.x)
            position.x = CELL_SIZE * MAP_WIDTH - GHOST_SPEED;
        else if (CELL_SIZE * MAP_WIDTH <= position.x)
            position.x = GHOST_SPEED - CELL_SIZE;
    }

    // Else if the ghost can't move
    else {
        double distance = std::sqrt((init_pos.x - position.x) * (init_pos.x - position.x) 
            + (init_pos.y - position.y) * (init_pos.y - position.y));
        double angle = std::atan2(init_pos.y - position.y, init_pos.x - position.x);
        if (distance > 0.01) {
            position.x += std::cos(angle) * GHOST_SPEED * 2;
            position.y += std::sin(angle) * GHOST_SPEED * 2;
        }

        // If ghost returned home
        else {
            canMove = true;
            isEaten = false;
        }
    }

    // If Pacman eat an energizer
    if (game_.isEnergized) {
        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - game_.t1).count();
        if (duration < 3000) {
            canBeEaten = true;
            if (collide_with_pacman(pacman_pos)) {
                if (!isEaten) {
                    game_.add_score(500);
                    isEaten = true;
                }
                canMove = false;
            }
            t2 = std::chrono::high_resolution_clock::now();
        }
        else {
            game_.isEnergized = false;
            canBeEaten = false;
        }
    }
}

bool Ghost::collide_with_pacman(Position pacman_pos) {
    if (position.x > pacman_pos.x - CELL_SIZE && position.x < CELL_SIZE + pacman_pos.x)
        if (position.y > pacman_pos.y - CELL_SIZE && position.y < CELL_SIZE + pacman_pos.y)
            return 1;
    return 0;
}