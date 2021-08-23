#include "Item.h"

Item::Item(const char* imageLocation, int colPosition, int rowPosition, ItemType type, int itemDuration)
    : Entity(imageLocation, colPosition, rowPosition, ITEM, 1), itemType(type), initDuration(itemDuration*1000)
{}

Item::~Item()
{}

ItemType Item::getItemType() {
    return this->itemType;
}

int Item::getPickUpTime() {
    return this->pickTime;
}

int Item::getDuration() {
    return this->duration;
}

void Item::setPickUpTime() {
    this->pickTime = SDL_GetTicks();
}

void Item::activateItem(){
    std::cout << "WORKS" << std::endl;
}

void Item::setDuration() {
    this->duration = SDL_GetTicks() + initDuration;
}
