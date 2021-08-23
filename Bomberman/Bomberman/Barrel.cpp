#include "Barrel.h"

const char* Barrel::barrelIMG;
void Barrel::setBarrelIMG(const char* source) {
    Barrel::barrelIMG = source;
}

Barrel::Barrel(int colPosition, int rowPosition)
    : Entity(Barrel::barrelIMG, colPosition * CELL_SIZE, rowPosition * CELL_SIZE, BARREL, 1)
{}

Barrel::~Barrel(){}
