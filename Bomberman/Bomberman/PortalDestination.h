#ifndef PORTALDESTINATION_H
#define PORTALDESTINATION_H

#include "Entity.h"

class PortalDestination: public Entity
{
    public:
        static const char* portalDestinationIMG;
        static void setPortalDestinationIMG(const char* source);

        PortalDestination(int colPosition, int rowPosition);
        ~PortalDestination();

    protected:

    private:
};

#endif // PORTALDESTINATION_H
