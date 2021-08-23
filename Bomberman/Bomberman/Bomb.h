#ifndef BOMB_H
#define BOMB_H

#include "Entity.h"
#include "Player.h"

#define BOMB_WIDTH 750
#define BOMB_COL_COUNT 15
#define BOMB_HEIGHT 50


#define EXPLODE_WIDTH 512
#define EXPLODE_COL_COUNT 4
#define EXPLODE_HEIGHT 512
#define EXPLODE_ROW_COUNT 4

class Bomb: public Entity
{

    struct BombRange{
        int upRange = 55;
        int leftRange = 55;
        int downRange = 550;
        int rightRange = 1045;
    };

    public:

        Bomb(int colPosition, int rowPosition, SDL_Renderer* renderer, int rangeLimit);
        Bomb(int colPosition, int rowPosition, PlayerNumber bombOwner, SDL_Renderer* renderer, int rangeLimit);
        ~Bomb();

        int getSpawnTime();
        BombRange getRange();
        SDL_Rect* getDetonateSprite();
        PlayerNumber getOwner();

        void setBombRange(const std::vector<Entity>& blocks);
        void explode(SDL_Renderer* render);
        void setExplodeTimer(int time);
        void incrementDetonateFrameCol();
        void incrementExplodeFrame();
        void setSpawnTime(int time);

    protected:

    private:
        PlayerNumber owner;
        int spawnTime;
        int detonateTimer;
        int explodeTimer = 0;

        BombRange range;
        const char* explodeAnimateLocation;
        SDL_Texture* explodeTexture;

        SDL_Rect explodeDestRect;
        SDL_Rect explodeSpriteRect;

        SDL_Rect detonateRect;

        int maxRange;
};

#endif // BOMB_H
