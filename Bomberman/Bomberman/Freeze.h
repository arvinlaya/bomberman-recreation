#ifndef FREEZE_H
#define FREEZE_H

#include "Item.h"

class Freeze: public Item
{
    public:
        static const char* freezeIMG;
        static void setFreezeIMG(const char* source);
        Freeze(int colPosition, int rowPosition);
        ~Freeze();

    protected:

    private:
};

#endif // FREEZE_H
