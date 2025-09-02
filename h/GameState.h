#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <QVector>
#include "GameSettingDialog.h"

class GameState {
public:
    enum Cell { EMPTY, BLACK, WHITE, OBSTACLE };
    int boardSize;
    QVector<QVector<Cell>> board;
    int blackCount = 0;
    int whiteCount = 0;
    bool blackTurn = true;
    int turnCount = 0;

    void initialize(const GameSettingDialog::GameConfig &config);
};

#endif
