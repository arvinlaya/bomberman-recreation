#ifndef GAME_H
#define GAME_H

#include "Entity.h"
#include "Item.h"
#include "Player.h"
#include "Monster.h"
#include "Turtle.h"
#include "HealthBar.h"

#include "Wall.h"
#include "Brick.h"
#include "HardBrick.h"
#include "Crate.h"
#include "Barrel.h"
#include "Flag.h"
#include "CommonCrate.h"
#include "MetalCrate.h"

#include "Bazooka.h"
#include "Rocket.h"
#include "Zanic.h"
#include "Freeze.h"
#include "Snail.h"
#include "Laser.h"
#include "LaserBeam.h"
#include "Jumble.h"
#include "Portal.h"
#include "PortalSource.h"
#include "PortalDestination.h"
#include "Smite.h"
#include "Cloud.h"
#include "Lightning.h"
#include "Herb.h"
#include "F.h"
#include "BombAdd.h"
#include "RangeAdd.h"

#include "Bomb.h"

#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <iterator>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define PLAYER_SPEED 5
#define MONSTER_SPEED 2

enum Stage {
    CANDYLAND, JUNGLE, GRAVEYARD
};

class Game
{

    public:
        Game();
        ~Game();

        void initialize(const char* title, int gameWidth, int gameHeight, bool fullscreen);
        void handleEvent();
        void update();
        void render();
        void clean();

        void loadItem(Item item);
        void loadBlock(Entity entity);
        void loadFlag(Flag flag);
        void loadFlagCrate(PlayerNumber source);
        void loadPlayer(Player player);
        void loadMonster(Monster monster);
        void loadTurtle(Turtle turtle);
        void loadStage(const Stage gameStage);
        void spawnBomb(Player* player);
        void spawnBomb(Entity* entity);
        void spawnItem(Entity* entity);
        void explodeBlock(Bomb* bomb);
        void explodeEntity(Bomb* bomb);
        void laserEntity(LaserBeam* laserBeam);

        //Item effects
        void activateItem(Item* item, Player* player);
        void deactivateItem(Item* item, Player* player);
        void spawnRocket(int colPosition, int rowPosition, EntityType target, Player* player);
        void activateZanic(Player* source);
        void deactivateZanic(Player* source);
        void activateFreeze(Player* source);
        void deactivateFreeze(Player* source);
        void activateSnail(Player* source);
        void deactivateSnail(Player* source);
        void activateLaser(Player* source);
        void deactivateLaser(Player* source);
        void shootLaser(Player* source);
        void activateJumble(Player* source);
        void activatePortal(Item* item, Player* source);
        void deactivatePortal(Item* item, Player* source);
        void activateSmite(Player* source);
        void deactivateSmite(Player* source);
        void activateHerb(Player* source);
        void activateF(Player* source);
        void deactivateF(Player* source);
        void activateBombAdd(Player* source);
        void activateRangeAdd(Player* source);

        Player* getPlayer(PlayerNumber playerNumber);
        Monster* getMonster();
        Turtle* getTurtle();

        int roundNum(int input);

        bool isRunning();
        bool collisionCheck(Player* player);
        bool collisionCheck(Monster* monster);
        bool collisionCheck(Turtle* turtle);
        bool bombDuplicate(Bomb& bomb);

    protected:

    private:
        SDL_Event event;
        SDL_Renderer* renderer;
        SDL_Window* window;
        SDL_Texture* texture;
        bool running;
        int timer = 0;
        const char* crackedIMG;
        std::vector<Entity> blocks;
        std::vector<Flag> flagsOne;
        std::vector<Flag> flagsTwo;
        std::vector<MetalCrate> metalCrates;
        std::vector<Player> players;
        std::vector<Monster> monsters;
        std::vector<Turtle> turtles;
        std::vector<Bomb> bombs;
        std::vector<Bomb> barrelBombs;
        std::vector<Entity>::iterator blockIterator;
        std::vector<Flag>::iterator flagIterator;
        std::vector<MetalCrate>::iterator metalCrateIterator;
        std::vector<Player>::iterator playerIterator;

        std::vector<Monster>::iterator monsterIterator;
        std::vector<Turtle>::iterator turtleIterator;
        std::vector<Bomb>::iterator bombIterator;
        std::vector<Bomb>::iterator barrelBombsIterator;

        //Items
        std::vector<Item> items;
        std::vector<Rocket> rockets;
        std::vector<LaserBeam> laserBeams;
        std::vector<Portal> portals;
        std::vector<Cloud> clouds;

        std::vector<Item>::iterator itemIterator;
        std::vector<Rocket>::iterator rocketIterator;
        std::vector<LaserBeam>::iterator laserBeamIterator;
        std::vector<Portal>::iterator portalIterator;
        std::vector<Cloud>::iterator cloudIterator;
        const Uint8* keystates;
};

#endif // GAME_H
