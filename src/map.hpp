#ifndef __MAP_H_
#define __MAP_H_

#include "main.hpp"
#include <array>

class Tile {
public:
  // length of a cell/square/tile in the game
  static const int tileLength = 32;

  Tile(SDL_Texture *texture = nullptr, bool blocked = false,
       bool blocksSight = false, std::string label = "UNLABELLED")
      : _texture(texture), _blocked(blocked), _blocksSight(blocksSight),
        _label(label) {}
  Tile(const Tile &other)
      : _texture(other._texture), _blocked(other._blocked),
        _blocksSight(other._blocksSight) {}
  ~Tile() {}

  SDL_Texture *_texture;
  bool _blocked, _blocksSight;

  // human readable description of tile
  std::string _label;
};

using mapTileGrid =
    std::array<std::array<Tile, SCREEN_WIDTH / Tile::tileLength>,
               SCREEN_HEIGHT / Tile::tileLength>;

class Map {
public:
  Map();
  ~Map();

  void LoadMap(std::string mapName);
  void DrawMap();

  bool blockedAt(int i, int j) const;
  std::string labelAt(int i, int j) const;

private:
  // this is prob better than storing a texture for each tile, for space reasons
  SDL_Texture *dirt, *grass, *water, *wall;

  mapTileGrid mapArray;

  void generateRandomRooms();
};

#endif // __MAP_H_
