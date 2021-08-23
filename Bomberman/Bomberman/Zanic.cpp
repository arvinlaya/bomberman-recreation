#include "Zanic.h"

const char* Zanic::zanicIMG;
void Zanic::setZanicIMG(const char* source) {
    Zanic::zanicIMG = source;
}

Zanic::Zanic(int colPosition, int rowPosition)
    : Item(zanicIMG, colPosition, rowPosition, ZANIC, 10)
{}

Zanic::~Zanic(){}
