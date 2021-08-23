#ifndef BARREL_H
#define BARREL_H

#include "Entity.h"

class Barrel: public Entity
{

    public:

        static const char* barrelIMG;
        static void setBarrelIMG(const char* source);
        Barrel();
        Barrel(int colPosition, int rowPosition);
        ~Barrel();

    protected:

    private:

};

#endif // BARREL_H
