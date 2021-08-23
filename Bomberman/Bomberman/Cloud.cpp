#include "Cloud.h"

SDL_Texture* Cloud::cloudTexture;
void Cloud::loadCloudIMG(SDL_Renderer* renderer) {
    SDL_Surface* surface = IMG_Load("images/game/cloud.png");
    Cloud::cloudTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

Cloud::Cloud(Player* target)
    : Entity("", 0, 0, CLOUD, 0, CLOUD_HEIGHT, CLOUD_WIDTH), lightning(), targetPlayer(target), hitTime(SDL_GetTicks())
{}

Cloud::~Cloud()
{}

SDL_Texture* Cloud::getCloudTexture() {
    return Cloud::cloudTexture;
}

Lightning* Cloud::getLightning() {
    return &this->lightning;
}

Player* Cloud::getTarget() {
    return this->targetPlayer;
}

bool Cloud::charged() {
    if(SDL_GetTicks() - this->hitTime >= 4000) {
        if(SDL_GetTicks() - this->hitTime >= 5000) {
            this->hitTime = SDL_GetTicks();
            this->hitReady = true;
        }
        return true;
    }
    this->hitReady = false;
    return false;
}

bool Cloud::getHitState() {
    return this->hitReady;
}
