#include "Game.h"

Game::Game(){
   srand(time(NULL));
}
Game::~Game(){}

bool Game::isRunning() {
    return this->running;
}

bool Game::collisionCheck(Player* player) {
    int playerY = player->getYPosition();
    int playerX = player->getXPosition();
    int pastX = player->getPastX();
    int pastY = player->getPastY();

    if(playerY - pastY > CELL_SIZE || playerY - pastY < -CELL_SIZE || playerX - pastX > CELL_SIZE || playerX - pastX < -CELL_SIZE)
        player->setGhost(false);

    if(player->getGhostState() == false) {
        for(Entity& bomb: this->bombs) {
            if(playerY - COLLISION_RANGE < bomb.getYPosition() && playerY > bomb.getYPosition() - CELL_SIZE && playerX - COLLISION_RANGE < bomb.getXPosition() && playerX > bomb.getXPosition() - COLLISION_RANGE)
                return true;
        }
    }

    for(Entity& block: this->blocks) {
        if(playerY - COLLISION_RANGE < block.getYPosition() && playerY > block.getYPosition() - CELL_SIZE && playerX - COLLISION_RANGE < block.getXPosition() && playerX > block.getXPosition() - COLLISION_RANGE)
            return true;
    }

    for(this->itemIterator = this->items.begin(); this->itemIterator < this->items.end(); this->itemIterator++) {
        if(playerY - COLLISION_RANGE < itemIterator->getYPosition() && playerY > itemIterator->getYPosition() - CELL_SIZE && playerX - COLLISION_RANGE < itemIterator->getXPosition() && playerX > itemIterator->getXPosition() - COLLISION_RANGE) {
            player->pickItem(*itemIterator);
            activateItem(&*itemIterator, player);
            this->items.erase(itemIterator);
        }
    }

    for(Monster& monster: this->monsters) {
        if(playerX <= monster.getXPosition() + COLLISION_RANGE && playerX + COLLISION_RANGE >= monster.getXPosition() && playerY + COLLISION_RANGE >= monster.getYPosition() && playerY <= monster.getYPosition() + COLLISION_RANGE) {
            player->damaged(20);
        }
    }

    return false;
}

bool Game::collisionCheck(Monster* monster) {
    int monsterY = monster->getYPosition();
    int monsterX = monster->getXPosition();

    if(monsterY < 55) {
        monster->incrementY();
        return true;
    }
    else if(monsterY > 550) {
        monster->decrementY();
        return true;
    }
    else if(monsterX < 55) {
        monster->incrementX();
        return true;
    }
    else if(monsterX > 1100) {
        monster->decrementX();
        return true;
    }

    for(Entity& block: this->blocks) {
        if(monsterY - COLLISION_RANGE < block.getYPosition() && monsterY > block.getYPosition() - COLLISION_RANGE && monsterX - COLLISION_RANGE < block.getXPosition() && monsterX > block.getXPosition() - COLLISION_RANGE)
            return true;
    }

    for(Entity& bomb: this->bombs) {
        if(monsterY - COLLISION_RANGE < bomb.getYPosition() && monsterY > bomb.getYPosition() - COLLISION_RANGE && monsterX - COLLISION_RANGE < bomb.getXPosition() && monsterX > bomb.getXPosition() - COLLISION_RANGE)
            return true;
    }
    return false;
}

bool Game::collisionCheck(Turtle* turtle) {
    int turtleY = turtle->getYPosition();
    int turtleX = turtle->getXPosition();

    if(turtleY < 55) {
        turtle->incrementY();
        return true;
    }
    else if(turtleY > 550) {
        turtle->decrementY();
        return true;
    }
    else if(turtleX < 55) {
        turtle->incrementX();
        return true;
    }
    else if(turtleX > 1100) {
        turtle->decrementX();
        return true;
    }

    for(Entity& block: this->blocks) {
        if(turtleY - COLLISION_RANGE < block.getYPosition() && turtleY > block.getYPosition() - COLLISION_RANGE && turtleX - COLLISION_RANGE < block.getXPosition() && turtleX > block.getXPosition() - COLLISION_RANGE)
            return true;
    }

    for(Entity& bomb: this->bombs) {
        if(turtleY - COLLISION_RANGE < bomb.getYPosition() && turtleY > bomb.getYPosition() - COLLISION_RANGE && turtleX - COLLISION_RANGE < bomb.getXPosition() && turtleX > bomb.getXPosition() - COLLISION_RANGE)
            return true;
    }
    return false;
}

bool Game::bombDuplicate(Bomb& placedBomb) {
    int bombY = placedBomb.getYPosition();
    int bombX = placedBomb.getXPosition();

    for(Bomb& bomb: this->bombs) {
        if(bomb.getXPosition() ==  bombX && bomb.getYPosition() == bombY) {
            return true;
        }
    }

    return false;
}

int Game::roundNum(int input) {
    int roundDown = input - (input % 55);
    int roundUp = roundDown + 55;
    return ((input - roundDown) < (roundUp - input))? roundDown: roundUp;
}

Player* Game::getPlayer(PlayerNumber playerNumber) {
    for(this->playerIterator = this->players.begin(); this->playerIterator < this->players.end(); this->playerIterator++) {
        if(playerIterator->getPlayerNumber() == playerNumber)
            return &*playerIterator;
    }
    return NULL;
}

Monster* Game::getMonster() {
    int index = rand() % this->monsters.size();
    return &this->monsters[index];
}

Turtle* Game::getTurtle() {
    int index = rand() % this->turtles.size();
    return &this->turtles[index];
}

void Game::explodeBlock(Bomb* bomb) {
    int blockX, blockY, flagX, flagY;
    int bombX = bomb->getXPosition();
    int bombY = bomb->getYPosition();
    int up = bomb->getRange().upRange;
    int left = bomb->getRange().leftRange;
    int down = bomb->getRange().downRange;
    int right = bomb->getRange().rightRange;

    for(this->blockIterator = this->blocks.begin(); this->blockIterator < this->blocks.end(); this->blockIterator++) {
        EntityType type = blockIterator->getEntityType();
        blockX = blockIterator->getXPosition();
        blockY = blockIterator->getYPosition();

        if((bombX == blockX) & (blockY == up || blockY == down) || (bombY == blockY) & (blockX == right || blockX == left)) {
            blockIterator->decrementLife();
            if(type == HARDBRICK) {
                blockIterator->setTexture(this->renderer, IMG_Load(crackedIMG));
            }
        }
    }

    for(this->metalCrateIterator = this->metalCrates.begin(); this->metalCrateIterator < this->metalCrates.end(); this->metalCrateIterator++) {
        blockX = metalCrateIterator->getXPosition();
        blockY = metalCrateIterator->getYPosition();

        if((bombX == blockX) & (blockY == up || blockY == down) || (bombY == blockY) & (blockX == right || blockX == left))
            metalCrateIterator->decrementLife();
    }

}

void Game::explodeEntity(Bomb* bomb) {
    int bombX = bomb->getXPosition();
    int bombY = bomb->getYPosition();
    int up = bomb->getRange().upRange;
    int left = bomb->getRange().leftRange;
    int down = bomb->getRange().downRange;
    int right = bomb->getRange().rightRange;

    int entityX, entityY;

    for(this->playerIterator = this->players.begin(); this->playerIterator < this->players.end(); this->playerIterator++) {
        entityX = this->roundNum(playerIterator->getXPosition());
        entityY = this->roundNum(playerIterator->getYPosition());

        if(((entityX == bombX) && (entityY <= down && entityY >= up)) || ((entityY == bombY) && (entityX <= right && entityX >= left))) {
            if(playerIterator->getInvulnerabilityState() == false)
                playerIterator->damaged(30);
        }
    }

    for(this->monsterIterator = this->monsters.begin(); this->monsterIterator < this->monsters.end(); this->monsterIterator++) {
        entityX = monsterIterator->getXPosition();
        entityY = monsterIterator->getYPosition();
        if(((entityX == bombX) && (entityY <= down && entityY >= up)) || ((entityY == bombY) && (entityX <= right && entityX >= left))) {
            if(monsterIterator->getInvulnerabilityState() == false)
                monsterIterator->damaged(30);
        }
    }

    for(this->turtleIterator = this->turtles.begin(); this->turtleIterator < this->turtles.end(); this->turtleIterator++) {
        entityX = turtleIterator->getXPosition();
        entityY = turtleIterator->getYPosition();
        if(((entityX == bombX) && (entityY <= down && entityY >= up)) || ((entityY == bombY) && (entityX <= right && entityX >= left))) {
            if(turtleIterator->getInvulnerabilityState() == false)
                turtleIterator->damaged(30);

            if(turtleIterator->getLife() <= 0)
                loadFlagCrate(bomb->getOwner());
        }
    }

    for(this->flagIterator = this->flagsOne.begin(); this->flagIterator < this->flagsOne.end(); this->flagIterator++) {
        entityX = flagIterator->getXPosition();
        entityY = flagIterator->getYPosition();

        if(((entityX == bombX) && (entityY <= down && entityY >= up)) || ((entityY == bombY) && (entityX <= right && entityX >= left))) {
            if(flagIterator->getHitTime() >= 1000 || flagIterator->getHitTime() == 0) {
                flagIterator->setHitTime();
                flagIterator->decrementLife();

            }
        }
    }

    for(this->flagIterator = this->flagsTwo.begin(); this->flagIterator < this->flagsTwo.end(); this->flagIterator++) {
        entityX = flagIterator->getXPosition();
        entityY = flagIterator->getYPosition();

        if(((entityX == bombX) && (entityY <= down && entityY >= up)) || ((entityY == bombY) && (entityX <= right && entityX >= left))) {
            if(flagIterator->getHitTime() >= 1000 || flagIterator->getHitTime() == 0) {
                flagIterator->setHitTime();
                flagIterator->decrementLife();

            }
        }
    }
}

void Game::laserEntity(LaserBeam* laserBeam) {
    Direction shootDirection = laserBeam->getDirection();
    Player* targetPlayer = (laserBeam->getSource() == ONE)? this->getPlayer(TWO): this->getPlayer(ONE);
    int laserX = laserBeam->getXPosition();
    int laserY = laserBeam->getYPosition();
    int range = laserBeam->getRange();
    switch(shootDirection) {
        case UP:
            if(targetPlayer->getYPosition() <= laserY && targetPlayer->getYPosition() >= range && this->roundNum(targetPlayer->getXPosition()) == laserX) {
                targetPlayer->damaged(40);
            }

            for(this->monsterIterator = this->monsters.begin(); this->monsterIterator < this->monsters.end(); this->monsterIterator++) {
                if(monsterIterator->getYPosition() <= laserY && monsterIterator->getYPosition() >= range && this->roundNum(monsterIterator->getXPosition()) == laserX) {
                    monsterIterator->damaged(40);
                }
            }

            for(this->turtleIterator = this->turtles.begin(); this->turtleIterator < this->turtles.end(); this->turtleIterator++) {
                if(turtleIterator->getYPosition() <= laserY && turtleIterator->getYPosition() >= range && this->roundNum(turtleIterator->getXPosition()) == laserX) {
                    turtleIterator->damaged(40);
                }
            }

            for(this->blockIterator = this->blocks.begin(); this->blockIterator < this->blocks.end(); this->blockIterator++) {
                if(blockIterator->getYPosition() <= laserY && blockIterator->getYPosition() >= range && this->roundNum(blockIterator->getXPosition()) == laserX) {
                    blockIterator->decrementLife();
                    if(blockIterator->getEntityType() == HARDBRICK)
                        blockIterator->setTexture(this->renderer, IMG_Load(crackedIMG));
                }
            }
            break;

        case LEFT:
            if(targetPlayer->getXPosition() <= laserX && targetPlayer->getXPosition() >= range && this->roundNum(targetPlayer->getYPosition()) == laserY) {
                targetPlayer->damaged(40);
            }

            for(this->monsterIterator = this->monsters.begin(); this->monsterIterator < this->monsters.end(); this->monsterIterator++) {
                if(monsterIterator->getXPosition() <= laserX && monsterIterator->getXPosition() >= range && this->roundNum(monsterIterator->getYPosition()) == laserY) {
                    monsterIterator->damaged(40);
                }
            }

            for(this->turtleIterator = this->turtles.begin(); this->turtleIterator < this->turtles.end(); this->turtleIterator++) {
                if(turtleIterator->getXPosition() <= laserX && turtleIterator->getXPosition() >= range && this->roundNum(turtleIterator->getYPosition()) == laserY) {
                    turtleIterator->damaged(40);
                }
            }

            for(this->blockIterator = this->blocks.begin(); this->blockIterator < this->blocks.end(); this->blockIterator++) {
                if(blockIterator->getXPosition() <= laserX && blockIterator->getXPosition() >= range && this->roundNum(blockIterator->getYPosition()) == laserY) {
                    blockIterator->decrementLife();
                    if(blockIterator->getEntityType() == HARDBRICK)
                        blockIterator->setTexture(this->renderer, IMG_Load("images/candyland/blocks/crackedHardBrick.png"));
                }
            }
            break;

        case DOWN:
            if(targetPlayer->getYPosition() >= laserY && targetPlayer->getYPosition() <= range && targetPlayer->getXPosition() == laserX) {
                targetPlayer->damaged(40);
            }

            for(this->monsterIterator = this->monsters.begin(); this->monsterIterator < this->monsters.end(); this->monsterIterator++) {
                if(monsterIterator->getYPosition() >= laserY && monsterIterator->getYPosition() <= range && this->roundNum(monsterIterator->getXPosition()) == laserX) {
                    monsterIterator->damaged(40);
                }
            }

            for(this->turtleIterator = this->turtles.begin(); this->turtleIterator < this->turtles.end(); this->turtleIterator++) {
                if(turtleIterator->getYPosition() >= laserY && turtleIterator->getYPosition() <= range && this->roundNum(turtleIterator->getXPosition()) == laserX) {
                    turtleIterator->damaged(40);
                }
            }

            for(this->blockIterator = this->blocks.begin(); this->blockIterator < this->blocks.end(); this->blockIterator++) {
                if(blockIterator->getYPosition() >= laserY && blockIterator->getYPosition() <= range && this->roundNum(blockIterator->getXPosition()) == laserX) {
                    blockIterator->decrementLife();
                    if(blockIterator->getEntityType() == HARDBRICK)
                        blockIterator->setTexture(this->renderer, IMG_Load("images/candyland/blocks/crackedHardBrick.png"));
                }
            }
            break;

        case RIGHT:
            if(targetPlayer->getXPosition() >= laserX && targetPlayer->getXPosition() <= range && this->roundNum(targetPlayer->getYPosition()) == laserY) {
                targetPlayer->damaged(40);
            }

            for(this->monsterIterator = this->monsters.begin(); this->monsterIterator < this->monsters.end(); this->monsterIterator++) {
                if(monsterIterator->getXPosition() >= laserX && monsterIterator->getXPosition() <= range && this->roundNum(monsterIterator->getYPosition()) == laserY) {
                    monsterIterator->damaged(40);
                }
            }

            for(this->turtleIterator = this->turtles.begin(); this->turtleIterator < this->turtles.end(); this->turtleIterator++) {
                if(turtleIterator->getXPosition() >= laserX && turtleIterator->getXPosition() <= range && this->roundNum(turtleIterator->getYPosition()) == laserY) {
                    turtleIterator->damaged(40);
                }
            }

            for(this->blockIterator = this->blocks.begin(); this->blockIterator < this->blocks.end(); this->blockIterator++) {
                if(blockIterator->getXPosition() >= laserX && blockIterator->getXPosition() <= range && this->roundNum(blockIterator->getYPosition()) == laserY) {
                    blockIterator->decrementLife();
                    if(blockIterator->getEntityType() == HARDBRICK)
                        blockIterator->setTexture(this->renderer, IMG_Load("images/candyland/blocks/crackedHardBrick.png"));
                }
            }
            break;
    }
}

void Game::activateItem(Item* item,  Player* player) {
    ItemType type = item->getItemType();
    Player* targetPlayer = (player->getPlayerNumber() == ONE)? this->getPlayer(TWO): this->getPlayer(ONE);
    switch(type) {
        case BAZOOKA: {
                EntityType targetType;
                switch(rand() % 3) {
                    case 0:
                        targetType = PLAYER;
                        break;

                    case 1:
                        targetType = MONSTER;
                        break;

                    case 2:
                        targetType = TURTLE;
                        break;
                }
                this->spawnRocket(player->getXPosition(), player->getYPosition(), TURTLE, player);
            }
            break;

        case ZANIC:
            std::cout << "ZANIC ACT" << std::endl;
            this->activateZanic(player);
            break;

        case FREEZE:
            std::cout << "FREEZE ACT" << std::endl;
            this->activateFreeze(player);
            break;

        case LASER:
            std::cout << "LASER ACT" << std::endl;
            this->activateLaser(player);
            break;

        case SMITE:
            std::cout << "SMITE ACT" << std::endl;
            this->activateSmite(player);
            break;

        case SNAIL:
            std::cout << "SNAIL ACT" << std::endl;
            this->activateSnail(player);
            break;

        case PORTAL:
            std::cout << "PORTAL ACT" << std::endl;
            this->activatePortal(item, player);
            break;

        case JUMBLE:
            this->activateJumble(player);
            break;

        case HERB:
            std::cout << "HERB ACT" << std::endl;
            this->activateHerb(player);
            break;

        case F_ITEM:
            std::cout << "F ACT" << std::endl;
            this->activateF(player);
            break;

        case BOMB_ADD:
            std::cout << "BOMB ADD ACT" << std::endl;
            this->activateBombAdd(player);
            break;

        case RANGE_ADD:
            std::cout << "RANGE ADD ACT" << std::endl;
            this->activateRangeAdd(player);
            break;
    }
}

void Game::deactivateItem(Item* item, Player* player) {
    ItemType type = item->getItemType();
    Player* targetPlayer = (player->getPlayerNumber() == ONE)? this->getPlayer(TWO): this->getPlayer(ONE);
    switch(type) {
        case ZANIC:
            std::cout << "ZANIC DEACT" << std::endl;
            this->deactivateZanic(player);
            break;

        case FREEZE:
            std::cout << "FREEZE DEACT" << std::endl;
            player->setEffect(FREEZE, false);
            this->deactivateFreeze(player);
            break;

        case LASER:
            std::cout << "LASER DEACT" << std::endl;
            this->deactivateLaser(player);
            break;

        case SMITE:
            std::cout << "SMITE DEACT" << std::endl;
            this->deactivateSmite(player);
            break;

        case SNAIL:
            std::cout << "SNAIL DEACT" << std::endl;
            this->deactivateSnail(player);
            break;

        case PORTAL:
            std::cout << "PORTAL DEACT" << std::endl;
            this->deactivatePortal(item, player);
            break;

        case F_ITEM:
            std::cout << "F DEACT" << std::endl;
            this->deactivateF(player);
            break;
    }
}

void Game::spawnRocket(int colPosition, int rowPosition, EntityType target, Player* player) {
    if(this->monsters.size() <= 0 && target == MONSTER || this->turtles.size() <= 0 && target == TURTLE)
        target = PLAYER;

    if(target == MONSTER) {
        Monster* targetMonster = this->getMonster();
        Rocket rocket(player->getXPosition(), player->getYPosition(), targetMonster);
        SDL_Surface* surface = IMG_Load(rocket.getImageSource());
        rocket.setTexture(this->renderer, surface);
        this->rockets.emplace_back(rocket);
        SDL_FreeSurface(surface);
    }
    else if(target == PLAYER) {
        Player* targetPlayer = (player->getPlayerNumber() == ONE)? this->getPlayer(TWO): this->getPlayer(ONE);
        Rocket rocket(player->getXPosition(), player->getYPosition(), targetPlayer);
        SDL_Surface* surface = IMG_Load(rocket.getImageSource());
        rocket.setTexture(this->renderer, surface);
        this->rockets.emplace_back(rocket);
        SDL_FreeSurface(surface);
    }
    else {
        Turtle* targetTurtle = this->getTurtle();
        Rocket rocket(player->getXPosition(), player->getYPosition(), targetTurtle);
        SDL_Surface* surface = IMG_Load(rocket.getImageSource());
        rocket.setTexture(this->renderer, surface);
        this->rockets.emplace_back(rocket);
        SDL_FreeSurface(surface);
    }


}

void Game::activateZanic(Player* source) {
    if(source->getEffect(ZANIC)) {
        source->getItem(ZANIC)->setDuration();
    }
    source->setEffect(ZANIC, true);
    source->setVelocity(PLAYER_SPEED * 2);

}

void Game::deactivateZanic(Player* source) {
    source->setEffect(ZANIC, false);

    if(source->getEffect(FREEZE))
        source->setVelocity(0);
    else if(source->getEffect(SNAIL))
        source->setVelocity(PLAYER_SPEED - 3);
    else
        source->setVelocity(PLAYER_SPEED);
}

void Game::activateFreeze(Player* source) {
    Player* targetPlayer = (source->getPlayerNumber() == ONE)? this->getPlayer(TWO): this->getPlayer(ONE);
    if(targetPlayer->getEffect(FREEZE)) {
        source->getItem(FREEZE)->setDuration();
    }
    targetPlayer->setEffect(FREEZE, true);
    targetPlayer->setVelocity(0);


    for(this->monsterIterator = this->monsters.begin(); this->monsterIterator < this->monsters.end(); this->monsterIterator++) {
        monsterIterator->setEffect(FREEZE, true);
        monsterIterator->setVelocity(0);
    }
}

void Game::deactivateFreeze(Player* source) {
    Player* targetPlayer = (source->getPlayerNumber() == ONE)? this->getPlayer(TWO): this->getPlayer(ONE);
    targetPlayer->setEffect(FREEZE, false);

    if(targetPlayer->getEffect(ZANIC))
        targetPlayer->setVelocity(PLAYER_SPEED * 2);
    else if(targetPlayer->getEffect(SNAIL))
        targetPlayer->setVelocity(PLAYER_SPEED - 3);
    else
        targetPlayer->setVelocity(PLAYER_SPEED);


    for(this->monsterIterator = this->monsters.begin(); this->monsterIterator < this->monsters.end(); this->monsterIterator++) {
        monsterIterator->setEffect(FREEZE, false);

        if(monsterIterator->getEffect(SNAIL))
            monsterIterator->setVelocity((MONSTER_SPEED - 1) * monsterIterator->getDirectionalVelocity());
        else
            monsterIterator->setVelocity(MONSTER_SPEED * monsterIterator->getDirectionalVelocity());
    }

}

void Game::activateSnail(Player* source) {
    Player* targetPlayer = (source->getPlayerNumber() == ONE)? this->getPlayer(TWO): this->getPlayer(ONE);

    if(targetPlayer->getEffect(SNAIL)) {
        source->getItem(SNAIL)->setDuration();
    }
    targetPlayer->setEffect(SNAIL, true);
    if(targetPlayer->getEffect(FREEZE) == false)
        targetPlayer->setVelocity(PLAYER_SPEED - 3);

    for(this->monsterIterator = this->monsters.begin(); this->monsterIterator < this->monsters.end(); this->monsterIterator++) {
        monsterIterator->setEffect(SNAIL, true);

        if(monsterIterator->getEffect(FREEZE) == false)
            monsterIterator->setVelocity(MONSTER_SPEED - 1);
    }
}

void Game::deactivateSnail(Player* source) {
    Player* targetPlayer = (source->getPlayerNumber() == ONE)? this->getPlayer(TWO): this->getPlayer(ONE);
    targetPlayer->setEffect(SNAIL, false);
    if(targetPlayer->getEffect(FREEZE) == false)
        targetPlayer->setVelocity(PLAYER_SPEED);

    for(this->monsterIterator = this->monsters.begin(); this->monsterIterator < this->monsters.end(); this->monsterIterator++) {
        monsterIterator->setEffect(SNAIL, false);

        if(monsterIterator->getEffect(FREEZE) == false)
            monsterIterator->setVelocity(MONSTER_SPEED);
    }
}

void Game::activateLaser(Player* source) {
    if(source->getEffect(LASER))
        source->getItem(LASER)->setDuration();
    source->setEffect(LASER, true);
}

void Game::deactivateLaser(Player* source) {
    source->setEffect(LASER, false);
}

void Game::shootLaser(Player* source) {
    LaserBeam laserBeam(this->roundNum(source->getXPosition()), this->roundNum(source->getYPosition()), source->getDirection(), source->getPlayerNumber());
    laserBeam.setRange(&this->blocks);
    this->laserBeams.emplace_back(laserBeam);
}

void Game::activateJumble(Player* source) {
    Player* targetPlayer = (source->getPlayerNumber() == ONE)? this->getPlayer(TWO): this->getPlayer(ONE);
    source->damaged(0);
    targetPlayer->damaged(0);

    Entity* currentNode;
    Entity* nextNode;
    std::vector<Entity*> elements;
    std::vector<Entity*> elementIterator;
    std::vector<int> elementIndex;
    int population;

    for(this->playerIterator = this->players.begin(); this->playerIterator < this->players.end(); this->playerIterator++)
        elements.emplace_back(&*playerIterator);

    for(this->monsterIterator = this->monsters.begin(); this->monsterIterator < this->monsters.end(); this->monsterIterator++)
        elements.emplace_back(&*monsterIterator);

    for(this->turtleIterator = this->turtles.begin(); this->turtleIterator < this->turtles.end(); this->turtleIterator++)
        elements.emplace_back(&*turtleIterator);

    population = elements.size();

    std::unordered_set<int> indexes;
    while(indexes.size() < population) {
        indexes.insert(rand() % population);
    }
    for(int index: indexes)
        elementIndex.emplace_back(index);

    for(int x = 0; x < population-1; x++) {
        currentNode = elements.at(elementIndex.at(x));
        nextNode = elements.at(elementIndex.at(x+1));
        currentNode->setXPosition(this->roundNum(nextNode->getXPosition()));
        currentNode->setYPosition(this->roundNum(nextNode->getYPosition()));
    }
    currentNode = elements.at(elementIndex.at(population-1));;
    nextNode = elements.at(elementIndex.at(0));
    currentNode->setXPosition(this->roundNum(nextNode->getXPosition()));
    currentNode->setYPosition(this->roundNum(nextNode->getYPosition()));

}

void Game::activatePortal(Item* item, Player* source) {
    if(this->turtles.size() > 0) {
        Turtle* turtle = &this->turtles.at(0);
        this->portals.emplace_back(item->getXPosition(), item->getYPosition(), this->roundNum(turtle->getXPosition()), this->roundNum(turtle->getYPosition()), this->renderer);
    }
}

void Game::deactivatePortal(Item* item, Player* source) {
    this->portals.erase(this->portals.begin());
}

void Game::activateSmite(Player* source) {
    Player* targetPlayer = (source->getPlayerNumber() == ONE)? this->getPlayer(TWO): this->getPlayer(ONE);

    this->clouds.emplace_back(targetPlayer);
}

void Game::deactivateSmite(Player* source) {
    this->clouds.erase(clouds.begin());
}

void Game::activateHerb(Player* source) {
    source->heal(50);
}

void Game::activateF(Player* source) {
    source->setEffect(F_ITEM, true);
}

void Game::deactivateF(Player* source) {
    source->setEffect(F_ITEM, false);
}

void Game::activateBombAdd(Player* source) {
    source->incrementBombCount();
}

void Game::activateRangeAdd(Player* source) {
    source->incrementBombRange();
}

void Game::initialize(const char* title, int gameWidth, int gameHeight, bool fullscreen) {
    keystates = SDL_GetKeyboardState(NULL);
    int flag = (fullscreen)? SDL_WINDOW_FULLSCREEN: 0;

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "SDL INITIALIZED" << std::endl;

        this->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, gameWidth, gameHeight, flag);
        if(window)
            std::cout << "WINDOW INITIALIZED" << std::endl;

        this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if(this->renderer)
            std::cout << "RENDERER INITIALIZED" << std::endl;

        this->running = true;
    }
    else {
        std::cout << "INITIALIZING ERROR" << std::endl;
        this->running = false;
    }
}

void Game::handleEvent() {

    //Player 1 controls
    Player* playerOne = this->getPlayer(ONE);

    if(this->keystates[SDL_SCANCODE_UP]) {
        if(playerOne->getYPosition() > 55) {
            playerOne->incrementSpriteFrame(UP);
            playerOne->decrementY();
            if(this->collisionCheck(playerOne))
                playerOne->incrementY();
        }
    }
    else if(this->keystates[SDL_SCANCODE_LEFT]) {
        if(playerOne->getXPosition() > 55) {
            playerOne->incrementSpriteFrame(LEFT);
            playerOne->decrementX();
            if(this->collisionCheck(playerOne))
                playerOne->incrementX();
        }
    }
    else if(this->keystates[SDL_SCANCODE_DOWN]) {
        if(playerOne->getYPosition() < 550) {
            playerOne->incrementSpriteFrame(DOWN);
            playerOne->incrementY();
            if(this->collisionCheck(playerOne))
                playerOne->decrementY();
        }
    }
    else if(this->keystates[SDL_SCANCODE_RIGHT]) {
        if(playerOne->getXPosition() < 1100) {
            playerOne->incrementSpriteFrame(RIGHT);
            playerOne->incrementX();
            if(this->collisionCheck(playerOne))
                playerOne->decrementX();
        }
    }

    if(playerOne->getEffect(F_ITEM)) {
        int playerX = this->roundNum(playerOne->getXPosition());
        int playerY = this->roundNum(playerOne->getYPosition());
        playerOne->getPositionHistory()->inputHistory(playerX, playerY, playerOne->getFlagCount());
    }

    //Player 2 controls
    Player* playerTwo = this->getPlayer(TWO);
    if(this->keystates[SDL_SCANCODE_W]) {
        if(playerTwo->getYPosition() > 55) {
            playerTwo->incrementSpriteFrame(UP);
            playerTwo->decrementY();
            if(this->collisionCheck(playerTwo))
                playerTwo->incrementY();
        }
    }
    else if(this->keystates[SDL_SCANCODE_A]) {
        if(playerTwo->getXPosition() > 55) {
            playerTwo->incrementSpriteFrame(LEFT);
            playerTwo->decrementX();
            if(this->collisionCheck(playerTwo))
                playerTwo->incrementX();
        }
    }
    else if(this->keystates[SDL_SCANCODE_S]) {
        if(playerTwo->getYPosition() < 550) {
            playerTwo->incrementSpriteFrame(DOWN);
            playerTwo->incrementY();
            if(this->collisionCheck(playerTwo))
                playerTwo->decrementY();
        }
    }
    else if(this->keystates[SDL_SCANCODE_D]) {
        if(playerTwo->getXPosition() < 1100) {
            playerTwo->incrementSpriteFrame(RIGHT);
            playerTwo->incrementX();
            if(this->collisionCheck(playerTwo))
                playerTwo->decrementX();
        }
    }

    if(playerTwo->getEffect(F_ITEM)) {
        int playerX = this->roundNum(playerTwo->getXPosition());
        int playerY = this->roundNum(playerTwo->getYPosition());
        playerTwo->getPositionHistory()->inputHistory(playerX, playerY, playerTwo->getFlagCount());
    }

    while(SDL_PollEvent(&this->event)) {
        switch(this->event.type) {
            case SDL_QUIT:
                this->running = false;
                break;

            case SDL_KEYDOWN:
                switch(event.key.keysym.sym) {
                    //Player 1
                    case SDLK_UP:
                        this->getPlayer(ONE)->setDirection(UP);
                        break;

                    case SDLK_LEFT:
                        this->getPlayer(ONE)->setDirection(LEFT);
                        break;

                    case SDLK_DOWN:
                        this->getPlayer(ONE)->setDirection(DOWN);
                        break;

                    case SDLK_RIGHT:
                        this->getPlayer(ONE)->setDirection(RIGHT);
                        break;

                    case SDLK_l:
                        if(this->getPlayer(ONE)->getEffect(LASER) == false)
                            this->spawnBomb(this->getPlayer(ONE));
                        else {
                            if(SDL_GetTicks() - this->getPlayer(ONE)->getCooldown() >= 500) {
                                this->shootLaser(this->getPlayer(ONE));
                                this->getPlayer(ONE)->setCooldown();
                            }
                        }

                        break;

                    //Player 2
                    case SDLK_w:
                        this->getPlayer(TWO)->setDirection(UP);
                        break;

                    case SDLK_a:
                        this->getPlayer(TWO)->setDirection(LEFT);
                        break;

                    case SDLK_s:
                        this->getPlayer(TWO)->setDirection(DOWN);
                        break;

                    case SDLK_d:
                        this->getPlayer(TWO)->setDirection(RIGHT);
                        break;

                    case SDLK_g:
                        if(this->getPlayer(TWO)->getEffect(LASER) == false)
                            this->spawnBomb(this->getPlayer(TWO));
                        else {
                            if(SDL_GetTicks() - this->getPlayer(TWO)->getCooldown() >= 500) {
                                this->shootLaser(this->getPlayer(TWO));
                                this->getPlayer(TWO)->setCooldown();
                            }
                        }
                        break;
                }
                break;

        }
    }


}

void Game::update() {

    this->timer = SDL_GetTicks();

    SDL_RenderClear(this->renderer);

    //Loads Stage
    SDL_RenderCopy(this->renderer, this->texture, NULL, NULL);

    //Loads Flag
    //Player one flag
    int index = 1;
    Player* playerOne = this->getPlayer(ONE);
    for(this->flagIterator = this->flagsOne.begin(); this->flagIterator < this->flagsOne.end(); this->flagIterator++) {
        if(playerOne->getEffect(F_ITEM) && playerOne->getPositionHistory()->getSize() > playerOne->getFlagCount()) {
            flagIterator->setXPosition(playerOne->getXHistory()->at(index));
            flagIterator->setYPosition(playerOne->getYHistory()->at(index));
            index++;
        }

        SDL_RenderCopy(this->renderer, flagIterator->getTexture(), NULL, flagIterator->getDestRect());

        if(flagIterator->getLife() <= 0) {
            this->flagsOne.erase(flagIterator);
            this->getPlayer(ONE)->decrementFlagCount();
        }
    }

    //Player two flag
    index = 1;
    Player* playerTwo = this->getPlayer(TWO);
    for(this->flagIterator = this->flagsTwo.begin(); this->flagIterator < this->flagsTwo.end(); this->flagIterator++) {
        if(playerTwo->getEffect(F_ITEM) && playerTwo->getPositionHistory()->getSize() > playerTwo->getFlagCount()) {
            flagIterator->setXPosition(playerTwo->getXHistory()->at(index));
            flagIterator->setYPosition(playerTwo->getYHistory()->at(index));
            index++;
        }

        SDL_RenderCopy(this->renderer, flagIterator->getTexture(), NULL, flagIterator->getDestRect());

        if(flagIterator->getLife() <= 0) {
            this->flagsTwo.erase(flagIterator);
            this->getPlayer(TWO)->decrementFlagCount();
        }
    }


    //Loads Block
    for(this->blockIterator = this->blocks.begin(); this->blockIterator < this->blocks.end(); this->blockIterator++) {
        if(blockIterator->getLife() <= 0) {
            switch(blockIterator->getEntityType()) {
                case BARREL:
                    this->spawnBomb(&*blockIterator);
                    break;

                case CRATE: case COMMON_CRATE:
                    this->spawnItem(&*blockIterator);
                    break;
            }
            this->blocks.erase(blockIterator);
        }

        SDL_RenderCopy(this->renderer, blockIterator->getTexture(), NULL, blockIterator->getDestRect());
    }

    //Loads Flag armor
    for(this->metalCrateIterator = this->metalCrates.begin(); this->metalCrateIterator < this->metalCrates.end(); this->metalCrateIterator++) {
        if(metalCrateIterator->getLife() <= 0)
            metalCrates.erase(metalCrateIterator);

        SDL_RenderCopy(this->renderer, metalCrateIterator->getTexture(), NULL, metalCrateIterator->getDestRect());
    }

    //Loads Item
    for(this->itemIterator = this->items.begin(); this->itemIterator < this->items.end(); this->itemIterator++)
        SDL_RenderCopy(this->renderer, itemIterator->getTexture(), NULL, itemIterator->getDestRect());

    for(this->rocketIterator = this->rockets.begin(); this->rocketIterator < this->rockets.end(); this->rocketIterator++) {
        if(rocketIterator->rocketCollision())
            rockets.erase(rocketIterator);
        rocketIterator->track();
        SDL_RenderCopyEx(this->renderer, rocketIterator->getTexture(), NULL, rocketIterator->getDestRect(), rocketIterator->getAngle(), NULL, SDL_FLIP_NONE);
    }

    //Loads Portal
    for(this->portalIterator = this->portals.begin(); this->portalIterator < this->portals.end(); this->portalIterator++) {
        SDL_RenderCopy(this->renderer, portalIterator->getSourceTexture(), NULL, portalIterator->getSourceRect());
        SDL_RenderCopy(this->renderer, portalIterator->getDestinationTexture(), NULL, portalIterator->getDestinationRect());

        for(this->playerIterator = this->players.begin(); this->playerIterator < this->players.end(); this->playerIterator++) {
            int playerX = this->roundNum(playerIterator->getXPosition());
            int playerY = this->roundNum(playerIterator->getYPosition());

            if(portalIterator->inside(playerX, playerY, &*playerIterator)) {
                if(playerIterator->getPortalTimer()->getTime() >= 2000 && playerIterator->getPortalTimer()->getCooldown() >= 500) {
                    int portalX = this->roundNum(playerIterator->getXPosition());
                    int portalY = this->roundNum(playerIterator->getYPosition());
                    if((portalX == portalIterator->getSourceRect()->x && portalY == portalIterator->getSourceRect()->y) || (portalX == portalIterator->getDestinationRect()->x && portalY == portalIterator->getDestinationRect()->y))
                        portalIterator->teleport(portalX, portalY, &*playerIterator);
                }
            }
        }
    }

    //Loads Bomb
    for(this->bombIterator = this->bombs.begin(); this->bombIterator < this->bombs.end(); this->bombIterator++) {
        int duration = this->timer - this->bombIterator->getSpawnTime();

        if(this->timer - bombIterator->getSpawnTime() < 3000) {
            bombIterator->incrementDetonateFrameCol();
            SDL_RenderCopy(this->renderer, bombIterator->getTexture(), bombIterator->getDetonateSprite(), bombIterator->getDestRect());
        }
        if(duration > 3000 && duration < 3500) {
            this->bombIterator->explode(this->renderer);
            this->explodeEntity(&*bombIterator);
        }
        else if(duration > 3500) {
            this->explodeBlock(&*bombIterator);

            if(bombIterator->getOwner() == ONE)
                this->getPlayer(ONE)->decrementCurrentBomb();
            else if(bombIterator->getOwner() == TWO)
                this->getPlayer(TWO)->decrementCurrentBomb();

            this->bombs.erase(this->bombs.begin());
        }
    }

    for(this->barrelBombsIterator = this->barrelBombs.begin(); this->barrelBombsIterator < this->barrelBombs.end(); this->barrelBombsIterator++) {
        this->barrelBombsIterator->explode(this->renderer);
        int duration = this->timer - barrelBombsIterator->getSpawnTime();
        if(this->timer - this->barrelBombsIterator->getSpawnTime() > 500) {
            this->explodeEntity(&*barrelBombsIterator);
            this->explodeBlock(&*barrelBombsIterator);
            this->barrelBombs.erase(this->barrelBombs.begin());
        }
    }

    //Loads Monster
    for(this->monsterIterator = this->monsters.begin(); this->monsterIterator < this->monsters.end(); this->monsterIterator++) {
        SDL_RenderCopy(this->renderer, monsterIterator->getRedTexture(), NULL, monsterIterator->getRedDestRect(monsterIterator->getXPosition(), monsterIterator->getYPosition()));
        SDL_RenderCopy(this->renderer, monsterIterator->getGreenTexture(), NULL, monsterIterator->getGreenDestRect(monsterIterator->getXPosition(), monsterIterator->getYPosition()));

        monsterIterator->walk(collisionCheck(&*monsterIterator));
        if(monsterIterator->getInvulnerabilityState()) {
            monsterIterator->setInvulnerabilityState();
            if((SDL_GetTicks()/50) % 2 == 0)
                continue;
        }
        SDL_RenderCopy(this->renderer, monsterIterator->getTexture(), monsterIterator->getSpriteRect(), monsterIterator->getDestRect());
        if(monsterIterator->getLife() <= 0)
            monsters.erase(monsterIterator);
    }

    for(this->turtleIterator = this->turtles.begin(); this->turtleIterator < this->turtles.end(); this->turtleIterator++) {
        turtleIterator->walk(collisionCheck(&*turtleIterator));
        SDL_RenderCopy(this->renderer, turtleIterator->getRedTexture(), NULL, turtleIterator->getRedDestRect(turtleIterator->getXPosition(), turtleIterator->getYPosition()));
        SDL_RenderCopy(this->renderer, turtleIterator->getGreenTexture(), NULL, turtleIterator->getGreenDestRect(turtleIterator->getXPosition(), turtleIterator->getYPosition()));

        if(turtleIterator->getLife() <= 0)
            turtles.erase(turtleIterator);

        if(turtleIterator->getInvulnerabilityState()) {
            turtleIterator->setInvulnerabilityState();
            if((SDL_GetTicks()/50) % 2 == 0)
                continue;
        }
        SDL_RenderCopy(this->renderer, turtleIterator->getTexture(), turtleIterator->getSpriteRect(), turtleIterator->getDestRect());
    }

    // Loads Laser beam
    for(this->laserBeamIterator = this->laserBeams.begin(); this->laserBeamIterator < this->laserBeams.end(); this->laserBeamIterator++) {
        switch(laserBeamIterator->getDirection()) {
            case UP: case DOWN:
                while(laserBeamIterator->getDestRect()->y != laserBeamIterator->getRange()) {
                    laserBeamIterator->getDestRect()->y += laserBeamIterator->getDirectionalIncrement();
                    SDL_RenderCopyEx(this->renderer, laserBeamIterator->getTexture(), NULL, laserBeamIterator->getDestRect(), laserBeamIterator->getAngle(), NULL, SDL_FLIP_NONE);
                }
                laserBeamIterator->getDestRect()->y = laserBeamIterator->getYPosition();
                break;

            case LEFT: case RIGHT:
                while(laserBeamIterator->getDestRect()->x != laserBeamIterator->getRange()) {
                    laserBeamIterator->getDestRect()->x += laserBeamIterator->getDirectionalIncrement();
                    SDL_RenderCopyEx(this->renderer, laserBeamIterator->getTexture(), NULL, laserBeamIterator->getDestRect(), laserBeamIterator->getAngle(), NULL, SDL_FLIP_NONE);
                }
                laserBeamIterator->getDestRect()->x = laserBeamIterator->getXPosition();
                break;
        }

        laserBeamIterator->incrementDuration();
        if(laserBeamIterator->getDuration() <= 0) {
            laserEntity(&*laserBeamIterator);
            this->laserBeams.erase(laserBeamIterator);
        }


    }

    //Loads Player
    for(this->playerIterator = this->players.begin(); this->playerIterator < this->players.end(); this->playerIterator++) {
        if(this->bombs.size() <= 0)
            playerIterator->setCurrentBombCount(0);

        std::vector<Item>* playerItems = playerIterator->getItems();
        playerIterator->getHealthBar()->setHP(playerIterator->getLife());
        SDL_RenderCopy(this->renderer, playerIterator->getRedTexture(), NULL, playerIterator->getRedDestRect(playerIterator->getXPosition(), playerIterator->getYPosition()));
        SDL_RenderCopy(this->renderer, playerIterator->getGreenTexture(), NULL, playerIterator->getGreenDestRect(playerIterator->getXPosition(), playerIterator->getYPosition()));

        for(this->itemIterator = playerItems->begin(); this->itemIterator < playerItems->end(); this->itemIterator++) {
            if(this->timer >= itemIterator->getDuration()) {
                this->deactivateItem(&*itemIterator, &*playerIterator);
                playerItems->erase(itemIterator);
            }
        }

        if(playerIterator->getInvulnerabilityState()) {
            playerIterator->setInvulnerabilityState();
            if((SDL_GetTicks()/50) % 2 == 0)
                continue;
        }

        SDL_RenderCopy(this->renderer, playerIterator->getTexture(), playerIterator->getSpriteRect(), playerIterator->getDestRect());

        if(playerIterator->getLife() < 0)
            players.erase(playerIterator);
        // WIN CONDITION
    }


    //Loads cloud
    for(this->cloudIterator = this->clouds.begin(); this->cloudIterator < this->clouds.end(); this->cloudIterator++) {
        int targetX;
        int targetY;

        if(cloudIterator->charged()) {
            if((SDL_GetTicks()/50) % 2 == 0) {
                //Player Target
                targetX = cloudIterator->getTarget()->getXPosition();
                targetY = cloudIterator->getTarget()->getYPosition() - CELL_SIZE;
                cloudIterator->getLightning()->setXPosition(targetX);
                cloudIterator->getLightning()->setYPosition(targetY);
                SDL_RenderCopy(this->renderer, cloudIterator->getLightning()->getLightningTexture(), NULL, cloudIterator->getLightning()->getDestRect());

                for(this->monsterIterator = this->monsters.begin(); this->monsterIterator < this->monsters.end(); this->monsterIterator++) {
                    //Monster Target
                    targetX = monsterIterator->getXPosition();
                    targetY = monsterIterator->getYPosition() - CELL_SIZE;
                    cloudIterator->getLightning()->setXPosition(targetX);
                    cloudIterator->getLightning()->setYPosition(targetY);
                    SDL_RenderCopy(this->renderer, cloudIterator->getLightning()->getLightningTexture(), NULL, cloudIterator->getLightning()->getDestRect());
                }

                for(this->turtleIterator = this->turtles.begin(); this->turtleIterator < this->turtles.end(); this->turtleIterator++) {
                    //Turtle Target
                    targetX = turtleIterator->getXPosition();
                    targetY = turtleIterator->getYPosition() - CELL_SIZE;
                    cloudIterator->getLightning()->setXPosition(targetX);
                    cloudIterator->getLightning()->setYPosition(targetY);
                    SDL_RenderCopy(this->renderer, cloudIterator->getLightning()->getLightningTexture(), NULL, cloudIterator->getLightning()->getDestRect());
                }

            }
            //Lightning Damage
            if(cloudIterator->getHitState()) {
                cloudIterator->getTarget()->damaged(10);
                for(this->monsterIterator = this->monsters.begin(); this->monsterIterator < this->monsters.end(); this->monsterIterator++)
                    monsterIterator->damaged(10);

                for(this->turtleIterator = this->turtles.begin(); this->turtleIterator < this->turtles.end(); this->turtleIterator++)
                    turtleIterator->damaged(10);
            }
        }

        //Cloud Rendering
        targetX = cloudIterator->getTarget()->getXPosition() - (CELL_SIZE / 2);
        targetY = cloudIterator->getTarget()->getYPosition() - CELL_SIZE;
        cloudIterator->setXPosition(targetX);
        cloudIterator->setYPosition(targetY);
        SDL_RenderCopy(this->renderer, cloudIterator->getCloudTexture(), NULL, cloudIterator->getDestRect());

        //Monster's
        for(this->monsterIterator = this->monsters.begin(); this->monsterIterator < this->monsters.end(); this->monsterIterator++) {
            targetX = monsterIterator->getXPosition() - (CELL_SIZE / 2);
            targetY = monsterIterator->getYPosition() - CELL_SIZE;
            cloudIterator->setXPosition(targetX);
            cloudIterator->setYPosition(targetY);
            SDL_RenderCopy(this->renderer, cloudIterator->getCloudTexture(), NULL, cloudIterator->getDestRect());
        }

        //Turtle's
        for(this->turtleIterator = this->turtles.begin(); this->turtleIterator < this->turtles.end(); this->turtleIterator++) {
            targetX = turtleIterator->getXPosition() - (CELL_SIZE / 2);
            targetY = turtleIterator->getYPosition() - CELL_SIZE;
            cloudIterator->setXPosition(targetX);
            cloudIterator->setYPosition(targetY);
            SDL_RenderCopy(this->renderer, cloudIterator->getCloudTexture(), NULL, cloudIterator->getDestRect());
        }

    }
}

void Game::render() {
    SDL_RenderPresent(this->renderer);
}

void Game::clean() {
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
}

void Game::loadItem(Item item) {
    SDL_Surface* surface = IMG_Load(item.getImageSource());
    item.setTexture(this->renderer, surface);
    SDL_FreeSurface(surface);
    this->items.emplace_back(item);
}

void Game::loadBlock(Entity entity) {
    SDL_Surface* surface = IMG_Load(entity.getImageSource());
    entity.setTexture(this->renderer, surface);
    SDL_FreeSurface(surface);
    this->blocks.emplace_back(entity);
}

void Game::loadFlag(Flag flag) {
    SDL_Surface* surface = IMG_Load(flag.getImageSource());
    flag.setTexture(this->renderer, surface);
    SDL_FreeSurface(surface);

    if(flag.getEntityType() == FLAG_ONE)
        this->flagsOne.emplace_back(flag);
    else if(flag.getEntityType() == FLAG_TWO)
        this->flagsTwo.emplace_back(flag);
}

void Game::loadFlagCrate(PlayerNumber source) {
    if(source == ONE) {
        for(this->flagIterator = this->flagsOne.begin(); this->flagIterator < this->flagsOne.end(); this->flagIterator++) {
            flagIterator->setLife(flagIterator->getLife() + 2);
            this->loadBlock(MetalCrate(flagIterator->getXPosition(), flagIterator->getYPosition()));
        }
    }
    else if(source == TWO) {
        for(this->flagIterator = this->flagsTwo.begin(); this->flagIterator < this->flagsTwo.end(); this->flagIterator++) {
            flagIterator->setLife(flagIterator->getLife() + 2);
            this->loadBlock(MetalCrate(flagIterator->getXPosition(), flagIterator->getYPosition()));
        }
    }
}

void Game::loadPlayer(Player player) {
    SDL_Surface* surface = IMG_Load(player.getImageSource());
    player.setTexture(this->renderer, surface);
    SDL_FreeSurface(surface);

    SDL_QueryTexture(player.getTexture(), NULL, NULL, player.getImageWidth(), player.getImageHeight());
    player.setFrameSize(13, 21);
    this->players.emplace_back(player);
}

void Game::loadMonster(Monster monster) {
    SDL_Surface* surface = IMG_Load(monster.getImageSource());
    monster.setTexture(this->renderer, surface);
    SDL_FreeSurface(surface);

    SDL_QueryTexture(monster.getTexture(), NULL, NULL, monster.getImageWidth(), monster.getImageHeight());
    monster.setFrameSize(13, 21);
    this->monsters.emplace_back(monster);
}

void Game::loadTurtle(Turtle turtle) {
    SDL_Surface* surface = IMG_Load(turtle.getImageSource());
    turtle.setTexture(this->renderer, surface);
    SDL_FreeSurface(surface);

    SDL_QueryTexture(turtle.getTexture(), NULL, NULL, &turtle.getSpriteRect()->w, &turtle.getSpriteRect()->h);
    turtle.setFrameSize(4, 4);
    this->turtles.emplace_back(turtle);
}

void Game::loadStage(const Stage gameStage) {

    int p1CharNum = 1;
    int p2CharNum = 2;
    const char* p1CharSrc;
    const char* p2CharSrc;

    switch(p1CharNum) {
        case 1:
            {
            p1CharSrc = "images/character/char1.png";
            }
            break;
        case 2:
            {
            p1CharSrc = "images/character/char2.png";
            }
            break;
        case 3:
            {
            p1CharSrc = "images/character/char3.png";
            }
            break;
        case 4:
            {
            p1CharSrc = "images/character/char4.png";
            }
            break;
        case 5:
            {
            p1CharSrc = "images/character/char5.png";
            }
            break;
        case 6:
            {
            p1CharSrc = "images/character/char6.png";
            }
            break;
    }
    switch(p2CharNum) {
        case 1:
            {
            p2CharSrc = "images/character/char1.png";
            }
            break;
        case 2:
            {
            p2CharSrc = "images/character/char2.png";
            }
            break;
        case 3:
            {
            p2CharSrc = "images/character/char3.png";
            }
            break;
        case 4:
            {
            p2CharSrc = "images/character/char4.png";
            }
            break;
        case 5:
            {
            p2CharSrc = "images/character/char5.png";
            }
            break;
        case 6:
            {
            p2CharSrc = "images/character/char6.png";
            }
            break;
    }

    HealthBar::initializeHealthBar(this->renderer);
    SDL_Surface* surface;
    switch(gameStage) {
        case CANDYLAND:
            {
            //Player graphics
            this->loadPlayer(Player(p1CharSrc, 20, 10, ONE));
            this->loadPlayer(Player(p2CharSrc, 1, 1, TWO));

            //Stage graphics
            surface = IMG_Load("images/candyland/stage/Candyland.png");

            //Blocks graphics
            Wall::setWallIMG("images/candyland/blocks/wall.png");
            HardBrick::setHardBrickIMG("images/candyland/blocks/hardBrick.png");
            crackedIMG = "images/candyland/blocks/crackedHardBrick.png";
            Brick::setBrickIMG("images/candyland/blocks/brick.png");
            Crate::setCrateIMG("images/candyland/blocks/crate.png");
            CommonCrate::setCommonCrateIMG("images/jungle/blocks/commonCrate.png");
            Barrel::setBarrelIMG("images/candyland/blocks/barrel.png");
            PortalSource::setPortalSourceIMG("images/candyland/blocks/portalSource.png");
            PortalDestination::setPortalDestinationIMG("images/candyland/blocks/portalDestination.png");

            //Player 1 Flags
            Flag::setFlagIMG("images/candyland/blocks/orangeFlag.png");
            loadFlag(Flag(1, 10, FLAG_ONE));
            loadFlag(Flag(4, 10, FLAG_ONE));
            loadFlag(Flag(4, 8, FLAG_ONE));

            //Player 2 Flags
            Flag::setFlagIMG("images/candyland/blocks/blueFlag.png");
            loadFlag(Flag(17, 1, FLAG_TWO));
            loadFlag(Flag(20, 1, FLAG_TWO));
            loadFlag(Flag(15, 1, FLAG_TWO));

            //Items graphics
            Bazooka::setBazookaIMG("images/candyland/items/bazooka.png");
            Zanic::setZanicIMG("images/candyland/items/zanic.png");
            Freeze::setFreezeIMG("images/candyland/items/freeze.png");
            Laser::setLaserIMG("images/candyland/items/laser.png");
            Smite::setSmiteIMG("images/candyland/items/smite.png");
            Snail::setSnailIMG("images/candyland/items/snail.png");
            Portal::setPortalIMG("images/candyland/items/portal.png");
            Jumble::setJumbleIMG("images/candyland/items/jumble.png");
            Herb::setHerbIMG("images/candyland/items/herb.png");
            F::setFIMG("images/candyland/items/F.png");
            LaserBeam::loadLaserBeamIMG(this->renderer);
            Cloud::loadCloudIMG(this->renderer);
            Lightning::loadLightningIMG(this->renderer);

            //Monsters graphics
            Monster::setMonsterIMG("images/candyland/entities/monster.png");
            Turtle::setTurtleIMG("images/candyland/entities/turtle.png");

            //Monsters Initialization
            this->loadTurtle(Turtle(10, 8, LEFT));
            this->loadMonster(Monster(8, 7, RIGHT));
            this->loadMonster(Monster(6, 10, RIGHT));
            this->loadMonster(Monster(15, 10, RIGHT));


            //Blocks Initialization
            this->loadBlock(Wall(2,2));
            this->loadBlock(Wall(2,3));
            this->loadBlock(Wall(2,5));
            this->loadBlock(Wall(2,6));
            this->loadBlock(Wall(2,8));
            this->loadBlock(Wall(2,9));
            this->loadBlock(Wall(3,10));
            this->loadBlock(Wall(4,1));
            this->loadBlock(Wall(4,2));
            this->loadBlock(Wall(4,4));
            this->loadBlock(Wall(4,5));
            this->loadBlock(Wall(4,7));
            this->loadBlock(Wall(5,10));
            this->loadBlock(Wall(6,2));
            this->loadBlock(Wall(6,3));
            this->loadBlock(Wall(6,8));
            this->loadBlock(Wall(7,7));
            this->loadBlock(Wall(8,1));
            this->loadBlock(Wall(8,2));
            this->loadBlock(Wall(8,4));
            this->loadBlock(Wall(8,6));
            this->loadBlock(Wall(8,8));
            this->loadBlock(Wall(9,6));
            this->loadBlock(Wall(10,2));
            this->loadBlock(Wall(10,4));
            this->loadBlock(Wall(10,10));
            this->loadBlock(Wall(11,1));
            this->loadBlock(Wall(11,3));
            this->loadBlock(Wall(11,10));
            this->loadBlock(Wall(12,6));
            this->loadBlock(Wall(13,1));
            this->loadBlock(Wall(13,2));
            this->loadBlock(Wall(13,4));
            this->loadBlock(Wall(13,6));
            this->loadBlock(Wall(13,8));
            this->loadBlock(Wall(14,7));
            this->loadBlock(Wall(15,2));
            this->loadBlock(Wall(15,3));
            this->loadBlock(Wall(15,5));
            this->loadBlock(Wall(15,8));
            this->loadBlock(Wall(16,10));
            this->loadBlock(Wall(17,2));
            this->loadBlock(Wall(17,4));
            this->loadBlock(Wall(17,5));
            this->loadBlock(Wall(17,7));
            this->loadBlock(Wall(17,8));
            this->loadBlock(Wall(19,2));
            this->loadBlock(Wall(19,3));
            this->loadBlock(Wall(19,5));
            this->loadBlock(Wall(19,6));
            this->loadBlock(Wall(19,8));
            this->loadBlock(Wall(19,9));


            this->loadBlock(HardBrick(3,1));
            this->loadBlock(HardBrick(4,9));
            this->loadBlock(HardBrick(5,3));
            this->loadBlock(HardBrick(5,6));
            this->loadBlock(HardBrick(5,8));
            this->loadBlock(HardBrick(7,3));
            this->loadBlock(HardBrick(7,5));
            this->loadBlock(HardBrick(7,9));
            this->loadBlock(HardBrick(9,1));
            this->loadBlock(HardBrick(9,3));
            this->loadBlock(HardBrick(9,9));
            this->loadBlock(HardBrick(10,5));
            this->loadBlock(HardBrick(10,6));
            this->loadBlock(HardBrick(11,5));
            this->loadBlock(HardBrick(11,6));
            this->loadBlock(HardBrick(12,2));
            this->loadBlock(HardBrick(12,4));
            this->loadBlock(HardBrick(12,9));
            this->loadBlock(HardBrick(14,3));
            this->loadBlock(HardBrick(14,5));
            this->loadBlock(HardBrick(14,9));
            this->loadBlock(HardBrick(16,3));
            this->loadBlock(HardBrick(16,6));
            this->loadBlock(HardBrick(16,8));
            this->loadBlock(HardBrick(17,9));
            this->loadBlock(HardBrick(18,1));

            this->loadBlock(Brick(1,7));
            this->loadBlock(Brick(3,4));
            this->loadBlock(Brick(3,7));
            this->loadBlock(Brick(6,1));
            this->loadBlock(Brick(10,9));
            this->loadBlock(Brick(11,9));
            this->loadBlock(Brick(18,4));
            this->loadBlock(Brick(18,7));
            this->loadBlock(Brick(20,3));
            this->loadBlock(Brick(20,7));

            this->loadBlock(Crate(1,9));
            this->loadBlock(Crate(2,4));
            this->loadBlock(Crate(2,10));
            this->loadBlock(Crate(3,3));
            this->loadBlock(Crate(3,6));
            this->loadBlock(Crate(5,2));
            this->loadBlock(Crate(6,4));
            this->loadBlock(Crate(6,6));
            this->loadBlock(Crate(6,7));
            this->loadBlock(Crate(6,9));
            this->loadBlock(Crate(8,3));
            this->loadBlock(Crate(8,5));
            this->loadBlock(Crate(9,2));
            this->loadBlock(Crate(11,2));
            this->loadBlock(Crate(11,4));
            this->loadBlock(Crate(13,3));
            this->loadBlock(Crate(13,5));
            this->loadBlock(Crate(13,9));
            this->loadBlock(Crate(14,1));
            this->loadBlock(Crate(14,6));
            this->loadBlock(Crate(15,7));
            this->loadBlock(Crate(15,9));
            this->loadBlock(Crate(16,2));
            this->loadBlock(Crate(17,10));
            this->loadBlock(Crate(18,3));
            this->loadBlock(Crate(18,5));
            this->loadBlock(Crate(19,1));
            this->loadBlock(Crate(19,7));
            this->loadBlock(Crate(20,5));

            this->loadBlock(CommonCrate(1,5));
            this->loadBlock(CommonCrate(2,7));
            this->loadBlock(CommonCrate(3,5));
            this->loadBlock(CommonCrate(3,8));
            this->loadBlock(CommonCrate(4,3));
            this->loadBlock(CommonCrate(4,6));
            this->loadBlock(CommonCrate(5,1));
            this->loadBlock(CommonCrate(5,4));
            this->loadBlock(CommonCrate(5,7));
            this->loadBlock(CommonCrate(7,2));
            this->loadBlock(CommonCrate(7,4));
            this->loadBlock(CommonCrate(7,6));
            this->loadBlock(CommonCrate(7,8));
            this->loadBlock(CommonCrate(10,1));
            this->loadBlock(CommonCrate(10,3));
            this->loadBlock(CommonCrate(12,1));
            this->loadBlock(CommonCrate(14,4));
            this->loadBlock(CommonCrate(14,8));
            this->loadBlock(CommonCrate(15,6));
            this->loadBlock(CommonCrate(16,1));
            this->loadBlock(CommonCrate(16,4));
            this->loadBlock(CommonCrate(16,7));
            this->loadBlock(CommonCrate(16,9));
            this->loadBlock(CommonCrate(17,3));
            this->loadBlock(CommonCrate(18,6));
            this->loadBlock(CommonCrate(18,8));
            this->loadBlock(CommonCrate(19,4));
            this->loadBlock(CommonCrate(20,2));
            this->loadBlock(CommonCrate(20,6));

            this->loadBlock(Barrel(1,6));
            this->loadBlock(Barrel(1,8));
            this->loadBlock(Barrel(3,2));
            this->loadBlock(Barrel(3,9));
            this->loadBlock(Barrel(5,5));
            this->loadBlock(Barrel(5,9));
            this->loadBlock(Barrel(7,1));
            this->loadBlock(Barrel(8,9));
            this->loadBlock(Barrel(9,4));
            this->loadBlock(Barrel(9,5));
            this->loadBlock(Barrel(12,3));
            this->loadBlock(Barrel(12,5));
            this->loadBlock(Barrel(14,2));
            this->loadBlock(Barrel(15,4));
            this->loadBlock(Barrel(16,5));
            this->loadBlock(Barrel(17,6));
            this->loadBlock(Barrel(18,2));
            this->loadBlock(Barrel(18,9));
            this->loadBlock(Barrel(20,3));
            break;

        case JUNGLE:

            //Player graphics
            this->loadPlayer(Player(p1CharSrc, 20, 10, ONE));
            this->loadPlayer(Player(p2CharSrc, 1, 1, TWO));

            //Stage graphics
            surface = IMG_Load("images/jungle/stage/jungle.png");

            //Blocks graphics
            Wall::setWallIMG("images/jungle/blocks/wall.png");
            HardBrick::setHardBrickIMG("images/jungle/blocks/hardBrick.png");
            crackedIMG = "images/jungle/blocks/crackedHardBrick.png";
            Brick::setBrickIMG("images/jungle/blocks/brick.png");
            Crate::setCrateIMG("images/jungle/blocks/crate.png");
            CommonCrate::setCommonCrateIMG("images/jungle/blocks/commonCrate.png");
            Barrel::setBarrelIMG("images/jungle/blocks/barrel.png");
            PortalSource::setPortalSourceIMG("images/jungle/blocks/portalSource.png");
            PortalDestination::setPortalDestinationIMG("images/jungle/blocks/portalDestination.png");

            //Player 1 Flags
            Flag::setFlagIMG("images/jungle/blocks/orangeFlag.png");
            loadFlag(Flag(15, 1, FLAG_ONE));
            loadFlag(Flag(18, 2, FLAG_ONE));
            loadFlag(Flag(20, 2, FLAG_ONE));

            //Player 2 Flags
            Flag::setFlagIMG("images/jungle/blocks/blueFlag.png");
            loadFlag(Flag(2, 10, FLAG_TWO));
            loadFlag(Flag(1, 9, FLAG_TWO));
            loadFlag(Flag(2, 8, FLAG_TWO));

            //Items graphics
            Bazooka::setBazookaIMG("images/jungle/items/bazooka.png");
            Zanic::setZanicIMG("images/jungle/items/zanic.png");
            Freeze::setFreezeIMG("images/jungle/items/freeze.png");
            Laser::setLaserIMG("images/jungle/items/laser.png");
            Smite::setSmiteIMG("images/jungle/items/smite.png");
            Snail::setSnailIMG("images/jungle/items/snail.png");
            Portal::setPortalIMG("images/jungle/items/portal.png");
            Jumble::setJumbleIMG("images/jungle/items/jumble.png");
            Herb::setHerbIMG("images/jungle/items/herb.png");
            F::setFIMG("images/jungle/items/F.png");
            LaserBeam::loadLaserBeamIMG(this->renderer);
            Cloud::loadCloudIMG(this->renderer);
            Lightning::loadLightningIMG(this->renderer);

            //Monsters graphics
            Monster::setMonsterIMG("images/jungle/entities/monster.png");
            Turtle::setTurtleIMG("images/jungle/entities/turtle.png");

            //Monsters Initialization
            this->loadTurtle(Turtle(10, 8, LEFT));
            this->loadMonster(Monster(7, 7, UP));
            this->loadMonster(Monster(5, 10, UP));
            this->loadMonster(Monster(14, 7, UP));

            this->loadBlock(Wall(4,1));
            this->loadBlock(Wall(7,1));
            this->loadBlock(Wall(14,1));
            this->loadBlock(Wall(2,2));
            this->loadBlock(Wall(6,2));
            this->loadBlock(Wall(10,2));
            this->loadBlock(Wall(11,2));
            this->loadBlock(Wall(15,2));
            this->loadBlock(Wall(19,2));
            this->loadBlock(Wall(4,3));
            this->loadBlock(Wall(8,3));
            this->loadBlock(Wall(13,3));
            this->loadBlock(Wall(10,4));
            this->loadBlock(Wall(11,4));
            this->loadBlock(Wall(19,4));
            this->loadBlock(Wall(2,5));
            this->loadBlock(Wall(13,5));
            this->loadBlock(Wall(8,6));
            this->loadBlock(Wall(19,6));
            this->loadBlock(Wall(2,7));
            this->loadBlock(Wall(10,7));
            this->loadBlock(Wall(11,7));
            this->loadBlock(Wall(8,8));
            this->loadBlock(Wall(13,8));
            this->loadBlock(Wall(17,8));
            this->loadBlock(Wall(2,9));
            this->loadBlock(Wall(6,9));
            this->loadBlock(Wall(10,9));
            this->loadBlock(Wall(11,9));
            this->loadBlock(Wall(15,9));
            this->loadBlock(Wall(19,9));
            this->loadBlock(Wall(7,10));
            this->loadBlock(Wall(14,10));
            this->loadBlock(Wall(17,10));

            this->loadBlock(HardBrick(7,3));
            this->loadBlock(HardBrick(14,3));
            this->loadBlock(HardBrick(16,3));
            this->loadBlock(HardBrick(4,4));
            this->loadBlock(HardBrick(5,4));
            this->loadBlock(HardBrick(3,5));
            this->loadBlock(HardBrick(6,5));
            this->loadBlock(HardBrick(8,5));
            this->loadBlock(HardBrick(15,5));
            this->loadBlock(HardBrick(19,5));
            this->loadBlock(HardBrick(2,6));
            this->loadBlock(HardBrick(6,6));
            this->loadBlock(HardBrick(13,6));
            this->loadBlock(HardBrick(15,6));
            this->loadBlock(HardBrick(16,6));
            this->loadBlock(HardBrick(18,6));
            this->loadBlock(HardBrick(5,7));
            this->loadBlock(HardBrick(17,7));
            this->loadBlock(HardBrick(7,8));
            this->loadBlock(HardBrick(14,8));

            this->loadBlock(Brick(9,1));
            this->loadBlock(Brick(12,1));
            this->loadBlock(Brick(17,1));
            this->loadBlock(Brick(3,2));
            this->loadBlock(Brick(17,3));
            this->loadBlock(Brick(9,4));
            this->loadBlock(Brick(12,4));
            this->loadBlock(Brick(17,4));
            this->loadBlock(Brick(1,5));
            this->loadBlock(Brick(10,6));
            this->loadBlock(Brick(4,7));
            this->loadBlock(Brick(9,7));
            this->loadBlock(Brick(12,7));
            this->loadBlock(Brick(4,8));
            this->loadBlock(Brick(18,9));
            this->loadBlock(Brick(4,10));
            this->loadBlock(Brick(9,10));
            this->loadBlock(Brick(12,10));
            this->loadBlock(Brick(1,8));
            this->loadBlock(Brick(2,3));
            this->loadBlock(Brick(2,4));
            this->loadBlock(Brick(3,6));
            this->loadBlock(Brick(3,10));
            this->loadBlock(Brick(4,6));
            this->loadBlock(Brick(5,2));
            this->loadBlock(Brick(6,1));
            this->loadBlock(Brick(7,9));
            this->loadBlock(Brick(8,2));
            this->loadBlock(Brick(8,9));
            this->loadBlock(Brick(13,2));
            this->loadBlock(Brick(15,8));
            this->loadBlock(Brick(16,2));
            this->loadBlock(Brick(16,4));
            this->loadBlock(Brick(16,9));
            this->loadBlock(Brick(17,5));
            this->loadBlock(Brick(18,1));
            this->loadBlock(Brick(18,3));
            this->loadBlock(Brick(18,7));
            this->loadBlock(Brick(18,10));
            this->loadBlock(Brick(19,3));
            this->loadBlock(Brick(19,7));

            this->loadBlock(Crate(3,1));
            this->loadBlock(Crate(10,1));
            this->loadBlock(Crate(16,1));
            this->loadBlock(Crate(4,2));
            this->loadBlock(Crate(6,3));
            this->loadBlock(Crate(9,3));
            this->loadBlock(Crate(11,3));
            this->loadBlock(Crate(3,4));
            this->loadBlock(Crate(13,4));
            this->loadBlock(Crate(15,4));
            this->loadBlock(Crate(20,4));
            this->loadBlock(Crate(10,5));
            this->loadBlock(Crate(18,5));
            this->loadBlock(Crate(1,6));
            this->loadBlock(Crate(5,6));
            this->loadBlock(Crate(9,6));
            this->loadBlock(Crate(6,7));
            this->loadBlock(Crate(8,7));
            this->loadBlock(Crate(16,7));
            this->loadBlock(Crate(18,8));
            this->loadBlock(Crate(20,8));
            this->loadBlock(Crate(3,9));
            this->loadBlock(Crate(13,9));
            this->loadBlock(Crate(1,10));
            this->loadBlock(Crate(11,10));
            this->loadBlock(Crate(13,10));
            this->loadBlock(Crate(15,10));

            this->loadBlock(CommonCrate(1,7));
            this->loadBlock(CommonCrate(3,3));
            this->loadBlock(CommonCrate(3,8));
            this->loadBlock(CommonCrate(5,1));
            this->loadBlock(CommonCrate(5,3));
            this->loadBlock(CommonCrate(5,5));
            this->loadBlock(CommonCrate(6,8));
            this->loadBlock(CommonCrate(8,1));
            this->loadBlock(CommonCrate(9,2));
            this->loadBlock(CommonCrate(9,5));
            this->loadBlock(CommonCrate(9,9));
            this->loadBlock(CommonCrate(10,3));
            this->loadBlock(CommonCrate(10,10));
            this->loadBlock(CommonCrate(11,1));
            this->loadBlock(CommonCrate(12,9));
            this->loadBlock(CommonCrate(13,1));
            this->loadBlock(CommonCrate(14,9));
            this->loadBlock(CommonCrate(15,3));
            this->loadBlock(CommonCrate(16,5));
            this->loadBlock(CommonCrate(16,8));
            this->loadBlock(CommonCrate(16,10));
            this->loadBlock(CommonCrate(17,2));
            this->loadBlock(CommonCrate(18,4));
            this->loadBlock(CommonCrate(20,1));
            this->loadBlock(CommonCrate(20,3));
            this->loadBlock(CommonCrate(20,5));
            this->loadBlock(CommonCrate(20,7));

            this->loadBlock(Barrel(19,1));
            this->loadBlock(Barrel(1,3));
            this->loadBlock(Barrel(7,2));
            this->loadBlock(Barrel(12,2));
            this->loadBlock(Barrel(14,2));
            this->loadBlock(Barrel(1,4));
            this->loadBlock(Barrel(6,4));
            this->loadBlock(Barrel(8,4));
            this->loadBlock(Barrel(4,5));
            this->loadBlock(Barrel(11,5));
            this->loadBlock(Barrel(12,5));
            this->loadBlock(Barrel(17,6));
            this->loadBlock(Barrel(3,7));
            this->loadBlock(Barrel(13,7));
            this->loadBlock(Barrel(15,7));
            this->loadBlock(Barrel(19,8));
            this->loadBlock(Barrel(4,9));
            this->loadBlock(Barrel(17,9));
            this->loadBlock(Barrel(6,10));
            this->loadBlock(Barrel(8,10));
            }
            break;

        case GRAVEYARD:

            //Player graphics
            this->loadPlayer(Player(p1CharSrc, 20, 10, ONE));
            this->loadPlayer(Player(p2CharSrc, 1, 1, TWO));

            //Stage graphics
            surface = IMG_Load("images/graveyard/stage/graveyard.png");

            //Blocks graphics
            Wall::setWallIMG("images/graveyard/blocks/wall.png");
            HardBrick::setHardBrickIMG("images/graveyard/blocks/hardBrick.png");
            crackedIMG = "images/graveyard/blocks/crackedHardBrick.png";
            Brick::setBrickIMG("images/graveyard/blocks/brick.png");
            Crate::setCrateIMG("images/graveyard/blocks/crate.png");
            CommonCrate::setCommonCrateIMG("images/jungle/blocks/commonCrate.png");
            Barrel::setBarrelIMG("images/graveyard/blocks/barrel.png");
            PortalSource::setPortalSourceIMG("images/graveyard/blocks/portalSource.png");
            PortalDestination::setPortalDestinationIMG("images/graveyard/blocks/portalDestination.png");

            //Player 1 Flags
            Flag::setFlagIMG("images/graveyard/blocks/orangeFlag.png");
            loadFlag(Flag(16, 1, FLAG_ONE));
            loadFlag(Flag(17, 2, FLAG_ONE));
            loadFlag(Flag(19, 2, FLAG_ONE));

            //Player 2 Flags
            Flag::setFlagIMG("images/graveyard/blocks/blueFlag.png");
            loadFlag(Flag(1, 9, FLAG_TWO));
            loadFlag(Flag(3, 10, FLAG_TWO));
            loadFlag(Flag(2, 8, FLAG_TWO));

            //Items graphics
            Bazooka::setBazookaIMG("images/graveyard/items/bazooka.png");
            Zanic::setZanicIMG("images/graveyard/items/zanic.png");
            Freeze::setFreezeIMG("images/graveyard/items/freeze.png");
            Laser::setLaserIMG("images/graveyard/items/laser.png");
            Smite::setSmiteIMG("images/graveyard/items/smite.png");
            Snail::setSnailIMG("images/graveyard/items/snail.png");
            Portal::setPortalIMG("images/graveyard/items/portal.png");
            Jumble::setJumbleIMG("images/graveyard/items/jumble.png");
            Herb::setHerbIMG("images/graveyard/items/herb.png");
            F::setFIMG("images/graveyard/items/F.png");
            LaserBeam::loadLaserBeamIMG(this->renderer);
            Cloud::loadCloudIMG(this->renderer);
            Lightning::loadLightningIMG(this->renderer);

            //Monsters graphics
            Monster::setMonsterIMG("images/graveyard/entities/monster.png");
            Turtle::setTurtleIMG("images/graveyard/entities/turtle.png");

            //Monsters Initialization
            this->loadTurtle(Turtle(10, 9, RIGHT));
            this->loadMonster(Monster(10, 7, DOWN));
            this->loadMonster(Monster(12, 6, DOWN));
            this->loadMonster(Monster(7, 8, DOWN));

            this->loadBlock(Wall(6,1));
            this->loadBlock(Wall(10,1));
            this->loadBlock(Wall(13,1));
            this->loadBlock(Wall(8,2));
            this->loadBlock(Wall(12,2));
            this->loadBlock(Wall(15,2));
            this->loadBlock(Wall(3,3));
            this->loadBlock(Wall(5,3));
            this->loadBlock(Wall(4,4));
            this->loadBlock(Wall(8,4));
            this->loadBlock(Wall(11,4));
            this->loadBlock(Wall(1,5));
            this->loadBlock(Wall(2,5));
            this->loadBlock(Wall(6,5));
            this->loadBlock(Wall(10,5));
            this->loadBlock(Wall(11,5));
            this->loadBlock(Wall(12,5));
            this->loadBlock(Wall(8,6));
            this->loadBlock(Wall(11,6));
            this->loadBlock(Wall(18,6));
            this->loadBlock(Wall(2,7));
            this->loadBlock(Wall(4,7));
            this->loadBlock(Wall(6,7));
            this->loadBlock(Wall(11,7));
            this->loadBlock(Wall(14,7));
            this->loadBlock(Wall(17,7));
            this->loadBlock(Wall(19,7));
            this->loadBlock(Wall(11,8));
            this->loadBlock(Wall(9,9));
            this->loadBlock(Wall(14,9));
            this->loadBlock(Wall(16,9));
            this->loadBlock(Wall(8,10));
            this->loadBlock(Wall(12,10));

            this->loadBlock(HardBrick(2,10));
            this->loadBlock(HardBrick(18,1));
            this->loadBlock(HardBrick(4,2));
            this->loadBlock(HardBrick(7,3));
            this->loadBlock(HardBrick(8,3));
            this->loadBlock(HardBrick(9,3));
            this->loadBlock(HardBrick(8,5));
            this->loadBlock(HardBrick(16,5));
            this->loadBlock(HardBrick(5,6));
            this->loadBlock(HardBrick(14,6));
            this->loadBlock(HardBrick(13,7));
            this->loadBlock(HardBrick(15,7));
            this->loadBlock(HardBrick(14,8));
            this->loadBlock(HardBrick(18,8));
            this->loadBlock(HardBrick(5,10));
            this->loadBlock(HardBrick(14,10));

            this->loadBlock(Brick(13,3));
            this->loadBlock(Brick(15,3));
            this->loadBlock(Brick(17,3));
            this->loadBlock(Brick(19,3));
            this->loadBlock(Brick(15,4));
            this->loadBlock(Brick(17,4));
            this->loadBlock(Brick(19,4));
            this->loadBlock(Brick(20,5));
            this->loadBlock(Brick(3,6));
            this->loadBlock(Brick(9,7));
            this->loadBlock(Brick(4,8));
            this->loadBlock(Brick(6,8));
            this->loadBlock(Brick(8,8));
            this->loadBlock(Brick(2,9));
            this->loadBlock(Brick(4,9));
            this->loadBlock(Brick(6,9));
            this->loadBlock(Brick(16,10));
            this->loadBlock(Brick(1,3));
            this->loadBlock(Brick(3,1));
            this->loadBlock(Brick(3,4));
            this->loadBlock(Brick(3,7));
            this->loadBlock(Brick(4,5));
            this->loadBlock(Brick(4,10));
            this->loadBlock(Brick(5,5));
            this->loadBlock(Brick(5,7));
            this->loadBlock(Brick(6,2));
            this->loadBlock(Brick(6,3));
            this->loadBlock(Brick(7,2));
            this->loadBlock(Brick(7,5));
            this->loadBlock(Brick(9,1));
            this->loadBlock(Brick(9,6));
            this->loadBlock(Brick(10,2));
            this->loadBlock(Brick(11,1));
            this->loadBlock(Brick(11,9));
            this->loadBlock(Brick(12,3));
            this->loadBlock(Brick(13,5));
            this->loadBlock(Brick(14,2));
            this->loadBlock(Brick(14,4));
            this->loadBlock(Brick(16,6));
            this->loadBlock(Brick(16,8));
            this->loadBlock(Brick(17,5));
            this->loadBlock(Brick(17,9));
            this->loadBlock(Brick(18,4));
            this->loadBlock(Brick(18,9));
            this->loadBlock(Brick(19,5));
            this->loadBlock(Brick(19,8));
            this->loadBlock(Brick(20,8));


            this->loadBlock(Crate(1,10));
            this->loadBlock(Crate(5,1));
            this->loadBlock(Crate(8,1));
            this->loadBlock(Crate(12,1));
            this->loadBlock(Crate(15,1));
            this->loadBlock(Crate(17,1));
            this->loadBlock(Crate(20,2));
            this->loadBlock(Crate(4,3));
            this->loadBlock(Crate(16,3));
            this->loadBlock(Crate(1,4));
            this->loadBlock(Crate(5,4));
            this->loadBlock(Crate(7,4));
            this->loadBlock(Crate(9,4));
            this->loadBlock(Crate(12,4));
            this->loadBlock(Crate(6,6));
            this->loadBlock(Crate(10,6));
            this->loadBlock(Crate(13,6));
            this->loadBlock(Crate(20,6));
            this->loadBlock(Crate(1,7));
            this->loadBlock(Crate(18,7));
            this->loadBlock(Crate(1,8));
            this->loadBlock(Crate(3,8));
            this->loadBlock(Crate(5,8));
            this->loadBlock(Crate(17,8));
            this->loadBlock(Crate(9,5));
            this->loadBlock(Crate(8,9));
            this->loadBlock(Crate(9,10));
            this->loadBlock(Crate(13,10));
            this->loadBlock(Crate(18,10));


            this->loadBlock(CommonCrate(1,6));
            this->loadBlock(CommonCrate(2,4));
            this->loadBlock(CommonCrate(3,5));
            this->loadBlock(CommonCrate(3,9));
            this->loadBlock(CommonCrate(4,1));
            this->loadBlock(CommonCrate(5,2));
            this->loadBlock(CommonCrate(6,4));
            this->loadBlock(CommonCrate(7,1));
            this->loadBlock(CommonCrate(7,6));
            this->loadBlock(CommonCrate(9,5));
            this->loadBlock(CommonCrate(9,8));
            this->loadBlock(CommonCrate(10,4));
            this->loadBlock(CommonCrate(11,2));
            this->loadBlock(CommonCrate(11,3));
            this->loadBlock(CommonCrate(11,10));
            this->loadBlock(CommonCrate(13,4));
            this->loadBlock(CommonCrate(14,1));
            this->loadBlock(CommonCrate(14,3));
            this->loadBlock(CommonCrate(16,2));
            this->loadBlock(CommonCrate(16,4));
            this->loadBlock(CommonCrate(17,6));
            this->loadBlock(CommonCrate(17,10));
            this->loadBlock(CommonCrate(19,6));
            this->loadBlock(CommonCrate(20,1));
            this->loadBlock(CommonCrate(20,3));
            this->loadBlock(CommonCrate(20,7));
            this->loadBlock(CommonCrate(16,7));
            this->loadBlock(CommonCrate(15,9));
            this->loadBlock(CommonCrate(18,2));


            this->loadBlock(Barrel(19,1));
            this->loadBlock(Barrel(3,2));
            this->loadBlock(Barrel(9,2));
            this->loadBlock(Barrel(13,2));
            this->loadBlock(Barrel(18,3));
            this->loadBlock(Barrel(20,4));
            this->loadBlock(Barrel(14,5));
            this->loadBlock(Barrel(15,5));
            this->loadBlock(Barrel(18,5));
            this->loadBlock(Barrel(2,6));
            this->loadBlock(Barrel(4,6));
            this->loadBlock(Barrel(15,6));
            this->loadBlock(Barrel(7,7));
            this->loadBlock(Barrel(8,7));
            this->loadBlock(Barrel(6,10));
            this->loadBlock(Barrel(15,10));
            this->loadBlock(Barrel(10,3));
            this->loadBlock(Barrel(13,8));
            this->loadBlock(Barrel(15,8));
            this->loadBlock(Barrel(2,3));
            break;
    }

    this->texture = SDL_CreateTextureFromSurface(this->renderer, surface);
    SDL_FreeSurface(surface);
}


void Game::spawnBomb(Player* player) {
        if(player->getCurrentBomb() < player->getBombCount()) {
           player->setPastX(this->roundNum(player->getXPosition()));
            player->setPastY(this->roundNum(player->getYPosition()));
            int bombX = this->roundNum(player->getPastX());
            int bombY = this->roundNum(player->getPastY());

            Bomb bomb(bombX, bombY, player->getPlayerNumber(), this->renderer, player->getBombRange());

            if(this->bombDuplicate(bomb) == false) {
                player->setGhost(true);
                SDL_Surface* surface = IMG_Load(bomb.getImageSource());
                bomb.setTexture(this->renderer, surface);
                bomb.setBombRange(this->blocks);
                this->bombs.push_back(bomb);
                player->incrementCurrentBomb();
            }
        }
}

void Game::spawnBomb(Entity* entity) {
    int bombX = this->roundNum(entity->getXPosition());
    int bombY = this->roundNum(entity->getYPosition());

    Bomb bomb(bombX, bombY, this->renderer, 3);
    SDL_Surface* surface = IMG_Load(bomb.getImageSource());
    bomb.setTexture(this->renderer, surface);
    bomb.setBombRange(this->blocks);
    bomb.setSpawnTime(bomb.getSpawnTime());
    this->barrelBombs.push_back(bomb);
}

void Game::spawnItem(Entity* entity) {
    EntityType crateType = entity->getEntityType();
    int crateX = entity->getXPosition();
    int crateY = entity->getYPosition();
    if(crateType == CRATE) {
        int itemNum = (rand() % 10) + 1;
        switch(itemNum) {
            case 1:
                loadItem(Bazooka(crateX, crateY));
                break;
            case 2:
                loadItem(Zanic(crateX, crateY));
                break;
            case 3:
                loadItem(Freeze(crateX, crateY));
                break;
            case 4:
                loadItem(Laser(crateX, crateY));
                break;
            case 5:
                loadItem(Smite(crateX, crateY));
                break;
            case 6:
                loadItem(Snail(crateX, crateY));
                break;
            case 7:
                loadItem(Portal(crateX, crateY));
                break;
            case 8:
                loadItem(Jumble(crateX, crateY));
                break;
            case 9:
                loadItem(Herb(crateX, crateY));
                break;
            case 10:
                loadItem(F(crateX, crateY));
                break;
        }
    }
    else if(crateType == COMMON_CRATE) {
        int itemNum = rand() % 2;
        if(itemNum == 0)
            loadItem(BombAdd(crateX, crateY));
        else if(itemNum == 1)
            loadItem(RangeAdd(crateX, crateY));
    }


}

