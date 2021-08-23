#ifndef ENTITY_H
#define ENTITY_H

#define ENTITY_HEIGHT 55
#define ENTITY_WIDTH 55
#define CELL_SIZE 55
#define COLLISION_RANGE 45

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <iostream>

enum EntityType {
    WALL, BRICK, HARDBRICK, CRATE, BARREL, FLAG_ONE, FLAG_TWO, COMMON_CRATE, METAL_CRATE, PORTAL_SOURCE, PORTAL_DESTINATION, BOMB, ITEM, PLAYER, MONSTER, TURTLE, ROCKET, LIGHTNING, CLOUD
};

enum ItemType {
    BAZOOKA, ZANIC, FREEZE, LASER, SMITE, SNAIL, PORTAL, JUMBLE, HERB, F_ITEM, MUSHROOM, BOMB_ADD, RANGE_ADD
};

class Entity
{

    public:

        Entity(const char* imageLocation, int colPosition, int rowPosition, EntityType type, int lifeCount, int imageWidth, int imageHeight);
        Entity(const char* imageLocation, int colPosition, int rowPosition, EntityType type, int lifeCount);
        ~Entity();

        void setTexture(SDL_Renderer* render, SDL_Surface* surface);
        void setLife(int value);
        void decrementLife();
        void setXPosition(int value);
        void setYPosition(int value);

        const char* getImageSource();
        int getYPosition();
        int getXPosition();
        int getLife();
        SDL_Texture* getTexture();
        SDL_Rect* getDestRect();
        EntityType getEntityType();

    protected:

    private:
        const char* imageSource;
        SDL_Rect destRect;
        EntityType entityType;
        int life;

        SDL_Texture* texture;
};

#endif // ENTITY_H
