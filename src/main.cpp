#include "main.hpp"
#include "game.hpp"

// TODO: lesson 8
// TODO: or continue with https://www.youtube.com/watch?v=jzasDqPmtPI&list=PLhfAbcv9cehhkG7ZQK0nfIGJC_C-wSLrx&index=6

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

Game *game = nullptr;

//  NOTE: uncheck native opengl when running with WSL
int main(int argc, char *argv[]) {
  game = new Game();

  game->init("Dunescape", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
             SCREEN_WIDTH, SCREEN_HEIGHT, false);
  while (game->running()) {
    game->handleEvents();
    game->update();
    game->render();
  }

  game->clean();

  return 0;
}
