#include "Renderer.h"
#include "Pacman.h"
#include <iostream>

Renderer::Renderer(const int screen_width, const int screen_height) : 
    screen_width(screen_width), screen_height(screen_height) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }
    else {
        // Create window
        window = SDL_CreateWindow("Pac-Man Game --> Azza", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_width, 
            screen_height, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        }
        else {
            // Create renderer
            sdl_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (nullptr == sdl_renderer) {
                std::cerr << "Renderer could not be created.\n";
                std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
            }
        }
    }
}

Renderer::~Renderer() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Renderer::render(Pacman& pacman) {
    // Clear screen
    SDL_SetRenderDrawColor(sdl_renderer, 0x0, 0x0, 0x0, 0xFF);
    SDL_RenderClear(sdl_renderer);

    // Initialize the map
    std::array<std::string, MAP_HEIGHT> map_sketch = {
        " ################### ",
        " #        #        # ",
        " # ## ### # ### ## # ",
        " #                 # ",
        " # ## # ##### # ## # ",
        " #    #   #   #    # ",
        " #### ### # ### #### ",
        "    # #       # #    ",
        "##### # ## ## # #####",
        "        #   #        ",
        "##### # ##### # #####",
        "    # #       # #    ",
        " #### # ##### # #### ",
        " #        P        # ",
        " #  #  ### ###  #  # ",
        " # # #   #   # # # # ",
        " # ###  #   #  ### # ",
        " # # # #   #   # # # ",
        " # # # ### ### # # # ",
        " #                 # ",
        " ################### "
    };

    // Sketch the map
    std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> map;
	for (unsigned char a = 0; a < MAP_HEIGHT; a++) {
		for (unsigned char b = 0; b < MAP_WIDTH; b++) {
			switch (map_sketch[a][b]) {
			    case '#': map[b][a] = Cell::Wall;                               break;
                case 'P': pacman.set_position(CELL_SIZE * b, CELL_SIZE * a);    break;
                default: map[b][a] = Cell::Empty;
			}
		}
	}
    
    // Draw the map
    SDL_Rect cellShape = {0, 0, CELL_SIZE, CELL_SIZE};
	for (unsigned char a = 0; a < MAP_WIDTH; a++) {
		for (unsigned char b = 0; b < MAP_HEIGHT; b++) {
			cellShape.x = CELL_SIZE * a;
			cellShape.y = CELL_SIZE * b;
			switch (map[a][b]) {
			    case Cell::Wall:
                    SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 200, 255);
                    SDL_RenderFillRect(sdl_renderer, &cellShape);
                    break;
			}
		}
	}

    // Draw Pacman
    pacman.draw(sdl_renderer);

    // Update Screen
    SDL_RenderPresent(sdl_renderer);
    std::cout << "Good job Azza!" << '\n';
}
