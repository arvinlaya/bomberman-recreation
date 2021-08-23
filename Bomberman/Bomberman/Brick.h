#ifndef BRICK_H
#define BRICK_H

#include "Entity.h"


class Brick: public Entity
{
    public:
        static const char* brickIMG;
        static void setBrickIMG(const char* source);
        Brick(int colPosition, int rowPosition);
        ~Brick();

    protected:

    private:
};

#endif // BRICK_H
