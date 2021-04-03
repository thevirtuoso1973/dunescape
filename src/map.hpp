#ifndef __MAP_H_
#define __MAP_H_

#include "game.hpp"
#include "main.hpp"
#include <array>

using mapGrid = std::array<std::array<char, SCREEN_WIDTH / 32>, SCREEN_HEIGHT / 32>;

class Map {
public:
  Map();
  ~Map();

  void LoadMap(const mapGrid);
  void DrawMap();

private:
  SDL_Rect src, dest;

  SDL_Texture *dirt, *grass, *water;

  mapGrid mapArray;
};

#endif // __MAP_H_
