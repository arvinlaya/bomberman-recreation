#ifndef MONSTER_H
#define MONSTER_H

#include "Entity.h"
#include "Player.h"

#define MONSTER_SPEED 2
#define VELOCITY_DIRECTION 1

class Monster: public Entity
{
    public:
        static const char* monsterIMG;
        static void setMonsterIMG(const char* source);

        Monster(int colPosition, int rowPosition, Direction direction);
        ~Monster();

        int* getImageWidth();
        int* getImageHeight();
        int getDirectionalVelocity();
        int roundNum(int input);
        bool getInvulnerabilityState();
        SDL_Rect* getSpriteRect();
        Direction getDirection();
        Direction randomDirection();
        HealthBar* getHealthBar();
        SDL_Texture* getGreenTexture();
        SDL_Texture* getRedTexture();
        SDL_Rect* getGreenDestRect(int xPosition, int yPosition);
        SDL_Rect* getRedDestRect(int xPosition, int yPosition);

        Item* getItem(ItemType type);
        bool getEffect(ItemType type);
        void setEffect(ItemType type, bool state);

        void incrementX();
        void incrementY();
        void decrementX();
        void decrementY();
        void setFrameSize(int totalCol, int totalRow);
        void walk(bool collisionCheck);
        void oppositeDirection();
        void damaged(int damage);
        void setHitTime();
        void setInvulnerabilityState();
        void setInvulnerabilityState(bool state);
        void subtractLife(int damage);
        void setVelocity(int value);
        void setDirection();

    protected:

    private:
        Direction direction;
        int pastFrame;
        HealthBar healthBar;
        int totalFrameCol;
        int currentFrame;
        int imageWidth;
        int imageHeight;
        int hitTime;
        int redirectTime = 1000;
        bool invulnerable = false;
        int xVelocity = 2;
        int yVelocity = 2;
        int directionalVelocity = 1;
        int currentXVelocity  = MONSTER_SPEED;
        int currentYVelocity = MONSTER_SPEED;
        int turnCount = 0;
        SDL_Rect spriteRect;
        bool freezeEffect = false;
        bool snailEffect = false;
};

#endif // MONSTER_H
