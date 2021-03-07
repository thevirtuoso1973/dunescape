#include "game.hpp"
#include "textureManager.hpp"

// NOTE: use software renderer instead if this doesn't work
const Uint32 RENDERER_TYPE = SDL_RENDERER_ACCELERATED;

SDL_Texture *playerTex;

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

  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

  if (TTF_Init() == -1) {
    printf("SDL_ttf couldn't init. error: %s\n", TTF_GetError());
    return;
  }

  font = TTF_OpenFont("resources/FiraCode-Regular.ttf", 24);
  if (font == nullptr) {
    printf("Couldn't open font.");
    return;
  }

  playerTex = TextureManager::LoadTextureText(font, "@", {0, 0, 0}, renderer);
  if (playerTex == nullptr) {
    printf("Couldn't load player.");
  }

  isRunning = true;
}

void Game::handleEvents() {
  SDL_Event e;
  SDL_PollEvent(&e);

  switch (e.type) {
  case SDL_QUIT:
    isRunning = false;
    break;
  default:
    break;
  }
}

void Game::update() { count++; }

void Game::render() {
  SDL_RenderClear(renderer);
  SDL_Rect rect;
  rect.x = count % screen_width;
  rect.w = 50;
  rect.h = 50;
  SDL_RenderCopy(renderer, playerTex, nullptr, &rect);
  SDL_RenderPresent(renderer);
}

void Game::clean() {
  SDL_DestroyTexture(playerTex);
  playerTex = nullptr;

  SDL_DestroyWindow(window);
  window = nullptr;

  SDL_DestroyRenderer(renderer);
  renderer = nullptr;

  TTF_CloseFont(font);
  font = nullptr;

  TTF_Quit();
  SDL_Quit();
}
