#include "Smite.h"

const char* Smite::smiteIMG;
void Smite::setSmiteIMG(const char* source) {
    Smite::smiteIMG = source;
}

Smite::Smite(int colPosition, int rowPosition)
    : Item(Smite::smiteIMG, colPosition, rowPosition, SMITE, 21)
{}

Smite::~Smite(){}
