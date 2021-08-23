#include "Lightning.h"

SDL_Texture* Lightning::lightningTexture;
void Lightning::loadLightningIMG(SDL_Renderer* renderer) {
    SDL_Surface* surface = IMG_Load("images/game/lightning.png");
    Lightning::lightningTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

Lightning::Lightning()
    : Entity("", 0, 0, LIGHTNING, 0, LIGHTNING_HEIGHT, LIGHTNING_WIDTH)
{}

Lightning::~Lightning(){}

SDL_Texture* Lightning::getLightningTexture() {
    return Lightning::lightningTexture;
}
