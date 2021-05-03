#ifndef __GRIDPOSITIONCOMPONENT_H_
#define __GRIDPOSITIONCOMPONENT_H_

#include "ecs.hpp"
#include "game.hpp"

inline void notifyBump(std::string label) {
  std::cout << "You bumped into a " << label << std::endl;
}

class GridPositionComponent : public Component {
private:
  int maxRows, maxCols;
  int rowPos, colPos;

  void update(SDL_Event e, Map &map) {
    if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
      case SDLK_h: // left
        if (!map.blockedAt(rowPos, colPos - 1)) {
          colPos = std::max(0, colPos - 1);
        } else {
          notifyBump(map.labelAt(rowPos, colPos - 1));
        }
        break;
      case SDLK_j: // down
        if (!map.blockedAt(rowPos + 1, colPos)) {
          rowPos = std::min(maxRows - 1, rowPos + 1);
        } else {
          notifyBump(map.labelAt(rowPos + 1, colPos));
        }
        break;
      case SDLK_k: // up
        if (!map.blockedAt(rowPos - 1, colPos)) {
          rowPos = std::max(0, rowPos - 1);
        } else {
          notifyBump(map.labelAt(rowPos - 1, colPos));
        }
        break;
      case SDLK_l: // right
        if (!map.blockedAt(rowPos, colPos + 1)) {
          colPos = std::min(maxCols - 1, colPos + 1);
        } else {
          notifyBump(map.labelAt(rowPos, colPos + 1));
        }
        break;
      }
      std::cout << "x: " << rowPos << ", y: " << colPos << std::endl;
    }
  }

public:
  int row() { return rowPos; }
  int col() { return colPos; }

  GridPositionComponent(int maxRows, int maxCols, int startRow = 0,
                        int startCol = 0) {
    this->maxRows = maxRows;
    this->maxCols = maxCols;

    rowPos = startRow;
    colPos = startCol;
  }

  void update(const std::vector<SDL_Event> &events, Map &map) override {
    for (auto &e : events) {
      update(e, map);
    }
  }
};

#endif // __GRIDPOSITIONCOMPONENT_H_
