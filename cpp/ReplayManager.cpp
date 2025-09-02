#include "ReplayManager.h"

void ReplayManager::recordTurn(const GameState &state) {
    history.append(state);
}

QList<GameState> ReplayManager::getHistory() const {
    return history;
}
