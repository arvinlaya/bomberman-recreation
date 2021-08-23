#ifndef FLAG_H
#define FLAG_H

#include "Entity.h"
#include "Player.h"

class Flag: public Entity
{
    public:
        static const char* flagIMG;
        static void setFlagIMG(const char* source);

        Flag(int colPosition, int rowPosition, EntityType flagNum);
        ~Flag();

        int getHitTime();

        void setHitTime();

    protected:

    private:
        int hitTime = 0;
};

#endif // FLAG_H
