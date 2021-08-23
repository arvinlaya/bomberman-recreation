#include "Portal.h"

const char* Portal::portalIMG;
void Portal::setPortalIMG(const char* source) {
    Portal::portalIMG = source;
}

Portal::Portal(int colPosition, int rowPosition)
    : Item(Portal::portalIMG, colPosition, rowPosition, PORTAL, 30), source(0, 0), destination(0, 0)
{}

Portal::Portal(int colPosition, int rowPosition, int targetColPosition, int targetRowPosition, SDL_Renderer* renderer)
    : Item(Portal::portalIMG, colPosition, rowPosition, PORTAL, 30), source(colPosition, rowPosition), destination(targetColPosition, targetRowPosition)
{
    SDL_Surface* surface = IMG_Load(source.getImageSource());
    this->source.setTexture(renderer, surface);

    surface = IMG_Load(destination.getImageSource());
    this->destination.setTexture(renderer, surface);

    SDL_FreeSurface(surface);
}

Portal::~Portal(){}

bool Portal::inside(int playerX, int playerY, Player* player) {
    if((playerX == this->source.getXPosition() && playerY == this->source.getYPosition()) || (playerX == this->destination.getXPosition() && playerY == this->destination.getYPosition())) {
        if(player->getPortalTimer()->isInitialized() == false)
            player->getPortalTimer()->setInitial(SDL_GetTicks());

        player->getPortalTimer()->setResetTimer();
        return true;
    }
    if(player->getPortalTimer()->getResetTimer() <= 100)
        return true;

    player->getPortalTimer()->setInitial(0);
    return false;
}

Path Portal::getPath(int playerX, int playerY) {
    if(playerX == this->source.getXPosition() && playerY == this->source.getYPosition())
        return DESTINATION;
    return SOURCE;
}

SDL_Texture* Portal::getSourceTexture() {
    return this->source.getTexture();
}

SDL_Texture* Portal::getDestinationTexture() {
    return this->destination.getTexture();
}

SDL_Rect* Portal::getSourceRect() {
    return this->source.getDestRect();
}

SDL_Rect* Portal::getDestinationRect() {
    return this->destination.getDestRect();
}

void Portal::teleport(int playerX, int playerY, Player* player) {
    Path path = this->getPath(playerX, playerY);
    player->getPortalTimer()->setInitial(0);
    player->getPortalTimer()->setCooldown();

    if(path == DESTINATION) {
        player->damaged(0);
        player->setXPosition(this->destination.getXPosition());
        player->setYPosition(this->destination.getYPosition());
    }
    else if(path == SOURCE) {
        player->damaged(0);
        player->setXPosition(this->source.getXPosition());
        player->setYPosition(this->source.getYPosition());
    }

}
