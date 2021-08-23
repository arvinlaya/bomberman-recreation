#include "PortalDestination.h"

const char* PortalDestination::portalDestinationIMG;
void PortalDestination::setPortalDestinationIMG(const char* source) {
    PortalDestination::portalDestinationIMG = source;
}

PortalDestination::PortalDestination(int colPosition, int rowPosition)
    : Entity(PortalDestination::portalDestinationIMG, colPosition, rowPosition, PORTAL_DESTINATION, 1)
{}

PortalDestination::~PortalDestination(){}
