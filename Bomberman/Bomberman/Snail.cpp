#include "Snail.h"

const char* Snail::snailIMG;
void Snail::setSnailIMG(const char* source) {
    Snail::snailIMG = source;
}

Snail::Snail(int colPosition, int rowPosition)
    : Item(Snail::snailIMG, colPosition, rowPosition, SNAIL, 5)
{}

Snail::~Snail()
{
    //dtor
}
