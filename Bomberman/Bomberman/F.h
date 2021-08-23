#ifndef F_H
#define F_H

#include "Item.h"

class F: public Item
{
    public:
        static const char* fIMG;
        static void setFIMG(const char* source);

        F(int colPosition, int rowPosition);
        ~F();

    protected:

    private:
};

#endif // F_H
