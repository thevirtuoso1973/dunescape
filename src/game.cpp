#include "game.hpp"
#include "gameObject.hpp"
#include "gridPositionComponent.hpp"
#include "textureComponent.hpp"
#include "textureManager.hpp"

// NOTE: use software renderer instead if this doesn't work
const Uint32 RENDERER_TYPE = SDL_RENDERER_ACCELERATED;

SDL_Renderer *Game::renderer = nullptr;
TTF_Font *Game::font = nullptr;

Game::Game() {}
Game::~Game() {}

void Game::init(const char *title, int xpos, int ypos, int width, int height,
                bool fullscreen) {
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    return;
  }

  int flags = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;
  window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
  screen_width = width;
  screen_height = height;
  if (window == nullptr) {
    printf("Couldn't create window! SDL_Error: %s\n", SDL_GetError());
    return;
  }

  renderer = SDL_CreateRenderer(window, -1, RENDERER_TYPE);
  if (renderer == nullptr) {
    printf("Renderer could not be created! SDL error: %s\n", SDL_GetError());
    return;
  }

  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);

  if (TTF_Init() == -1) {
    printf("SDL_ttf couldn't init. error: %s\n", TTF_GetError());
    return;
  }

  font = TTF_OpenFont("resources/FiraCode-Regular.ttf", 24);
  if (font == nullptr) {
    printf("Couldn't open font.");
    return;
  }

  map = new Map();

  auto &player(manager.addEntity());
  player.addComponent<GridPositionComponent>(SCREEN_HEIGHT / 32,
                                             SCREEN_WIDTH / 32, 1, 1);
  SDL_Color white = {0xFF, 0xFF, 0xFF};
  player.addComponent<TextureComponent>("@", white);

  isRunning = true;
}

// handles events and updates
void Game::update() {
  std::vector<SDL_Event> events;
  SDL_Event e;

  while (SDL_PollEvent(&e)) {
    events.emplace_back(e);
  }

  if (std::any_of(events.begin(), events.end(),
                  [](SDL_Event event) { return event.type == SDL_QUIT; })) {
    isRunning = false;
  }

  manager.update(events, *map);
}

void Game::render() {
  SDL_RenderClear(renderer);

  map->DrawMap();
  manager.draw();

  SDL_RenderPresent(renderer);
}

void Game::clean() {
  SDL_DestroyWindow(window);
  window = nullptr;

  SDL_DestroyRenderer(renderer);
  renderer = nullptr;

  TTF_CloseFont(font);
  font = nullptr;

  TTF_Quit();
  SDL_Quit();
}
