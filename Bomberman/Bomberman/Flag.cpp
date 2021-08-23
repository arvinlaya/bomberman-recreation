#include "Flag.h"

const char* Flag::flagIMG;
void Flag::setFlagIMG(const char* source) {
    Flag::flagIMG = source;
}

Flag::Flag(int colPosition, int rowPosition, EntityType flagNum)
    : Entity(Flag::flagIMG, colPosition * CELL_SIZE, rowPosition * CELL_SIZE, flagNum, 3)
{}

Flag::~Flag(){}

int Flag::getHitTime() {
    if(this->hitTime == 0)
        return 0;

    return SDL_GetTicks() - this->hitTime;
}

void Flag::setHitTime() {
    this->hitTime = SDL_GetTicks();
}
