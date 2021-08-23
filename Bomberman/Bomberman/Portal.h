#ifndef PORTAL_H
#define PORTAL_H

#include "Item.h"
#include "Player.h"
#include "PortalSource.h"
#include "PortalDestination.h"

enum Path {
    DESTINATION, SOURCE
};

class Portal: public Item
{
    public:
        static const char* portalIMG;
        static void setPortalIMG(const char* source);

        Portal(int colPosition, int rowPosition);
        Portal(int colPosition, int rowPosition, int targetColPosition, int targetRowPosition, SDL_Renderer* renderer);
        ~Portal();

        bool inside(int playerX, int playerY, Player* player);
        Path getPath(int playerX, int playerY);

        SDL_Texture* getSourceTexture();
        SDL_Texture* getDestinationTexture();

        SDL_Rect* getSourceRect();
        SDL_Rect* getDestinationRect();

        void teleport(int playerX, int playerY, Player* player);

    protected:

    private:
        PortalSource source;
        PortalDestination destination;
        int resetTimer;
};

#endif // PORTAL_H
