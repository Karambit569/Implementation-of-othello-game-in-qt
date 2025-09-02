#include "GameBoardWidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QDebug>

GameBoardWidget::GameBoardWidget(const GameSettingDialog::GameConfig &config, QWidget *parent)
    : QWidget(parent) {
    currentState.boardSize = config.boardSize;
    currentState.initialize(config);
    setupUI();
    calculateValidMoves();
    updateStatusLabels();
}

GameBoardWidget::GameBoardWidget(const GameState &state, QWidget *parent)
    : QWidget(parent), currentState(state) {
    setupUI();
    calculateValidMoves();
    updateStatusLabels();
}

void GameBoardWidget::setupUI() {
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    setLayout(mainLayout);

    // Drawing area on the left
    QWidget *boardArea = new QWidget(this);
    boardArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mainLayout->addWidget(boardArea);

    // Right side info panel
    rightPanel = new QWidget(this);
    rightPanelLayout = new QVBoxLayout(rightPanel);

    turnLabel = new QLabel(this);
    turnCountLabel = new QLabel(this);
    scoreLabel = new QLabel(this);

    saveAndReturnBtn = new QPushButton("저장하고 메인으로", this);
    connect(saveAndReturnBtn, &QPushButton::clicked, [=]() {
        emit requestReturnToMain(currentState);
    });

    rightPanelLayout->addWidget(turnLabel);
    rightPanelLayout->addWidget(turnCountLabel);
    rightPanelLayout->addWidget(scoreLabel);
    rightPanelLayout->addStretch();
    rightPanelLayout->addWidget(saveAndReturnBtn);

    mainLayout->addWidget(rightPanel);
}

void GameBoardWidget::updateStatusLabels() {
    turnLabel->setText(QString("현재 턴: %1").arg(currentState.blackTurn ? "흑" : "백"));
    turnCountLabel->setText(QString("턴 수: %1").arg(currentState.turnCount));
    scoreLabel->setText(QString("흑: %1개, 백: %2개")
                            .arg(currentState.blackCount)
                            .arg(currentState.whiteCount));
}

void GameBoardWidget::paintEvent(QPaintEvent *) {
    if (!isVisible()) return;
    QPainter painter(this);
    int size = currentState.boardSize;
    int cellSize = qMin(width(), height()) / size;

    for (int row = 0; row < size; ++row) {
        for (int col = 0; col < size; ++col) {
            QRect rect(col * cellSize, row * cellSize, cellSize, cellSize);
            painter.setPen(Qt::black);
            painter.drawRect(rect);

            switch (currentState.board[row][col]) {
            case GameState::BLACK:
                painter.setBrush(Qt::black);
                painter.drawEllipse(rect.adjusted(5, 5, -5, -5));
                break;
            case GameState::WHITE:
                painter.setBrush(Qt::white);
                painter.drawEllipse(rect.adjusted(5, 5, -5, -5));
                break;
            case GameState::OBSTACLE:
                painter.fillRect(rect.adjusted(5, 5, -5, -5), Qt::darkBlue);
                break;
            case GameState::EMPTY:
                if (validMoves.contains({row, col})) {
                    painter.setBrush(Qt::green);
                    painter.drawEllipse(rect.center(), 4, 4);
                }
                break;
            }
        }
    }
}

void GameBoardWidget::mousePressEvent(QMouseEvent *event) {
    int size = currentState.boardSize;
    int cellSize = qMin(width(), height()) / size;
    int col = event->pos().x() / cellSize;
    int row = event->pos().y() / cellSize;

    if (row < 0 || col < 0 || row >= size || col >= size) return;
    if (!validMoves.contains({row, col})) return;

    GameState::Cell me = currentState.blackTurn ? GameState::BLACK : GameState::WHITE;
    currentState.board[row][col] = me;
    flipStones(row, col);

    // Update counts
    currentState.blackCount = 0;
    currentState.whiteCount = 0;
    for (int r = 0; r < size; ++r) {
        for (int c = 0; c < size; ++c) {
            if (currentState.board[r][c] == GameState::BLACK) currentState.blackCount++;
            if (currentState.board[r][c] == GameState::WHITE) currentState.whiteCount++;
        }
    }

    currentState.blackTurn = !currentState.blackTurn;
    currentState.turnCount++;
    calculateValidMoves();
    updateStatusLabels();
    update();
}

void GameBoardWidget::calculateValidMoves() {
    validMoves.clear();
    const int dx[] = {-1, -1, -1, 0, 1, 1, 1, 0};
    const int dy[] = {-1, 0, 1, 1, 1, 0, -1, -1};

    int size = currentState.boardSize;
    GameState::Cell me = currentState.blackTurn ? GameState::BLACK : GameState::WHITE;
    GameState::Cell opponent = currentState.blackTurn ? GameState::WHITE : GameState::BLACK;

    for (int row = 0; row < size; ++row) {
        for (int col = 0; col < size; ++col) {
            if (currentState.board[row][col] != GameState::EMPTY) continue;

            for (int d = 0; d < 8; ++d) {
                int x = col + dx[d];
                int y = row + dy[d];
                bool foundOpponent = false;

                while (x >= 0 && y >= 0 && x < size && y < size) {
                    if (currentState.board[y][x] == opponent) {
                        foundOpponent = true;
                    } else if (currentState.board[y][x] == me && foundOpponent) {
                        validMoves.insert({row, col});
                        break;
                    } else break;
                    x += dx[d];
                    y += dy[d];
                }
                if (validMoves.contains({row, col})) break;
            }
        }
    }

    if (validMoves.isEmpty()) {
        currentState.blackTurn = !currentState.blackTurn;
        calculateValidMoves();
        QMessageBox::information(this, "턴 넘김", "착수할 수 없어 턴을 넘깁니다.");
    }
}

void GameBoardWidget::flipStones(int row, int col) {
    const int dx[] = {-1, -1, -1, 0, 1, 1, 1, 0};
    const int dy[] = {-1, 0, 1, 1, 1, 0, -1, -1};

    GameState::Cell me = currentState.blackTurn ? GameState::BLACK : GameState::WHITE;
    GameState::Cell opponent = currentState.blackTurn ? GameState::WHITE : GameState::BLACK;

    for (int d = 0; d < 8; ++d) {
        int x = col + dx[d];
        int y = row + dy[d];
        QVector<QPair<int, int>> toFlip;

        while (x >= 0 && y >= 0 && x < currentState.boardSize && y < currentState.boardSize) {
            if (currentState.board[y][x] == opponent) {
                toFlip.append({y, x});
            } else if (currentState.board[y][x] == me) {
                for (const auto &p : toFlip)
                    currentState.board[p.first][p.second] = me;
                break;
            } else break;

            x += dx[d];
            y += dy[d];
        }
    }
}
