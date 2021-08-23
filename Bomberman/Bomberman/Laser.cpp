#include "Laser.h"

const char* Laser::laserIMG;
void Laser::setLaserIMG(const char* source) {
    Laser::laserIMG = source;
}

Laser::Laser(int colPosition, int rowPosition)
    : Item(Laser::laserIMG, colPosition, rowPosition, LASER, 5)
{}

Laser::~Laser(){}
