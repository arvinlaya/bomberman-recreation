#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include "Entity.h"

class HealthBar
{
    public:

        static SDL_Texture* redBarTexture;
        static SDL_Texture* greenBarTexture;
        static void initializeHealthBar(SDL_Renderer* renderer);

        HealthBar(int HP);
        ~HealthBar();

        SDL_Texture* getGreenTexture();
        SDL_Texture* getRedTexture();
        SDL_Rect* getGreenDestRect(int xPosition, int yPosition);
        SDL_Rect* getRedDestRect(int xPosition, int yPosition);

        void setHP(int life);
    protected:

    private:
        int health;
        SDL_Rect greenDestRect;
        SDL_Rect redDestRect;
};

#endif // HEALTHBAR_H
