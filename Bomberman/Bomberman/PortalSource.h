#ifndef PORTALSOURCE_H
#define PORTALSOURCE_H

#include "Entity.h"

class PortalSource: public Entity
{
    public:
        static const char* portalSourceIMG;
        static void setPortalSourceIMG(const char* source);

        PortalSource(int colPosition, int rowPosition);
        ~PortalSource();

    protected:

    private:
};

#endif // PORTALSOURCE_H
