#include "map.hpp"
#include "main.hpp"
#include "textureManager.hpp"
#include <algorithm>

Map::Map() {
  const SDL_Color brown = {0x99, 0x33, 0x00};
  const SDL_Color green = {0x00, 0xFF, 0x00};
  const SDL_Color blue = {0x00, 0x00, 0xFF};
  const SDL_Color grey = {0x80, 0x80, 0x80};

  dirt = TextureManager::LoadTextureText(".", brown);
  grass = TextureManager::LoadTextureText(".", green);
  water = TextureManager::LoadTextureText("}", blue);
  wall = TextureManager::LoadTextureText("|", grey);

  for (auto &tile : mapArray[0]) {
    tile._texture = wall;
    tile._blocked = tile._blocksSight = true;
    tile._label = "Wall";
  }
  for (unsigned i = 1; i < mapArray.size(); ++i) {
    for (auto &tile : mapArray[i]) {
      tile._texture = grass;
      tile._blocked = tile._blocksSight = false;
      tile._label = "Grass";
    }
  }

  src.x = src.y = 0;
  src.w = 32;
  src.h = 32;
}

Map::~Map() {}

void Map::LoadMap(const std::string mapName) {
  // TODO: load map from file
}

void Map::DrawMap() {
  for (unsigned row = 0; row < mapArray.size(); ++row) {
    for (unsigned col = 0; col < mapArray[0].size(); ++col) {
      SDL_Rect dest;
      dest.w = dest.h = 32;
      dest.x = col * 32;
      dest.y = row * 32;
      TextureManager::Draw(mapArray[row][col]._texture, src, dest);
    }
  }
}

bool Map::blockedAt(int i, int j) const {
  return i < 0 || i >= int(mapArray.size()) || j < 0 || j >= int(mapArray[0].size()) ||
         mapArray[i][j]._blocked;
}

std::string Map::labelAt(int i, int j) const {
  return i >= 0 && i < int(mapArray.size()) && j >= 0 && j < int(mapArray[0].size())
             ? mapArray[i][j]._label
             : "OUT_OF_BOUNDS";
}
