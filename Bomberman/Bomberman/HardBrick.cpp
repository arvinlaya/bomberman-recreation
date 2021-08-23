#include "HardBrick.h"

const char* HardBrick::hardBrickIMG;
void HardBrick::setHardBrickIMG(const char* source) {
    HardBrick::hardBrickIMG = source;
}

HardBrick::HardBrick(int colPosition, int rowPosition)
    : Entity(HardBrick::hardBrickIMG, colPosition * CELL_SIZE, rowPosition * CELL_SIZE, HARDBRICK, 2)
{}

HardBrick::~HardBrick(){}


