#include "main.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdio>

// TODO: lesson 8

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

enum KeyPressSurfaces {
  KEY_PRESS_SURFACE_DEFAULT,
  KEY_PRESS_SURFACE_UP,
  KEY_PRESS_SURFACE_DOWN,
  KEY_PRESS_SURFACE_LEFT,
  KEY_PRESS_SURFACE_RIGHT,
  KEY_PRESS_SURFACE_TOTAL, // holds the total number of surfaces
};

SDL_Window *gWindow = nullptr;
SDL_Renderer *gRenderer = nullptr;
SDL_Texture *gKeyPressTextures[KeyPressSurfaces::KEY_PRESS_SURFACE_TOTAL];
SDL_Texture *gTexture = nullptr; // currently displayed texture

// NOTE: uncheck native opengl when running with WSL
int main(int argc, char *argv[]) {
  if (!init()) {
    printf("Failed to init.\n");
    return 1;
  }
  if (!loadMedia()) {
    printf("Failed to load media.\n");
    return 1;
  }

  bool quit = false;
  SDL_Event e;

  gTexture = gKeyPressTextures[KEY_PRESS_SURFACE_DEFAULT];

  while (!quit) {
    while (SDL_PollEvent(&e) != 0) { // retrieve and store next event
      if (e.type == SDL_QUIT) {
        quit = true;
      } else if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
        case SDLK_UP: // don't blame me for the formatting, blame ccls
          gTexture = gKeyPressTextures[KEY_PRESS_SURFACE_UP];
          break;
        case SDLK_DOWN:
          gTexture = gKeyPressTextures[KEY_PRESS_SURFACE_DOWN];
          break;
        case SDLK_LEFT:
          gTexture = gKeyPressTextures[KEY_PRESS_SURFACE_LEFT];
          break;
        case SDLK_RIGHT:
          gTexture = gKeyPressTextures[KEY_PRESS_SURFACE_RIGHT];
          break;
        default:
          gTexture = gKeyPressTextures[KEY_PRESS_SURFACE_DEFAULT];
          break;
        }
      }
    }

    SDL_RenderClear(gRenderer);
    SDL_RenderCopy(gRenderer, gTexture, nullptr, nullptr);
    SDL_RenderPresent(gRenderer); // actually update the screen
  }

  close();
  return 0;
}

bool init() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    return false;
  }

  gWindow = SDL_CreateWindow("SDL Practice", SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                             SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (gWindow == NULL) {
    printf("Couldn't create window! SDL_Error: %s\n", SDL_GetError());
    return false;
  }

  gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
  if (gRenderer == nullptr) {
    printf("Renderer could not be created! SDL error: %s\n", SDL_GetError());
    return false;
  }

  SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

  const int imgFlags = IMG_INIT_PNG;
  if (!(IMG_Init(imgFlags) & imgFlags)) { // check that we got back desired flag
    printf("SDL_image could not initialize! SDL_image error %s\n",
           SDL_GetError());
    return false;
  }

  return true;
}

bool loadMedia() {
  gKeyPressTextures[KEY_PRESS_SURFACE_DEFAULT] =
      loadTexture("resources/press.bmp");
  gKeyPressTextures[KEY_PRESS_SURFACE_UP] = loadTexture("resources/up.bmp");
  gKeyPressTextures[KEY_PRESS_SURFACE_DOWN] = loadTexture("resources/down.bmp");
  gKeyPressTextures[KEY_PRESS_SURFACE_LEFT] = loadTexture("resources/left.bmp");
  gKeyPressTextures[KEY_PRESS_SURFACE_RIGHT] =
      loadTexture("resources/right.bmp");

  for (int i = 0; i < KeyPressSurfaces::KEY_PRESS_SURFACE_TOTAL; ++i) {
    if (gKeyPressTextures[i] == nullptr) {
      printf("Failed to load some texture image.\n");
      return false;
    }
  }
  return true;
}

void close() {
  // free the texture
  SDL_DestroyTexture(gTexture);
  gTexture = nullptr;

  SDL_DestroyRenderer(gRenderer);
  gRenderer = nullptr;

  SDL_DestroyWindow(gWindow);
  gWindow = nullptr;

  IMG_Quit();
  SDL_Quit();
}

SDL_Texture *loadTexture(std::string path) {
  SDL_Surface *loadedSurface = IMG_Load(path.c_str());
  if (loadedSurface == nullptr) {
    printf("Couldn't load image %s, error: %s\n", path.c_str(), IMG_GetError());
    return nullptr;
  }

  SDL_Texture *newTexture =
      SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
  if (newTexture == nullptr) {
    printf("texture error! error: %s\n", SDL_GetError());
  }

  SDL_FreeSurface(loadedSurface);
  return newTexture;
}
