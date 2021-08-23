#include "Herb.h"

const char* Herb::herbIMG;
void Herb::setHerbIMG(const char* source) {
    Herb::herbIMG = source;
}

Herb::Herb(int colPosition, int rowPosition)
    : Item(Herb::herbIMG, colPosition, rowPosition, HERB, 0)
{}

Herb::~Herb(){}
