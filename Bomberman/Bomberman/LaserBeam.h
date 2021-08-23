#ifndef LASERBEAM_H
#define LASERBEAM_H

#include "Player.h"
#include "Entity.h"

#include <vector>
#include <iterator>

class LaserBeam
{


    public:

        static void loadLaserBeamIMG(SDL_Renderer* renderer);

        LaserBeam(int initX, int initY, Direction direction, PlayerNumber source);
        ~LaserBeam();

        int getXPosition();
        int getYPosition();
        int getRange();
        int getAngle();
        int getDirectionalIncrement();
        int getDuration();
        Direction getDirection();
        SDL_Rect* getDestRect();
        SDL_Texture* getTexture();
        PlayerNumber getSource();

        void setRange(std::vector<Entity>* blocks);
        void incrementDuration();

    protected:

    private:
        int xPosition;
        int yPosition;
        Direction shootDirection;
        PlayerNumber playerNumber;
        SDL_Rect destRect;
        std::vector<Entity>::iterator blockIterator;
        int angle;
        int directionalIncrement;
        int duration = 0;
        int durationIncrement = 30;
        int range = 2000;
        static SDL_Texture* beamTail;
        static SDL_Texture* beamBody;
        static SDL_Texture* beamHead;
};

#endif // LASERBEAM_H
