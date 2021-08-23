#ifndef WALL_H
#define WALL_H

#include "Entity.h"

class Wall : public Entity
{

    public:
        static const char* wallIMG;
        static void setWallIMG(const char* source);

        Wall(int colPosition, int rowPosition);
        ~Wall();


    protected:

    private:
};

#endif // WALL_H
