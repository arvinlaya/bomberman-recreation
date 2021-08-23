#ifndef PLAYER_H
#define PLAYER_H

#define PLAYER_HP 100

#include "Entity.h"
#include "Item.h"
#include "Bazooka.h"
#include "PortalTimer.h"
#include "PositionHistory.h"
#include "HealthBar.h"

#include <memory>

enum Direction {
    UP = 8, LEFT, DOWN, RIGHT
};

enum PlayerNumber {
    ONE = 1, TWO, NONE
};

class Player: public Entity
{
    public:
        Player(const char* imageLocation, int initXPosition, int initYPosition, PlayerNumber num);
        ~Player();

        SDL_Rect* getSpriteRect();
        int* getImageWidth();
        int* getImageHeight();
        Direction getDirection();
        int getPastX();
        int getPastY();
        int getCooldown();
        int getFlagCount();
        int getBombCount();
        int getCurrentBomb();
        int getBombRange();
        bool getGhostState();
        bool getInvulnerabilityState();
        PlayerNumber getPlayerNumber();
        PortalTimer* getPortalTimer();
        PositionHistory* getPositionHistory();
        std::vector<int>* getXHistory();
        std::vector<int>* getYHistory();
        std::vector<Item>* getItems();
        HealthBar* getHealthBar();
        SDL_Texture* getGreenTexture();
        SDL_Texture* getRedTexture();
        SDL_Rect* getGreenDestRect(int xPosition, int yPosition);
        SDL_Rect* getRedDestRect(int xPosition, int yPosition);

        Item* getItem(ItemType type);
        bool getEffect(ItemType type);
        void setEffect(ItemType type, bool state);

        void setFrameSize(int totalCol, int totalRow);
        void setDirection(Direction direction);
        void incrementFlagCount();
        void incrementX();
        void incrementY();
        void decrementFlagCount();
        void decrementX();
        void decrementY();
        void setPastX(int x);
        void setPastY(int y);
        void setCooldown();
        void setGhost(bool state);
        void incrementSpriteFrame(Direction direction);
        void damaged(int damage);
        void setInvulnerabilityState(bool state);
        void setInvulnerabilityState();
        void subtractLife(int damage);
        void setHitTime();
        void pickItem(Item item);
        void setVelocity(int value);
        void heal(int value);
        void setCurrentBombCount(int value);
        void incrementBombCount();
        void incrementCurrentBomb();
        void decrementCurrentBomb();
        void incrementBombRange();

    protected:

    private:
        PositionHistory positionHistory;
        PlayerNumber playerNumber;
        PortalTimer portalTimer;
        SDL_Rect spriteRect;
        Direction direction;
        HealthBar healthBar;
        int totalFrameCol;
        int pastX;
        int pastY;
        int hitTime;
        int playerVelocity = 5;
        int cooldown;
        int flagCount = 3;
        int bombCount = 1;
        int currentBomb = 0;
        int bombRange = 1;
        bool ghost = true;
        bool invulnerable = false;
        bool zanicEffect = false;
        bool freezeEffect = false;
        bool snailEffect = false;
        bool laserEffect = false;
        bool FEffect = false;

        std::vector<Item> items;
        std::vector<Item>::iterator itemIterator;
};

#endif // PLAYER_H
