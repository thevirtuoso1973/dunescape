#include "main.hpp"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 640;

SDL_Window *gWindow = nullptr;
SDL_Surface *gScreenSurface = nullptr;
SDL_Surface *gHelloWorld = nullptr;

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

  while (!quit) {
    while (SDL_PollEvent(&e) != 0) { // retrieve and store next event
      if (e.type == SDL_QUIT) {
        quit = true;
      }
    }

    //  applies image to surface.
    // Draws to the back buffer.
    SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);

    //  update front buffer, the thing the user sees
    SDL_UpdateWindowSurface(gWindow);
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

  gScreenSurface = SDL_GetWindowSurface(gWindow);

  return true;
}

bool loadMedia() {
  const char *relativePath = "resources/hello_world.bmp";
  gHelloWorld = SDL_LoadBMP(relativePath);
  if (gHelloWorld == NULL) {
    printf("Unable to load image %s! SDL error: %s\n", relativePath,
           SDL_GetError());
    return false;
  }
  return true;
}

void close() {
  // deallocates surface
  SDL_FreeSurface(gHelloWorld);
  gHelloWorld = nullptr;

  SDL_DestroyWindow(gWindow);
  gWindow = nullptr;

  SDL_Quit();
}

SDL_Surface *loadSurface(std::string path) {
  SDL_Surface *loaded = SDL_LoadBMP(path.c_str());
  if (loaded == nullptr) {
    std::cout << "Unable to load image " << path
              << "! SDL Error: " << SDL_GetError() << std::endl;
  }
  return loaded;
}
