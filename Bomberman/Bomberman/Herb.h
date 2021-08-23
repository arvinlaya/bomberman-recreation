#ifndef HERB_H
#define HERB_H

#include "Item.h"

class Herb: public Item
{
    public:
        static const char* herbIMG;
        static void setHerbIMG(const char* source);

        Herb(int colPosition, int rowPosition);
        ~Herb();

    protected:

    private:
};

#endif // HERB_H
