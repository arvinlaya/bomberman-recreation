#ifndef TURTLE_H
#define TURTLE_H

#define TURTLE_SPEED 1

#include "Entity.h"
#include "Player.h"

class Turtle : public Entity
{
    public:
        static const char* turtleIMG;
        static void setTurtleIMG(const char* source);

        Turtle(int colPosition, int rowPosition, Direction initDirection);
        ~Turtle();

        SDL_Rect* getSpriteRect();
        Direction getDirection();
        Direction randomDirection();
        HealthBar* getHealthBar();
        SDL_Texture* getGreenTexture();
        SDL_Texture* getRedTexture();
        SDL_Rect* getGreenDestRect(int xPosition, int yPosition);
        SDL_Rect* getRedDestRect(int xPosition, int yPosition);
        bool getInvulnerabilityState();
        int roundNum(int input);

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

    protected:

    private:
        Direction direction;
        int pastFrame;
        HealthBar healthBar;
        int totalFrameCol;
        int currentFrameRow;
        int currentFrame;
        SDL_Rect spriteRect;
        int xVelocity = 0;
        int yVelocity = 0;
        int hitTime;
        int redirectTime = 1000;
        bool invulnerable = false;
        int directionalVelocity = 1;
        int turnCount = 0;

};

#endif // TURTLE_H
