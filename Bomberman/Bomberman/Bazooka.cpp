#include "Bazooka.h"

const char* Bazooka::bazookaIMG;
void Bazooka::setBazookaIMG(const char* source) {
    Bazooka::bazookaIMG = source;
}

Bazooka::Bazooka(int colPosition, int rowPosition)
    : Item(Bazooka::bazookaIMG, colPosition, rowPosition, BAZOOKA, 0)
{}

Bazooka::~Bazooka(){}

