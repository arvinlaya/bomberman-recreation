#ifndef ROCKET_H
#define ROCKET_H

#include "Entity.h"
#include "Player.h"
#include "Monster.h"
#include "Turtle.h"
#include <math.h>

class Rocket: public Entity
{
    public:
        Rocket(int colPosition ,int rowPosition, Player* target);
        Rocket(int colPosition ,int rowPosition, Monster* target);
        Rocket(int colPosition ,int rowPosition, Turtle* target);

        ~Rocket();

        Entity* getTarget();
        float getAngle();

        bool rocketCollision();

        void track();
        void setAngle(float deltaX, float deltaY, float targetX, float targetY, float hypotenuse);

    protected:

    private:
        EntityType targetType;
        Player* targetPlayer;
        Monster* targetMonster;
        Turtle* targetTurtle;

        int xVelocity = 7;
        int yVelocity = 7;
        float angle;
};

#endif // ROCKET_H
