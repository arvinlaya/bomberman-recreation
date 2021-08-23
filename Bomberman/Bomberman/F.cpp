#include "F.h"

const char* F::fIMG;
void F::setFIMG(const char* source) {
    F::fIMG = source;
}

F::F(int colPosition, int rowPosition)
    : Item(F::fIMG, colPosition, rowPosition, F_ITEM, 10)
{}

F::~F(){}
