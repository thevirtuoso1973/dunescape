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

  generateRandomRooms();
}

Map::~Map() {}

void Map::LoadMap(const std::string mapName) {
  // TODO: load map from file
}

void Map::DrawMap() {
  SDL_Rect src;
  src.x = src.y = 0;
  src.w = src.h = Tile::tileLength;

  for (unsigned row = 0; row < mapArray.size(); ++row) {
    for (unsigned col = 0; col < mapArray[0].size(); ++col) {
      SDL_Rect dest;
      dest.w = dest.h = Tile::tileLength;
      dest.x = col * Tile::tileLength;
      dest.y = row * Tile::tileLength;
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

void Map::generateRandomRooms() {
  for (auto &row : mapArray) {
    for (auto &tile : row) {
      tile._texture = wall;
      tile._blocked = tile._blocksSight = true;
      tile._label = "Wall";
    }
  }
}
