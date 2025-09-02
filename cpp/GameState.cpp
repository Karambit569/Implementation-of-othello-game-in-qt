#include "GameState.h"
#include <cstdlib>

void GameState::initialize(const GameSettingDialog::GameConfig &config) {
    boardSize = config.boardSize;
    board = QVector<QVector<Cell>>(boardSize, QVector<Cell>(boardSize, EMPTY));

    int mid = boardSize / 2;
    board[mid - 1][mid - 1] = WHITE;
    board[mid][mid] = WHITE;
    board[mid - 1][mid] = BLACK;
    board[mid][mid - 1] = BLACK;

    blackCount = 2;
    whiteCount = 2;
    turnCount = 1;

    blackTurn = (config.firstPlayer == "흑") ||
                (config.firstPlayer == "무작위" && rand() % 2 == 0);
}
