#ifndef PORTALTIMER_H
#define PORTALTIMER_H

#include "Entity.h"

class PortalTimer
{
    public:
        PortalTimer(int initial);
        ~PortalTimer();

        int getTime();
        int getResetTimer();
        int getCooldown();

        bool isInitialized();

        void setCooldown();
        void setInitial(int value);
        void setResetTimer();

    protected:

    private:
        int start = 0;
        int resetTimer;
        int coolDown = 0;
};

#endif // PORTALTIMER_H
