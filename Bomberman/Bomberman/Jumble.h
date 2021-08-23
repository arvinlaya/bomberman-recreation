#ifndef JUMBLE_H
#define JUMBLE_H

#include "Item.h"

class Jumble: public Item
{
    public:
        static const char* jumbleIMG;
        static void setJumbleIMG(const char* source);

        Jumble(int colPosition, int rowPosition);
        ~Jumble();

    protected:

    private:
};

#endif // JUMBLE_H
