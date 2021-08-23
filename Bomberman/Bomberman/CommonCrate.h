#ifndef COMMONCRATE_H
#define COMMONCRATE_H

#include "Entity.h"

class CommonCrate: public Entity
{
    public:
        static const char* commonCrateIMG;
        static void setCommonCrateIMG(const char* source);

        CommonCrate(int colPosition, int rowPosition);
        ~CommonCrate();

    protected:

    private:
};

#endif // COMMONCRATE_H
