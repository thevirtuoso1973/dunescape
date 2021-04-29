#ifndef __GRIDPOSITIONCOMPONENT_H_
#define __GRIDPOSITIONCOMPONENT_H_

#include "ecs.hpp"

class GridPositionComponent : public Component {
private:
  int maxRows, maxCols;
  int rowPos, colPos;

  void update(SDL_Event e) {
    if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
      case SDLK_h: // left
        // '%' isn't the modulo operator, so we can't use (colPos - 1) % maxCols
        colPos = colPos == 0 ? maxCols - 1 : colPos - 1;
        break;
      case SDLK_j: // down
        rowPos = (rowPos + 1) % maxRows;
        break;
      case SDLK_k: // up
        rowPos = rowPos == 0 ? maxRows - 1 : rowPos - 1;
        break;
      case SDLK_l: // right
        colPos = (colPos + 1) % maxCols;
        break;
      }
    }
  }

public:
  int row() { return rowPos; }
  int col() { return colPos; }

  GridPositionComponent(int maxRows, int maxCols) {
    this->maxRows = maxRows;
    this->maxCols = maxCols;

    rowPos = colPos = 0;
  }

  void update(const std::vector<SDL_Event> &events) override {
    for (auto &e : events) {
      update(e);
    }
  }
};

#endif // __GRIDPOSITIONCOMPONENT_H_
