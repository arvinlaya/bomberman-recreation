#include "Turtle.h"

const char* Turtle::turtleIMG;
void Turtle::setTurtleIMG(const char* source) {
    Turtle::turtleIMG = source;
}

Turtle::Turtle(int colPosition, int rowPosition, Direction initDirection)
    : Entity(Turtle::turtleIMG, colPosition * CELL_SIZE, rowPosition * CELL_SIZE, TURTLE, 200), direction(initDirection), pastFrame(SDL_GetTicks()), healthBar(200)
{}

Turtle::~Turtle(){}

SDL_Rect* Turtle::getSpriteRect() {
    return &this->spriteRect;
}

Direction Turtle::getDirection() {
    return this->direction;
}

Direction Turtle::randomDirection() {
    switch(rand() % 4) {
        case 0:
            return UP;
            break;

        case 1:
            return LEFT;
            break;

        case 2:
            return DOWN;
            break;

        case 3:
            return RIGHT;
            break;
    }
}

HealthBar* Turtle::getHealthBar() {
    return &this->healthBar;
}

SDL_Texture* Turtle::getGreenTexture() {
    return this->healthBar.getGreenTexture();
}

SDL_Texture* Turtle::getRedTexture() {
    return this->healthBar.getRedTexture();
}

SDL_Rect* Turtle::getGreenDestRect(int xPosition, int yPosition) {
    return this->healthBar.getGreenDestRect(xPosition, yPosition);
}

SDL_Rect* Turtle::getRedDestRect(int xPosition, int yPosition) {
    return this->healthBar.getRedDestRect(xPosition, yPosition);
}

void Turtle::incrementX() {
    this->getDestRect()->x += 1;
}

void Turtle::incrementY() {
    this->getDestRect()->y += 1;
}

void Turtle::decrementX() {
    this->getDestRect()->x -= 1;
}

void Turtle::decrementY() {
    this->getDestRect()->y -= 1;
}

void Turtle::setFrameSize(int totalCol, int totalRow) {
    this->totalFrameCol = totalCol;
    this->spriteRect.h /= totalRow;
    this->spriteRect.w /= totalCol;
    this->spriteRect.x = 0;
    switch(this->direction) {
        case UP:
            this->spriteRect.y = spriteRect.h * 0;
            this->xVelocity = 0;
            this->yVelocity = -TURTLE_SPEED;
            break;

        case LEFT:
            this->spriteRect.y = spriteRect.h * 3;
            this->xVelocity = -TURTLE_SPEED;
            this->yVelocity = 0;
            break;

        case DOWN:
            this->spriteRect.y = spriteRect.h * 1;
            this->xVelocity = TURTLE_SPEED;
            this->yVelocity = 0;
            break;

        case RIGHT:
            this->spriteRect.y = spriteRect.h * 2;
            this->xVelocity = TURTLE_SPEED;
            this->yVelocity = 0;
            break;
    }

}

void Turtle::walk(bool collisionCheck) {
    this->currentFrame = SDL_GetTicks();

    if(collisionCheck && this->turnCount == 0) {
        this->oppositeDirection();
        this->turnCount = 1;
    }
    else if(collisionCheck == false) {
        this->turnCount = 0;
        if((this->currentFrame - this->pastFrame) >= 300) {
            pastFrame = currentFrame;
            if(this->spriteRect.x < (spriteRect.w * 3))
                this->spriteRect.x += spriteRect.w;
            else
                this->spriteRect.x = 0;
        }

        this->getDestRect()->x += this->xVelocity;
        this->getDestRect()->y += this->yVelocity;
    }


}

void Turtle::oppositeDirection() {

    if(SDL_GetTicks() - this->redirectTime <= 500) {
        this->direction = this->randomDirection();
        this->setXPosition(this->roundNum(this->getXPosition()));
        this->setYPosition(this->roundNum(this->getYPosition()));
    }
    this->redirectTime = SDL_GetTicks();

    switch(this->direction) {
        case UP:
            this->direction = DOWN;
            this->spriteRect.y = this->spriteRect.h * 1;
            this->incrementY();
            this->xVelocity = 0;
            this->yVelocity = TURTLE_SPEED;
            break;

        case LEFT:
            this->direction = RIGHT;
            this->spriteRect.y = this->spriteRect.h * 2;
            this->incrementX();
            this->xVelocity = TURTLE_SPEED;
            this->yVelocity = 0;
            break;

        case DOWN:
            this->direction = UP;
            this->spriteRect.y = this->spriteRect.h * 0;
            this->decrementY();
            this->xVelocity = 0;
            this->yVelocity = -TURTLE_SPEED;
            break;

        case RIGHT:
            this->direction = LEFT;
            this->spriteRect.y = this->spriteRect.h * 3;
            this->decrementX();
            this->xVelocity = -TURTLE_SPEED;
            this->yVelocity = 0;
            break;
    }
}

bool Turtle::getInvulnerabilityState() {
    return this->invulnerable;
}

int Turtle::roundNum(int input) {
    int roundDown = input - (input % 55);
    int roundUp = roundDown + 55;
    return ((input - roundDown) < (roundUp - input))? roundDown: roundUp;
}

void Turtle::damaged(int damage) {
    if(this->getInvulnerabilityState() == false) {
        this->setInvulnerabilityState(true);
        this->subtractLife(damage);
        this->setHitTime();
        this->healthBar.setHP(this->getLife());
    }
}

void Turtle::setHitTime() {
    this->hitTime = SDL_GetTicks();
}

void Turtle::setInvulnerabilityState() {
    if(SDL_GetTicks() - this->hitTime > 2000)
        this->setInvulnerabilityState(false);
}

void Turtle::setInvulnerabilityState(bool state) {
    this->invulnerable = state;
}

void Turtle::subtractLife(int damage) {
    this->setLife(this->getLife() - damage);
}
