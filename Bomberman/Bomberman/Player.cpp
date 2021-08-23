#include "Player.h"

Player::Player(const char* imageLocation, int initXPosition, int initYPosition, PlayerNumber num)
    : Entity(imageLocation, initXPosition * CELL_SIZE, initYPosition * CELL_SIZE, PLAYER, 100), positionHistory(), playerNumber(num), portalTimer(0), healthBar(100)
{}

Player::~Player(){}

SDL_Rect* Player::getSpriteRect() {
    return &this->spriteRect;
}

int* Player::getImageWidth() {
    return &this->spriteRect.w;
}

int* Player::getImageHeight() {
    return &this->spriteRect.h;
}

Direction Player::getDirection() {
    return this->direction;
}

int Player::getPastX() {
    return this->pastX;
}

int Player::getPastY() {
    return this->pastY;
}

int Player::getCooldown() {
    return this->cooldown;
}

int Player::getFlagCount() {
    return this->flagCount;
}

int Player::getBombCount() {
    return this->bombCount;
}

int Player::getCurrentBomb() {
    return this->currentBomb;
}

int Player::getBombRange() {
    return this->bombRange;
}

bool Player::getGhostState() {
    return this->ghost;
}

bool Player::getInvulnerabilityState() {
    return this->invulnerable;
}

PlayerNumber Player::getPlayerNumber() {
    return this->playerNumber;
}

PortalTimer* Player::getPortalTimer() {
    return &this->portalTimer;
}

PositionHistory* Player::getPositionHistory() {
    return &this->positionHistory;
}

std::vector<int>* Player::getXHistory() {
    return this->positionHistory.getXHistory();
}

std::vector<int>* Player::getYHistory() {
    return this->positionHistory.getYHistory();
}

std::vector<Item>* Player::getItems() {
    return &this->items;
}

HealthBar* Player::getHealthBar() {
    return &this->healthBar;
}

SDL_Texture* Player::getGreenTexture() {
    return this->healthBar.getGreenTexture();
}

SDL_Texture* Player::getRedTexture() {
    return this->healthBar.getRedTexture();
}

SDL_Rect* Player::getGreenDestRect(int xPosition, int yPosition) {
    return this->healthBar.getGreenDestRect(xPosition, yPosition);
}

SDL_Rect* Player::getRedDestRect(int xPosition, int yPosition) {
    return this->healthBar.getRedDestRect(xPosition, yPosition);
}

Item* Player::getItem(ItemType type) {
    for(this->itemIterator = this->items.begin(); this->itemIterator < this->items.end(); this->itemIterator++) {
        if(itemIterator->getItemType() == type)
            return &*itemIterator;
    }
}

bool Player::getEffect(ItemType type) {
     switch(type) {
        case ZANIC:
            return this->zanicEffect;
            break;

        case FREEZE:
            return this->freezeEffect;
            break;

        case SNAIL:
            return this->snailEffect;
            break;

        case LASER:
            return this->laserEffect;
            break;

        case F_ITEM:
            return this->FEffect;
            break;

        default:
            return false;
    }
}

void Player::setEffect(ItemType type, bool state) {
    switch(type) {
        case ZANIC:
            this->zanicEffect = state;
            break;

        case FREEZE:
            this->freezeEffect = state;
            break;

        case SNAIL:
            this->snailEffect = state;
            break;

        case LASER:
            this->laserEffect = state;
            break;

        case F_ITEM:
            this->FEffect = state;
            break;
    }
}

void Player::incrementFlagCount() {
    this->flagCount++;
}

void Player::decrementFlagCount() {
    this->flagCount--;
}

void Player::incrementX() {
    this->getDestRect()->x += playerVelocity;
}

void Player::incrementY() {
    this->getDestRect()->y += playerVelocity;
}

void Player::decrementX() {
    this->getDestRect()->x -= playerVelocity;
}

void Player::decrementY() {
    this->getDestRect()->y -= playerVelocity;
}

void Player::setFrameSize(int totalCol, int totalRow) {
    this->spriteRect.x = 0;
    this->spriteRect.y = 0;
    this->spriteRect.w /= totalCol;
    this->spriteRect.h /= totalRow;
    this->totalFrameCol = totalCol - 1;
}

void Player::setDirection(Direction playerDirection) {
    this->direction = playerDirection;
}

void Player::setPastX(int x) {
    this->pastX = x;
}

void Player::setPastY(int y) {
    this->pastY = y;
}

void Player::setCooldown() {
    this->cooldown = SDL_GetTicks();
}

void Player::setGhost(bool state) {
    this->ghost = state;
}

void Player::incrementSpriteFrame(Direction direction) {
    if(this->spriteRect.x / this->spriteRect.w > (this->totalFrameCol - 6))
       this->spriteRect.x = 0;
    else
        this->spriteRect.x += this->spriteRect.w;

    this->spriteRect.y = this->spriteRect.h * (direction);
}

void Player::damaged(int damage) {
    if(this->getInvulnerabilityState() == false) {
        this->setInvulnerabilityState(true);
        this->subtractLife(damage);
        this->setHitTime();
        this->healthBar.setHP(this->getLife());
        std::cout << this->getLife() << std::endl;
    }
}

void Player::setInvulnerabilityState(bool state) {
    this->invulnerable = state;
    if(state == true) {
        if(freezeEffect == false)
            this->playerVelocity = 3;
    }

    else {
       if(this->zanicEffect)
            this->playerVelocity = 10;
        else if(this->snailEffect)
            this->playerVelocity = 2;
        else if(this->freezeEffect)
            this->playerVelocity = 0;
        else
            this->playerVelocity = 5;
    }

}

void Player::setInvulnerabilityState() {
    if(SDL_GetTicks() - this->hitTime > 2000)
        this->setInvulnerabilityState(false);
}

void Player::subtractLife(int damage) {
    this->setLife(this->getLife() - damage);
}

void Player::setHitTime() {
    this->hitTime = SDL_GetTicks();
}

void Player::pickItem(Item item) {
    if(this->getEffect(item.getItemType()) == false) {
        item.setDuration();
        item.setPickUpTime();
        this->items.emplace_back(item);
    }
}

void Player::setVelocity(int value) {
    this->playerVelocity = value;
}

void Player::heal(int value) {
    if(this->getLife() + value > 100)
        this->setLife(100);
    else
        this->setLife(this->getLife() + value);

    std::cout << this->getLife() << std::endl;
    this->healthBar.setHP(this->getLife());
}

void Player::setCurrentBombCount(int value) {
    this->currentBomb = value;
}

void Player::incrementBombCount() {
    this->bombCount++;
}

void Player::incrementCurrentBomb() {
    this->currentBomb++;
}

void Player::decrementCurrentBomb() {
    this->currentBomb--;
}

void Player::incrementBombRange() {
    this->bombRange++;
}
