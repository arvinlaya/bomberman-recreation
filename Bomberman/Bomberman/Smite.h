#ifndef SMITE_H
#define SMITE_H

#include "Item.h"

class Smite: public Item
{
    public:
        static const char* smiteIMG;
        static void setSmiteIMG(const char* source);

        Smite(int colPosition, int rowPosition);
        ~Smite();

    protected:

    private:
};

#endif // SMITE_H
