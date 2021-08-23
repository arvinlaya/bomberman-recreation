#include "Crate.h"

const char* Crate::crateIMG;
void Crate::setCrateIMG(const char* source) {
    Crate::crateIMG = source;
}

Crate::Crate(int colPosition, int rowPosition)
    : Entity(Crate::crateIMG, colPosition * CELL_SIZE, rowPosition * CELL_SIZE, CRATE, 1)
{}

Crate::~Crate(){}

