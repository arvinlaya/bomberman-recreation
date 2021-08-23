#include "Brick.h"

const char* Brick::brickIMG;
void Brick::setBrickIMG(const char* source) {
    Brick::brickIMG = source;
}

Brick::Brick(int colPosition, int rowPosition)
    : Entity(Brick::brickIMG, colPosition * CELL_SIZE, rowPosition * CELL_SIZE, BRICK, 1)
{}

Brick::~Brick(){}

