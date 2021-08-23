#include "MetalCrate.h"

MetalCrate::MetalCrate(int colPosition, int rowPosition)
    : Entity("images/game/metalCrate.png", colPosition, rowPosition, METAL_CRATE, 2)
{}

MetalCrate::~MetalCrate(){}
