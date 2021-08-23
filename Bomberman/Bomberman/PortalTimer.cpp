#include "PortalTimer.h"

PortalTimer::PortalTimer(int initial)
    : start(initial)
{}

PortalTimer::~PortalTimer(){}

int PortalTimer::getTime() {
    return (SDL_GetTicks() - this->start);
}

int PortalTimer::getResetTimer() {
    return (SDL_GetTicks() - this->resetTimer);
}

int PortalTimer::getCooldown() {
    return(SDL_GetTicks() - this->coolDown);
}

bool PortalTimer::isInitialized() {
    if(this->start == 0)
        return false;
    return true;
}

void PortalTimer::setInitial(int value) {
    this->start = value;
}

void PortalTimer::setResetTimer() {
    this->resetTimer = SDL_GetTicks();
}

void PortalTimer::setCooldown() {
    this->coolDown = SDL_GetTicks();
}
