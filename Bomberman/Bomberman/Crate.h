#ifndef CRATE_H
#define CRATE_H

#include "Entity.h"

class Crate: public Entity
{
    public:
        static const char* crateIMG;
        static void setCrateIMG(const char* source);

        Crate(int colPosition, int rowPosition);
        ~Crate();

    protected:

    private:
};

#endif // CRATE_H
