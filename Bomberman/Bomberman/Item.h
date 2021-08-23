#ifndef ITEM_H
#define ITEM_H

#include "Entity.h"

class Item: public Entity
{
    public:
        Item(const char* imageLocation, int colPosition, int rowPosition, ItemType type, int timeDuration);
        ~Item();

        ItemType getItemType();
        int getPickUpTime();
        int getDuration();

        virtual void activateItem();
        void setPickUpTime();
        void spawnRocket(int colPosition, int rowPosition);
        void setDuration();

    protected:

    private:
        ItemType itemType;
        int pickTime;
        int initDuration;
        int duration;
};

#endif // ITEM_H
