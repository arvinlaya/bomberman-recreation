#include "Wall.h"

const char* Wall::wallIMG;
void Wall::setWallIMG(const char* source) {
    Wall::wallIMG = source;
}

Wall::Wall(int colPosition, int rowPosition)
    : Entity(Wall::wallIMG, colPosition * CELL_SIZE, rowPosition * CELL_SIZE, WALL, 1)
{}

Wall::~Wall()
{}


