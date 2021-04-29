#include "main.hpp"
#include "game.hpp"

// TODO: lesson 8
// TODO: or continue with
// https://www.youtube.com/watch?v=XsvI8Sng6dk&list=PLhfAbcv9cehhkG7ZQK0nfIGJC_C-wSLrx&index=9

const int FPS = 60;
const int frameDelay = 1000 / FPS;

Game *game = nullptr;

//  NOTE: uncheck native opengl when running with WSL
int main(int argc, char *argv[]) {
  Uint32 frameStart;
  int frameTime;

  game = new Game();

  game->init("Dunescape", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
             SCREEN_WIDTH, SCREEN_HEIGHT, false);
  while (game->running()) {
    frameStart = SDL_GetTicks();

    game->update();
    game->render();

    frameTime = SDL_GetTicks() - frameStart;

    if (frameDelay > frameTime) {
      SDL_Delay(frameDelay - frameTime);
    }
  }

  game->clean();

  return 0;
}
