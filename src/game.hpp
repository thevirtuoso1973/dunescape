#ifndef __GAME_H_
#define __GAME_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>

class Game {
public:
  Game();
  ~Game();

  void init(const char *title, int xpos, int ypos, int width, int height,
            bool fullscreen);

  void handleEvents();
  void update();
  void render();
  void clean();

  bool running() { return isRunning; }

private:
  SDL_Window *window;
  SDL_Renderer *renderer;
  TTF_Font *font;

  int screen_width;
  int screen_height;

  int count;
  bool isRunning = false;
};

#endif // __GAME_H_
