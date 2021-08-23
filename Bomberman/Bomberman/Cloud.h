#ifndef CLOUD_H
#define CLOUD_H

#include "Entity.h"
#include "Lightning.h"
#include "Player.h"

#define CLOUD_WIDTH 110
#define CLOUD_HEIGHT 55

class Cloud: public Entity
{
    public:
        static SDL_Texture* cloudTexture;
        static void loadCloudIMG(SDL_Renderer* renderer);

        Cloud(Player* target);
        ~Cloud();

        SDL_Texture* getCloudTexture();
        Player* getTarget();
        Lightning* getLightning();

        bool charged();
        bool getHitState();

    protected:

    private:
        Lightning lightning;
        Player* targetPlayer;

        int hitTime;
        bool hitReady = false;
};

#endif // CLOUD_H
