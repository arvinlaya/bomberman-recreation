#ifndef LASER_H
#define LASER_H

#include "Item.h"

class Laser : public Item
{

    struct laserRange {
        int upRange = 55;
        int leftRange = 55;
        int downRange = 540;
        int rightRange = 1045;
    };

    public:
        static const char* laserIMG;
        static void setLaserIMG(const char* source);

        Laser(int colPosition, int rowPosition);
        ~Laser();

    protected:

    private:
};

#endif // LASER_H
