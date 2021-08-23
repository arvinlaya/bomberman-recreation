#ifndef HARDBRICK_H
#define HARDBRICK_H

#include "Entity.h"

class HardBrick: public Entity
{
    public:
        static const char* hardBrickIMG;
        static void setHardBrickIMG(const char* source);

        HardBrick(int colPosition, int rowPosition);
        ~HardBrick();

    protected:

    private:
};

#endif // HARDBRICK_H
