#include "main.hpp"

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
SDL_Surface *gScreenSurface = nullptr;
SDL_Surface *gKeyPressSurfaces[KeyPressSurfaces::KEY_PRESS_SURFACE_TOTAL];
SDL_Surface *gCurrentSurface = nullptr;

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

  gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];

  while (!quit) {
    while (SDL_PollEvent(&e) != 0) { // retrieve and store next event
      if (e.type == SDL_QUIT) {
        quit = true;
      } else if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
        case SDLK_UP: // don't blame me for the formatting, blame ccls
          gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
          break;
        case SDLK_DOWN:
          gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
          break;
        case SDLK_LEFT:
          gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
          break;
        case SDLK_RIGHT:
          gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
          break;
        default:
          gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
          break;
        }
      }
    }

    // applies image to surface.
    // Draws to the back buffer.
    SDL_Rect stretchRect;
    stretchRect.x = 0;
    stretchRect.y = 0;
    stretchRect.w = SCREEN_WIDTH;
    stretchRect.h = SCREEN_HEIGHT;
    SDL_BlitScaled(gCurrentSurface, NULL, gScreenSurface, &stretchRect);

    // update front buffer, the thing the user sees
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

  const int imgFlags = IMG_INIT_PNG;
  if (!(IMG_Init(imgFlags) & imgFlags)) { // check that we got back desired flag
    printf("SDL_image could not initialize! SDL_image error %s\n",
           SDL_GetError());
    return false;
  }

  gScreenSurface = SDL_GetWindowSurface(gWindow);

  return true;
}

bool loadMedia() {
  gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] =
      loadSurface("resources/press.bmp");
  gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("resources/up.bmp");
  gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("resources/down.bmp");
  gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("resources/left.bmp");
  gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] =
      loadSurface("resources/right.bmp");

  for (int i = 0; i < KeyPressSurfaces::KEY_PRESS_SURFACE_TOTAL; ++i) {
    if (gKeyPressSurfaces[i] == NULL) {
      printf("Failed to load some image.\n");
      return false;
    }
  }
  return true;
}

void close() {
  // deallocates surface
  SDL_FreeSurface(gCurrentSurface);
  gCurrentSurface = nullptr;

  SDL_DestroyWindow(gWindow);
  gWindow = nullptr;

  SDL_Quit();
}

SDL_Surface *loadSurface(std::string path) {
  SDL_Surface *loaded = IMG_Load(path.c_str());
  if (loaded == nullptr) {
    std::cout << "Unable to load image " << path
              << "! SDL Error: " << SDL_GetError() << std::endl;
  }

  // I assume convert surface will fail gracefully if `loaded` was null.
  SDL_Surface *optimizedSurface =
      SDL_ConvertSurface(loaded, gScreenSurface->format, 0);
  if (optimizedSurface == nullptr) {
    std::cout << "Unable to optimize image " << path
              << "! SDL Error: " << SDL_GetError() << std::endl;
  } else {
    SDL_FreeSurface(loaded);
  }

  return optimizedSurface;
}
