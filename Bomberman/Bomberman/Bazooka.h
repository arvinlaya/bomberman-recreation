#ifndef BAZOOKA_H
#define BAZOOKA_H

#include "Item.h"

class Bazooka: public Item
{
    public:

        static const char* bazookaIMG;
        static void setBazookaIMG(const char* source);

        Bazooka(int colPosition, int rowPosition);
        ~Bazooka();

    protected:

    private:
};

#endif // BAZOOKA_H
