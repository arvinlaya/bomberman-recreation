#include "Freeze.h"

const char* Freeze::freezeIMG;
void Freeze::setFreezeIMG(const char* source) {
    Freeze::freezeIMG = source;
}

Freeze::Freeze(int colPosition, int rowPosition)
    : Item(Freeze::freezeIMG, colPosition, rowPosition, FREEZE, 3)
{}

Freeze::~Freeze(){}
