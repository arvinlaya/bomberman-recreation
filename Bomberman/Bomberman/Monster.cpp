#include "Monster.h"

const char* Monster::monsterIMG;
void Monster::setMonsterIMG(const char* source) {
    Monster::monsterIMG = source;
}

Monster::Monster(int colPosition, int rowPosition, Direction initDirection)
    : Entity(monsterIMG, colPosition * CELL_SIZE, rowPosition * CELL_SIZE, MONSTER, 100), direction(initDirection), pastFrame(SDL_GetTicks()), healthBar(100)
{
    switch(initDirection) {
        case UP:
            this->directionalVelocity = -VELOCITY_DIRECTION;
            this->xVelocity = 0;
            this->yVelocity = currentYVelocity * directionalVelocity;
            break;

        case LEFT:
            this->directionalVelocity = -VELOCITY_DIRECTION;
            this->xVelocity = currentXVelocity * directionalVelocity;
            this->yVelocity = 0;
            break;

        case DOWN:
            this->directionalVelocity = VELOCITY_DIRECTION;
            this->xVelocity = 0;
            this->yVelocity = currentYVelocity * directionalVelocity;
            break;

        case RIGHT:
            this->directionalVelocity = VELOCITY_DIRECTION;
            this->xVelocity = currentXVelocity * directionalVelocity;
            this->yVelocity = 0;
            break;
    }
}

Monster::~Monster()
{}

int* Monster::getImageWidth() {
    return &this->imageWidth;
}

int* Monster::getImageHeight() {
    return &this->imageHeight;
}

int Monster::getDirectionalVelocity() {
    return this->directionalVelocity;
}

int Monster::roundNum(int input) {
    int roundDown = input - (input % 55);
    int roundUp = roundDown + 55;
    return ((input - roundDown) < (roundUp - input))? roundDown: roundUp;
}

SDL_Rect* Monster::getSpriteRect() {
    return &this->spriteRect;
}

bool Monster::getInvulnerabilityState() {
    return this->invulnerable;
}

Direction Monster::getDirection() {
    return this->direction;
}

Direction Monster::randomDirection() {
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

HealthBar* Monster::getHealthBar() {
    return &this->healthBar;
}

SDL_Texture* Monster::getGreenTexture() {
    return this->healthBar.getGreenTexture();
}

SDL_Texture* Monster::getRedTexture() {
    return this->healthBar.getRedTexture();
}

SDL_Rect* Monster::getGreenDestRect(int xPosition, int yPosition) {
    return this->healthBar.getGreenDestRect(xPosition, yPosition);
}

SDL_Rect* Monster::getRedDestRect(int xPosition, int yPosition) {
    return this->healthBar.getRedDestRect(xPosition, yPosition);
}

bool Monster::getEffect(ItemType type) {
    switch(type) {
        case FREEZE:
            return this->freezeEffect;
            break;

        case SNAIL:
            return this->snailEffect;
            break;

        default:
            false;
    }
}

void Monster::setEffect(ItemType type, bool state) {
    switch(type) {
        case FREEZE:
            this->freezeEffect = state;
            break;
        case SNAIL:
            this->snailEffect = state;
    }
}

void Monster::incrementX() {
    this->getDestRect()->x += MONSTER_SPEED;
}

void Monster::incrementY() {
    this->getDestRect()->y += MONSTER_SPEED;
}

void Monster::decrementX() {
    this->getDestRect()->x -= MONSTER_SPEED;
}

void Monster::decrementY() {
    this->getDestRect()->y -= MONSTER_SPEED;
}

void Monster::setFrameSize(int totalCol, int totalRow) {
    this->totalFrameCol = totalCol;
    this->imageHeight /= totalRow;
    this->imageWidth /= totalCol;
    this->spriteRect.h = imageHeight;
    this->spriteRect.w = imageWidth;
    this->spriteRect.x = 0;
    switch(this->direction) {
        case UP:
            this->spriteRect.y = spriteRect.h * 8;
            break;

        case LEFT:
            this->spriteRect.y = spriteRect.h * 9;
            break;

        case DOWN:
            this->spriteRect.y = spriteRect.h * 10;
            break;

        case RIGHT:
            this->spriteRect.y = spriteRect.h * 11;
            break;
    }
}

void Monster::walk(bool collisionCheck) {
    this->currentFrame = SDL_GetTicks();

    if(collisionCheck && this->turnCount == 0) {
        this->oppositeDirection();
        turnCount = 1;
    }
    else if(collisionCheck == false ) {
        turnCount = 0;
        if(this->currentFrame - this->pastFrame >= 100) {
            pastFrame = currentFrame;

            if(this->spriteRect.x / this->spriteRect.w > (this->totalFrameCol - 6))
                this->spriteRect.x = 0;
            else
                this->spriteRect.x += this->spriteRect.w;
        }

        this->getDestRect()->x += xVelocity;
        this->getDestRect()->y += yVelocity;
    }

}

void Monster::oppositeDirection() {
    if(SDL_GetTicks() - this->redirectTime <= 500)
        this->direction = this->randomDirection();

    this->redirectTime = SDL_GetTicks();

    switch(this->direction) {
        case UP:
            this->directionalVelocity = VELOCITY_DIRECTION;
            this->direction = DOWN;
            this->xVelocity = 0;
            this->yVelocity = currentYVelocity * directionalVelocity;
            this->incrementY();
            break;

        case LEFT:
            this->directionalVelocity = VELOCITY_DIRECTION;
            this->incrementX();
            this->xVelocity = currentXVelocity * directionalVelocity;
            this->yVelocity = 0;
            this->direction = RIGHT;
            break;

        case DOWN:
            this->directionalVelocity = -VELOCITY_DIRECTION;
            this->decrementY();
            this->xVelocity = 0;
            this->yVelocity = currentYVelocity * directionalVelocity;
            this->direction = UP;
            break;

        case RIGHT:
            this->directionalVelocity = -VELOCITY_DIRECTION;
            this->decrementX();
            this->xVelocity = currentXVelocity * directionalVelocity;
            this->yVelocity = 0;
            this->direction = LEFT;
            break;
    }

    this->setXPosition(this->roundNum(this->getXPosition()));
    this->setYPosition(this->roundNum(this->getYPosition()));
    this->setDirection();
}

void Monster::damaged(int damage) {
    if(this->getInvulnerabilityState() == false) {
        this->setInvulnerabilityState(true);
        this->subtractLife(damage);
        this->setHitTime();
        this->healthBar.setHP(this->getLife());
    }
}

void Monster::setHitTime() {
    this->hitTime = SDL_GetTicks();
}

void Monster::setInvulnerabilityState() {
    if(SDL_GetTicks() - this->hitTime > 2000)
        this->setInvulnerabilityState(false);
}

void Monster::setInvulnerabilityState(bool state) {
    this->invulnerable = state;
    if(state == true) {
        if(this->freezeEffect == false) {
            if(this->direction == UP || this->direction == DOWN)
                this->yVelocity = this->currentYVelocity * this->directionalVelocity;
            else
                this->xVelocity = this->currentXVelocity * this->directionalVelocity;
        }
    }
    else {
        if(this->freezeEffect == false) {
            if(this->direction == UP || this->direction == DOWN)
                this->yVelocity = this->currentYVelocity * this->directionalVelocity;
            else
                this->xVelocity = this->currentXVelocity * this->directionalVelocity;
        }
    }
}

void Monster::subtractLife(int damage) {
    this->setLife(this->getLife() - damage);
}

void Monster::setVelocity(int value) {
    switch(this->direction) {
        case UP: case DOWN:
            this->currentYVelocity = value;
            this->yVelocity = currentYVelocity * directionalVelocity;
            break;

        case LEFT: case RIGHT:
            this->currentXVelocity = value;
            this->xVelocity = currentXVelocity * directionalVelocity;
            break;
    }
}

void Monster::setDirection() {
    if(this->yVelocity > 0)
        this->spriteRect.y = this->spriteRect.h * 10;
    else if(this->xVelocity < 0)
        this->spriteRect.y = this->spriteRect.h * 11;
    else if(this->yVelocity < 0)
        this->spriteRect.y = this->spriteRect.h * 8;
    else if(this->xVelocity > 0)
        this->spriteRect.y = this->spriteRect.h * 9;
}

