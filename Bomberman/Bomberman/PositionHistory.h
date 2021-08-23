#ifndef POSITIONHISTORY_H
#define POSITIONHISTORY_H

#include <vector>

class PositionHistory
{
    public:
        PositionHistory();
        ~PositionHistory();

        std::vector<int>* getXHistory();
        std::vector<int>* getYHistory();
        int getSize();

        void inputHistory(int xPosition, int yPosition, int historySize);

    protected:

    private:
        std::vector<int> xHistory;
        std::vector<int> yHistory;
};

#endif // POSITIONHISTORY_H
