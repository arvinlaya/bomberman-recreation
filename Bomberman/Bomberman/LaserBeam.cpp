#include "LaserBeam.h"

SDL_Texture* LaserBeam::beamTail;
SDL_Texture* LaserBeam::beamBody;
SDL_Texture* LaserBeam::beamHead;

void LaserBeam::loadLaserBeamIMG(SDL_Renderer* renderer) {
    SDL_Surface* tailSurface = IMG_Load("images/game/laserStart.png");
    SDL_Surface* bodySurface = IMG_Load("images/game/laserBody.png");
    SDL_Surface* headSurface = IMG_Load("images/game/laserEnd.png");

    LaserBeam::beamTail = SDL_CreateTextureFromSurface(renderer, tailSurface);
    LaserBeam::beamBody = SDL_CreateTextureFromSurface(renderer, bodySurface);
    LaserBeam::beamHead = SDL_CreateTextureFromSurface(renderer, headSurface);

    SDL_FreeSurface(tailSurface);
    SDL_FreeSurface(bodySurface);
    SDL_FreeSurface(headSurface);
}

LaserBeam::LaserBeam(int initX, int initY, Direction direction, PlayerNumber source)
    : xPosition(initX), yPosition(initY), shootDirection(direction), playerNumber(source)
{}

LaserBeam::~LaserBeam(){}

int LaserBeam::getXPosition() {
    return this->xPosition;
}

int LaserBeam::getYPosition() {
    return this->yPosition;
}

int LaserBeam::getRange() {
    return this->range;
}

int LaserBeam::getAngle() {
    return this->angle;
}

int LaserBeam::getDirectionalIncrement() {
    return this->directionalIncrement;
}

int LaserBeam::getDuration() {
    return this->duration;
}

Direction LaserBeam::getDirection() {
    return this->shootDirection;
}

SDL_Rect* LaserBeam::getDestRect() {
    return &this->destRect;
}

SDL_Texture* LaserBeam::getTexture() {

    SDL_SetTextureAlphaMod(this->beamTail, this->duration);
    SDL_SetTextureAlphaMod(this->beamBody, this->duration);
    SDL_SetTextureAlphaMod(this->beamHead, this->duration);
    switch(this->shootDirection) {
        case UP: case DOWN:
            if((this->yPosition + this->directionalIncrement) == destRect.y)
                return beamTail;
            else if(this->destRect.y != range)
                return beamBody;
            else
                return beamHead;
            break;

        case LEFT: case RIGHT:
            if((this->xPosition + this->directionalIncrement) == destRect.x)
                return beamTail;
            else if(this->destRect.x != range)
                return beamBody;
            else
                return beamHead;
            break;
    }


}

PlayerNumber LaserBeam::getSource() {
    return this->playerNumber;
}

void LaserBeam::setRange(std::vector<Entity>* blocks) {
    this->destRect.x = xPosition;
    this->destRect.y = yPosition;
    this->destRect.h = CELL_SIZE;
    this->destRect.w = CELL_SIZE;

    int difference = 1500;
    int positionIncrement;
    int blockX, blockY;

    switch(this->shootDirection) {
        case UP:
            this->angle = 270;
            this->directionalIncrement = -CELL_SIZE;
            for(this->blockIterator = blocks->begin(); this->blockIterator < blocks->end(); this->blockIterator++) {
                blockX = blockIterator->getXPosition();
                blockY = blockIterator->getYPosition();
                EntityType type = blockIterator->getEntityType();

                if(type == WALL && xPosition == blockX && yPosition > blockY) {
                    if(difference > yPosition - blockY) {
                        difference = yPosition - blockY;
                        this->range = blockY + CELL_SIZE;
                    }
                }
            }
            break;

        case LEFT:
            this->angle = 180;
            this->directionalIncrement = -CELL_SIZE;
            for(this->blockIterator = blocks->begin(); this->blockIterator < blocks->end(); this->blockIterator++) {
                blockX = blockIterator->getXPosition();
                blockY = blockIterator->getYPosition();
                EntityType type = blockIterator->getEntityType();

                if(type == WALL && yPosition == blockY && xPosition > blockX) {
                    if(difference > xPosition - blockX) {
                        difference = xPosition - blockX;
                        this->range = blockX + CELL_SIZE;
                    }
                }
            }
            break;

        case DOWN:
            this->angle = 90;
            this->directionalIncrement = CELL_SIZE;
            for(this->blockIterator = blocks->begin(); this->blockIterator < blocks->end(); this->blockIterator++) {
                blockX = blockIterator->getXPosition();
                blockY = blockIterator->getYPosition();
                EntityType type = blockIterator->getEntityType();

                if(type == WALL && xPosition == blockX && yPosition < blockY) {
                    if(difference > blockY - yPosition) {
                        difference = blockY - yPosition;
                        this->range = blockY - CELL_SIZE;
                    }
                }
            }
            break;

        case RIGHT:
            this->angle = 0;
            this->directionalIncrement = CELL_SIZE;
            for(this->blockIterator = blocks->begin(); this->blockIterator < blocks->end(); this->blockIterator++) {
                blockX = blockIterator->getXPosition();
                blockY = blockIterator->getYPosition();
                EntityType type = blockIterator->getEntityType();

                if(type == WALL && yPosition == blockY && xPosition < blockX) {
                    if(difference > blockX - xPosition) {
                        difference = blockX - xPosition;
                        this->range = blockX - CELL_SIZE;
                    }
                }
            }
            break;
    }

    if(range == 2000) {
        switch(this->shootDirection) {
            case UP:
                this->range = 55;
                break;

            case LEFT:
                this->range = 55;
                break;

            case DOWN:
                this->range = 550;
                break;

            case RIGHT:
                this->range = 1100;
                break;
        }
    }
}

void LaserBeam::incrementDuration() {
    this->duration += durationIncrement;

    if(duration >= 255)
        this->durationIncrement = -durationIncrement;
}
