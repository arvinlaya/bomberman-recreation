#include "Jumble.h"

const char* Jumble::jumbleIMG;
void Jumble::setJumbleIMG(const char* source) {
    Jumble::jumbleIMG = source;
}

Jumble::Jumble(int colPosition, int rowPosition)
    : Item(Jumble::jumbleIMG, colPosition, rowPosition, JUMBLE, 0)
{}

Jumble::~Jumble(){}
