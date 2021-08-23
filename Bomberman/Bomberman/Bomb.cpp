#include "Bomb.h"

Bomb::Bomb(int colPosition, int rowPosition, SDL_Renderer* renderer, int rangeLimit)
    : Entity("images/game/bombDetonate.png", colPosition, rowPosition, BOMB, 1), owner(NONE), spawnTime(SDL_GetTicks()), detonateTimer(spawnTime/ 200), explodeAnimateLocation( "images/game/bombExplode.png"),  explodeDestRect{0, 0, CELL_SIZE, CELL_SIZE}, explodeSpriteRect{0, 0, EXPLODE_HEIGHT / EXPLODE_ROW_COUNT, EXPLODE_WIDTH / EXPLODE_COL_COUNT}, detonateRect{0, 0, BOMB_HEIGHT, BOMB_WIDTH / 15}, maxRange(rangeLimit)
{
    SDL_Surface* surface = IMG_Load(this->explodeAnimateLocation);
    this->explodeTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

Bomb::Bomb(int colPosition, int rowPosition, PlayerNumber bombOwner, SDL_Renderer* renderer, int rangeLimit)
    : Entity("images/game/bombDetonate.png", colPosition, rowPosition, BOMB, 1), owner(bombOwner), spawnTime(SDL_GetTicks()), detonateTimer(spawnTime/ 200), explodeAnimateLocation( "images/game/bombExplode.png"),  explodeDestRect{0, 0, CELL_SIZE, CELL_SIZE}, explodeSpriteRect{0, 0, EXPLODE_HEIGHT / EXPLODE_ROW_COUNT, EXPLODE_WIDTH / EXPLODE_COL_COUNT}, detonateRect{0, 0, BOMB_HEIGHT, BOMB_WIDTH / 15}, maxRange(rangeLimit)
{
    SDL_Surface* surface = IMG_Load(this->explodeAnimateLocation);
    this->explodeTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

Bomb::~Bomb(){}

int Bomb::getSpawnTime() {
    return this->spawnTime;
}

Bomb::BombRange Bomb::getRange() {
    return this->range;
}

SDL_Rect* Bomb::getDetonateSprite() {
    return &this->detonateRect;
}

PlayerNumber Bomb::getOwner() {
    return this->owner;
}

void Bomb::setBombRange(const std::vector<Entity>& blocks) {
        this->maxRange *= CELL_SIZE;
        int bombX = this->getXPosition();
        int bombY = this->getYPosition();

        int upDifference = 1500;

        int leftDifference = 1500;

        int downDifference = 1500;

        int rightDifference = 1500;

        int entityX, entityY;

        for(Entity entity: blocks) {
            entityY = entity.getYPosition();
            entityX = entity.getXPosition();

            //Y Range
            if(bombX == entityX) {
                //UP Range
                if(upDifference > bombY - entityY && bombY > entityY) {
                    upDifference = bombY - entityY;
                    this->range.upRange = entityY;
                    if(entity.getEntityType() == WALL)
                        this->range.upRange += CELL_SIZE;
                }
                //DOWN Range
                else if(downDifference > entityY - bombY && bombY < entityY) {
                    downDifference = entityY - bombY;
                    this->range.downRange = entityY;
                    if(entity.getEntityType() == WALL)
                        this->range.downRange -= CELL_SIZE;
                }
            }

            //X Range
            else if(bombY == entityY) {
                //LEFT Range
                if(leftDifference > bombX - entityX && bombX > entityX) {
                    leftDifference = bombX - entityX;
                    this->range.leftRange = entityX;
                    if(entity.getEntityType() == WALL)
                        this->range.leftRange += CELL_SIZE;
                }
                else if(rightDifference > entityX - bombX && entityX > bombX) {
                    rightDifference = entityX - bombX;
                    this->range.rightRange = entityX;
                    if(entity.getEntityType() == WALL)
                        this->range.rightRange -= CELL_SIZE;
                }
            }
        }

    if(this->range.upRange < (this->getYPosition() - maxRange))
        this->range.upRange = this->getYPosition() - maxRange;
    if(this->range.downRange > this->getYPosition() + maxRange)
        this->range.downRange = this->getYPosition() + maxRange;
    if(this->range.leftRange < (this->getXPosition() - maxRange))
        this->range.leftRange = this->getXPosition() - maxRange;
    if(this->range.rightRange > (this->getXPosition() + maxRange))
        this->range.rightRange = this->getXPosition() + maxRange;
}

void Bomb::explode(SDL_Renderer* renderer) {
    if(this->explodeTimer == 0)
        this->explodeTimer = SDL_GetTicks() / 35;

    if(this->explodeTimer < SDL_GetTicks() / 35) {
        this->explodeTimer = SDL_GetTicks() / 35;
        this->incrementExplodeFrame();
    }

    this->explodeDestRect.y = this->getYPosition();
    for(int x = this->getRange().leftRange; x <= this->getRange().rightRange; x += CELL_SIZE) {
        this->explodeDestRect.x = x;
        SDL_RenderCopy(renderer, this->explodeTexture, &this->explodeSpriteRect, &this->explodeDestRect);
    }

    this->explodeDestRect.x = this->getXPosition();
    for(int y = this->getRange().upRange; y <= this->getRange().downRange; y += CELL_SIZE) {
        this->explodeDestRect.y = y;
        SDL_RenderCopy(renderer, this->explodeTexture, &this->explodeSpriteRect, &this->explodeDestRect);
    }
}

void Bomb::incrementDetonateFrameCol() {
    if(detonateTimer < SDL_GetTicks() / 200) {
        detonateTimer = SDL_GetTicks() / 200;
        this->detonateRect.x += this->detonateRect.w;
    }
}

void Bomb::incrementExplodeFrame() {
    if(this->explodeSpriteRect.x <= EXPLODE_WIDTH) {
        this->explodeSpriteRect.x += this->explodeSpriteRect.w;
    }
    else {
        this->explodeSpriteRect.x = 0;
        this->explodeSpriteRect.y += this->explodeSpriteRect.h;
    }

}

void Bomb::setSpawnTime(int time) {
    this->spawnTime = time;
}

