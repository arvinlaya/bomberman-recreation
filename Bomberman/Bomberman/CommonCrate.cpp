#include "CommonCrate.h"

const char* CommonCrate::commonCrateIMG;
void CommonCrate::setCommonCrateIMG(const char* source) {
    CommonCrate::commonCrateIMG = source;
}

CommonCrate::CommonCrate(int colPosition, int rowPosition)
    : Entity(CommonCrate::commonCrateIMG, colPosition * CELL_SIZE, rowPosition * CELL_SIZE, COMMON_CRATE, 1)
{}

CommonCrate::~CommonCrate(){}
