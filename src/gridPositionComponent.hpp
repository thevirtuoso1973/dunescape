#ifndef __GRIDPOSITIONCOMPONENT_H_
#define __GRIDPOSITIONCOMPONENT_H_

#include "ecs.hpp"

class GridPositionComponent : public Component {
    private:
        int maxRows, maxCols;
        int rowPos, colPos;

    public:
        int row() { return rowPos; }
        int col() { return colPos; }

        GridPositionComponent(int maxRows, int maxCols) {
            this->maxRows = maxRows;
            this->maxCols = maxCols;

            rowPos = colPos = 0;
        }

        void update() override {
            rowPos = (rowPos + 1) % maxRows;
            colPos = (colPos + 1) % maxCols;
        }
};

#endif // __GRIDPOSITIONCOMPONENT_H_
