#ifndef SNAIL_H
#define SNAIL_H

#include "Item.h"

class Snail : public Item
{
    public:
        static const char* snailIMG;
        static void setSnailIMG(const char* source);

        Snail(int colPosition, int rowPosition);
        ~Snail();

    protected:

    private:
};

#endif // SNAIL_H
