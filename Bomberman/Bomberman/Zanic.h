#ifndef ZANIC_H
#define ZANIC_H

#include "Item.h"

class Zanic: public Item
{
    public:

        static const char* zanicIMG;
        static void setZanicIMG(const char* source);
        Zanic(int colPosition, int rowPosition);
        ~Zanic();

    protected:

    private:
};

#endif // ZANIC_H
