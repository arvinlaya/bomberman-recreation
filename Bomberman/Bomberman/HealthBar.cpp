#include "HealthBar.h"

SDL_Texture* HealthBar::greenBarTexture;
SDL_Texture* HealthBar::redBarTexture;

void HealthBar::initializeHealthBar(SDL_Renderer* renderer) {
    SDL_Surface* surface = IMG_Load("images/game/greenBar.png");
    HealthBar::greenBarTexture = SDL_CreateTextureFromSurface(renderer, surface);

    surface = IMG_Load("images/game/redBar.png");
    HealthBar::redBarTexture = SDL_CreateTextureFromSurface(renderer, surface);
}
//x y h w
HealthBar::HealthBar(int HP)
    : health(HP), greenDestRect{0, 0, CELL_SIZE, CELL_SIZE}, redDestRect{0, 0, CELL_SIZE, CELL_SIZE}
{}

HealthBar::~HealthBar(){}

SDL_Texture* HealthBar::getGreenTexture() {
    return this->greenBarTexture;
}

SDL_Texture* HealthBar::getRedTexture() {
    return this->redBarTexture;
}

SDL_Rect* HealthBar::getGreenDestRect(int xPosition, int yPosition) {
    this->greenDestRect.y = yPosition - (CELL_SIZE/2);
    this->greenDestRect.x = xPosition;
    return &this->greenDestRect;
}

SDL_Rect* HealthBar::getRedDestRect(int xPosition, int yPosition) {
    this->redDestRect.y = yPosition - (CELL_SIZE/2);
    this->redDestRect.x = xPosition;
    return &this->redDestRect;
}

void HealthBar::setHP(int life) {
    float barSize = ((float)life / (float)this->health) * CELL_SIZE;
    this->greenDestRect.w = barSize;
}
