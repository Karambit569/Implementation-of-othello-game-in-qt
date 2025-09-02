#ifndef REPLAYMANAGER_H
#define REPLAYMANAGER_H

#include <QList>
#include "GameState.h"

class ReplayManager {
public:
    void recordTurn(const GameState &state);
    QList<GameState> getHistory() const;

private:
    QList<GameState> history;
};

#endif
