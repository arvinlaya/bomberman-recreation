#ifndef LIGHTNING_H
#define LIGHTNING_H

#include "Entity.h"

#define LIGHTNING_WIDTH 55
#define LIGHTNING_HEIGHT 110

class Lightning: public Entity
{
    public:
        static SDL_Texture* lightningTexture;
        static void loadLightningIMG(SDL_Renderer* renderer);

        Lightning();
        ~Lightning();

        SDL_Texture* getLightningTexture();

    protected:

    private:

};

#endif // LIGHTNING_H
