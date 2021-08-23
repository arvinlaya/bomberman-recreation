#include "Entity.h"

Entity::Entity(const char* imageLocation, int colPosition, int rowPosition, EntityType type, int lifeCount, int imageWidth, int imageHeight)
    : imageSource(imageLocation), destRect{colPosition, rowPosition, imageHeight, imageWidth}, entityType(type), life(lifeCount)
{}

Entity::Entity(const char* imageLocation, int colPosition, int rowPosition, EntityType type, int lifeCount)
    : imageSource(imageLocation), destRect{colPosition, rowPosition, ENTITY_HEIGHT, ENTITY_WIDTH}, entityType(type), life(lifeCount)
{}

Entity::~Entity() {}

const char* Entity::getImageSource() {
    return this->imageSource;
}

SDL_Texture* Entity::getTexture() {
    return this->texture;
}

SDL_Rect* Entity::getDestRect() {
    return &this->destRect;
}

int Entity::getXPosition() {
    return this->destRect.x;
}

int Entity::getYPosition() {
    return this->destRect.y;
}

EntityType Entity::getEntityType(){
    return this->entityType;
}

int Entity::getLife() {
    return this->life;
}

void Entity::setTexture(SDL_Renderer* render, SDL_Surface* surface) {
    this->texture = SDL_CreateTextureFromSurface(render, surface);
}

void Entity::decrementLife() {
    this->life--;
}

void Entity::setLife(int value) {
    this->life = value;
}

void Entity::setXPosition(int value) {
    this->destRect.x = value;
}

void Entity::setYPosition(int value) {
    this->destRect.y = value;
}


