#include "PositionHistory.h"

PositionHistory::PositionHistory(){}

PositionHistory::~PositionHistory(){}

std::vector<int>* PositionHistory::getXHistory() {
    return &this->xHistory;
}

std::vector<int>* PositionHistory::getYHistory() {
    return &this->yHistory;
}

int PositionHistory::getSize() {
    return this->xHistory.size();
}

void PositionHistory::inputHistory(int xPosition, int yPosition, int historySize) {

    if(xHistory.size() > 0) {
        if(*(xHistory.begin()) != xPosition || *(yHistory.begin()) != yPosition) {
            this->xHistory.insert(xHistory.begin(), xPosition);
            this->yHistory.insert(yHistory.begin(), yPosition);
        }
    }
    else {
        this->xHistory.emplace_back(xPosition);
        this->yHistory.emplace_back(yPosition);
    }

    if(this->xHistory.size() > historySize+1)
        this->xHistory.erase(xHistory.end()-1);
    if(this->yHistory.size()> historySize+1)
        this->yHistory.erase(yHistory.end()-1);
}
