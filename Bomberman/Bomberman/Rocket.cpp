#include "Rocket.h"

Rocket::Rocket(int colPosition ,int rowPosition, Player* target)
    : Entity("images/game/rocket.png", colPosition, rowPosition, ROCKET, 1), targetType(PLAYER), targetPlayer(target)
{}


Rocket::Rocket(int colPosition ,int rowPosition, Monster* target)
    : Entity("images/game/rocket.png", colPosition, rowPosition, ROCKET, 1), targetType(MONSTER), targetMonster(target)
{}

Rocket::Rocket(int colPosition ,int rowPosition, Turtle* target)
    : Entity("images/game/rocket.png", colPosition, rowPosition, ROCKET, 1), targetType(TURTLE), targetTurtle(target)
{}

Rocket::~Rocket(){}

Entity* Rocket::getTarget() {
    switch(targetType) {
        case PLAYER:
            return this->targetPlayer;
            break;

        case MONSTER:
            return this->targetMonster;
            break;

        case TURTLE:
            return this->targetTurtle;
            break;
    }
}

bool Rocket::rocketCollision() {
    int targetY = this->getTarget()->getYPosition();
    int targetX = this->getTarget()->getXPosition();
    if(this->getYPosition() - COLLISION_RANGE < targetY && this->getYPosition() > targetY - CELL_SIZE && this->getXPosition() - COLLISION_RANGE < targetX && this->getXPosition() > targetX - COLLISION_RANGE) {
        if(this->targetType == PLAYER)
            this->targetPlayer->damaged(40);
        else if(this->targetType == MONSTER)
            this->targetMonster->damaged(40);
        else
            this->targetTurtle->damaged(40);

        return true;
    }
    return false;
}

float Rocket::getAngle() {
    return this->angle;
}

void Rocket::track() {
    Entity* target = this->getTarget();
    float targetX = target->getXPosition();
    float targetY = target->getYPosition();
    float deltaX = targetX - this->getXPosition();
    float deltaY = targetY - this->getYPosition();
    float distance = sqrt((deltaX * deltaX) + (deltaY * deltaY));
    this->getDestRect()->x += (deltaX * this->xVelocity) / distance;
    this->getDestRect()->y += (deltaY * this->yVelocity) / distance;
    this->setAngle(deltaX, deltaY, targetX, targetY, distance);
}

void Rocket::setAngle(float deltaX, float deltaY, float targetX, float targetY, float hypotenuse) {
    float adjacent = deltaX;
    float opposite = deltaY;

    if(targetY > this->getYPosition())
        this->angle = ((180 * (acos( adjacent / hypotenuse))) / M_PI);
    else {
        this->angle = ((180 * (atan( opposite / adjacent))) / M_PI);
        if(targetX < this->getXPosition())
            this->angle += 180;
    }
}
