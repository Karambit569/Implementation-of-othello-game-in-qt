#include "MainWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), gameBoard(nullptr) {

    central = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(central);

    gameLabel = new QLabel("Othello", this);
    newGameBtn = new QPushButton("새 게임", this);
    continueBtn = new QPushButton("이어하기", this);
    replayBtn = new QPushButton("리플레이", this);
    exitBtn = new QPushButton("게임 종료", this);
    infoLabel = new QLabel("2024402095 강태현", this);

    layout->addWidget(gameLabel);
    layout->addWidget(newGameBtn);
    layout->addWidget(continueBtn);
    layout->addWidget(replayBtn);
    layout->addWidget(exitBtn);
    layout->addWidget(infoLabel);

    continueBtn->setEnabled(false);
    replayBtn->setEnabled(false);

    setCentralWidget(central);

    connect(newGameBtn, &QPushButton::clicked, this, &MainWindow::startNewGame);
    connect(continueBtn, &QPushButton::clicked, this, &MainWindow::continueGame);
    connect(replayBtn, &QPushButton::clicked, this, &MainWindow::openReplay);
    connect(exitBtn, &QPushButton::clicked, this, &MainWindow::exitGame);
}

void MainWindow::startNewGame() {
    GameSettingDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        GameSettingDialog::GameConfig config = dialog.getConfig();

        if (gameBoard) {
            gameBoard->deleteLater();
            gameBoard = nullptr;
        }

        gameBoard = new GameBoardWidget(config, this);
        gameBoard->setMinimumSize(600, 600);
        setCentralWidget(gameBoard);

        connect(gameBoard, &GameBoardWidget::requestReturnToMain, this,
                [this](const GameState &state) {
                    savedState = state;
                    replayHistory.clear();
                    replayHistory.append(state);
                    gameBoard = nullptr;


                    setCentralWidget(central);

                    continueBtn->setEnabled(true);
                    replayBtn->setEnabled(true);
                });



        qDebug() << "새 게임 시작: " << config.boardSize << "x" << config.boardSize;
    }
}

void MainWindow::continueGame() {
    if (savedState.boardSize == 0) return;

    if (gameBoard) {
        gameBoard->deleteLater();
        gameBoard = nullptr;
    }

    gameBoard = new GameBoardWidget(savedState, this);
    gameBoard->setMinimumSize(600, 600);
    setCentralWidget(gameBoard);

    connect(gameBoard, &GameBoardWidget::requestReturnToMain, this,
            [this](const GameState &state) {
                savedState = state;
                replayHistory.clear();
                replayHistory.append(state);


                gameBoard = nullptr;
                setCentralWidget(central);

                continueBtn->setEnabled(true);
                replayBtn->setEnabled(true);
            });


}

void MainWindow::openReplay() {
    if (replayHistory.isEmpty()) return;

    ReplayWindow *replay = new ReplayWindow(replayHistory, this);
    replay->show();
}

void MainWindow::exitGame() {
    close();
}
