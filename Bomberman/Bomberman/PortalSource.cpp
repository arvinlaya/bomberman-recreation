#include "PortalSource.h"

const char* PortalSource::portalSourceIMG;
void PortalSource::setPortalSourceIMG(const char* source) {
    PortalSource::portalSourceIMG = source;
}

PortalSource::PortalSource(int colPosition, int rowPosition)
    : Entity(PortalSource::portalSourceIMG, colPosition, rowPosition, PORTAL_SOURCE, 1)
{}

PortalSource::~PortalSource(){}
