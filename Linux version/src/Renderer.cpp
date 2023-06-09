#include "Renderer.h"
#include "Pacman.h"
#include "Ghost.h"

Renderer::Renderer(const int screen_width, const int screen_height) : window(NULL), sdl_renderer(NULL), 
    screen_width(screen_width), screen_height(screen_height), font(NULL) {
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

            // Initialize the font
            if (TTF_Init() == -1) {
                printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
                throw std::runtime_error("Failed to initialize SDL_ttf");
            }
            font = TTF_OpenFont("assets/ObelixProIt-cyr.ttf", 24);
            if (font == NULL) {
                printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
                throw std::runtime_error("Failed to load font");
            }
        }
    }
}

Renderer::~Renderer() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}

std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> Renderer::map_init(Pacman& pacman, Ghost& Blinky, Ghost& Clyde) {
    // Initialize the map
    std::array<std::string, MAP_HEIGHT> map_sketch = {
        " ################### ",
        " #........#........# ",
        " #e##.###.#.###.##e# ",
        " #.................# ",
        " #.##.#.#####.#.##.# ",
        " #....#...#...#....# ",
        " ####.###.#.###.#### ",
        "    #.#       #.#    ",
        "#####.# ##-## #.#####",
        "     .  #CB #  .     ",
        "#####.# ##### #.#####",
        "    #.#       #.#    ",
        " ####.# ##### #.#### ",
        " #........P........# ",
        " #..#..###.###..#..# ",
        " #.# #...#...#.# #.# ",
        " #.###..#...#..###.# ",
        " #.#e#.#...#...#e#.# ",
        " #.#.#.###.###.#.#.# ",
        " #.................# ",
        " ################### "
    };

    // Sketch the map
    std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> map{};
    for (unsigned char a = 0; a < MAP_HEIGHT; a++) {
        for (unsigned char b = 0; b < MAP_WIDTH; b++) {
            switch (map_sketch[a][b]) {
                case '#': map[b][a] = Cell::Wall;                               break;
                case 'P': pacman.set_position(CELL_SIZE * b, CELL_SIZE * a);    break;
                case '.': map[b][a] = Cell::Dot;                                break;
                case 'B': Blinky.set_position(CELL_SIZE * b, CELL_SIZE * a);    break;
                case '-': map[b][a] = Cell::Door;                               break;
                case 'e': map[b][a] = Cell::Energizer;                          break;
                case 'C': Clyde.set_position(CELL_SIZE * b, CELL_SIZE * a);     break;
                default: map[b][a] = Cell::Empty;
            }
        }
    }

    return map;
}

void Renderer::render(Pacman& pacman, std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> map, int score, Ghost& Blinky, Ghost& Clyde) {
    // Clear screen
    SDL_SetRenderDrawColor(sdl_renderer, 0x0, 0x0, 0x0, 0xFF);
    SDL_RenderClear(sdl_renderer);

    // Draw the map
    SDL_Rect wallShape = {0, 0, CELL_SIZE, CELL_SIZE };
    SDL_Rect doorShape = { 0, 0, CELL_SIZE, CELL_SIZE / 3 };
    const int dotRadius = CELL_SIZE / 8;
    const int energizerRadius = CELL_SIZE / 3;
    int dotX, dotY, energizerX, energizerY;
	for (unsigned char a = 0; a < MAP_WIDTH; a++) {
		for (unsigned char b = 0; b < MAP_HEIGHT; b++) {
            wallShape.x = CELL_SIZE * a;
            wallShape.y = CELL_SIZE * b;
            dotX = (CELL_SIZE * a) + (CELL_SIZE / 2);
            dotY = (CELL_SIZE * b) + (CELL_SIZE / 2);
            energizerX = (CELL_SIZE * a) + (CELL_SIZE / 2);
            energizerY = (CELL_SIZE * b) + (CELL_SIZE / 2);
            doorShape.x = CELL_SIZE * a;
            doorShape.y = (CELL_SIZE * b) + (CELL_SIZE / 4);
			switch (map[a][b]) {
			    case Cell::Wall:
                    SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 255, 255);
                    SDL_RenderFillRect(sdl_renderer, &wallShape);
                    break;
                case Cell::Dot:
                    SDL_SetRenderDrawColor(sdl_renderer, 255, 255, 255, 255);
                    for (int y = -dotRadius; y <= dotRadius; ++y)
                        for (int x = -dotRadius; x <= dotRadius; ++x)
                            if (x * x + y * y <= dotRadius * dotRadius)
                                SDL_RenderDrawPoint(sdl_renderer, dotX + x, dotY + y);
                    break;
                case Cell::Door:
                    SDL_SetRenderDrawColor(sdl_renderer, 0, 255, 255, 255);
                    SDL_RenderFillRect(sdl_renderer, &doorShape);
                    break;
                case Cell::Energizer:
                    SDL_SetRenderDrawColor(sdl_renderer, 0, 255, 255, 255);
                    for (int y = -energizerRadius; y <= energizerRadius; ++y)
                        for (int x = -energizerRadius; x <= energizerRadius; ++x)
                            if (x * x + y * y <= energizerRadius * energizerRadius)
                                SDL_RenderDrawPoint(sdl_renderer, energizerX + x, energizerY + y);
                    break;
                default: break;
			}
		}
	}

    // Draw Pacman
    pacman.draw(sdl_renderer);

    // Render the score
    render_score(score, 0);

    // Draw Ghosts
    Blinky.draw(sdl_renderer, 1);
    Clyde.draw(sdl_renderer, 2);

    // Update Screen
    SDL_RenderPresent(sdl_renderer);
    //std::cout << "Wonderful job Azza!" << '\n';
}

void Renderer::render_score(int score, bool gameover) {
    // Convert the score to a string
    std::string score_str = "Score: " + std::to_string(score);

    // Create a surface containing the score text
    SDL_Color color = { 255, 255, 255, 255 }; // White
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, score_str.c_str(), color);
    if (textSurface == NULL) {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        return;
    }

    // Create a texture from the surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(sdl_renderer, textSurface);
    if (texture == NULL) {
        printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        SDL_FreeSurface(textSurface);
        return;
    }

    // Get the width and height of the texture
    int w, h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);

    // Construct a rectangle to hold the texture with location depending on game state
    SDL_Rect rect;
    if (!gameover) {
        rect.x = (screen_width - w) / 2;
        rect.y = screen_height - h - 15;
    }
    else {
        rect.x = (screen_width - w) / 2;
        rect.y = (screen_height - h) / 2;
    }
    rect.w = w;
    rect.h = h;

    // Render the texture to the screen
    SDL_RenderCopy(sdl_renderer, texture, NULL, &rect);

    // Clean up
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(textSurface);
}

void Renderer::render_gameover(Pacman& pacman, int score) {
    // Clear screen
    SDL_SetRenderDrawColor(sdl_renderer, 0x0, 0x0, 0x0, 0xFF);
    SDL_RenderClear(sdl_renderer);

    // Draw Pacman
    pacman.draw(sdl_renderer);

    // Render the score
    render_score(score, 1);

    // Render game over
    std::string gameover_str = "GAME   OVER";
    SDL_Color color = { 200, 0, 0, 255 };
    TTF_Font* endfont = TTF_OpenFont("assets/ObelixProIt-cyr.ttf", 50);
    SDL_Surface* textSurface = TTF_RenderText_Solid(endfont, gameover_str.c_str(), color);
    if (textSurface == NULL) {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        return;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(sdl_renderer, textSurface);
    if (texture == NULL) {
        printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        SDL_FreeSurface(textSurface);
        return;
    }
    int w, h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    SDL_Rect rect;
    rect.x = (screen_width - w) / 2;
    rect.y = (screen_height - h) / 3;
    rect.w = w;
    rect.h = h;
    SDL_RenderCopy(sdl_renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(textSurface);

    // Update Screen
    SDL_RenderPresent(sdl_renderer);
}

void Renderer::render_win(Pacman& pacman) {
    // Clear screen
    SDL_SetRenderDrawColor(sdl_renderer, 0x0, 0x0, 0x0, 0xFF);
    SDL_RenderClear(sdl_renderer);

    // Draw Pacman
    pacman.draw(sdl_renderer);

    // Render YOU WIN!
    std::string gameover_str = "YOU   WIN!";
    SDL_Color color = { 0, 255, 0, 255 };
    TTF_Font* endfont = TTF_OpenFont("assets/ObelixProIt-cyr.ttf", 50);
    SDL_Surface* textSurface = TTF_RenderText_Solid(endfont, gameover_str.c_str(), color);
    if (textSurface == NULL) {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        return;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(sdl_renderer, textSurface);
    if (texture == NULL) {
        printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        SDL_FreeSurface(textSurface);
        return;
    }
    int w, h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    SDL_Rect rect;
    rect.x = (screen_width - w) / 2;
    rect.y = (screen_height - h) / 3;
    rect.w = w;
    rect.h = h;
    SDL_RenderCopy(sdl_renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(textSurface);

    // Update Screen
    SDL_RenderPresent(sdl_renderer);
}