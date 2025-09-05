#include "GameWindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>

GameWindow::GameWindow(const GameSettingDialog::GameConfig &config, QWidget *parent)
    : QWidget(parent) {

    // Widget
    boardWidget = new GameBoardWidget(config, this);

    // Label
    turnLabel = new QLabel(this);
    blackCountLabel = new QLabel(this);
    whiteCountLabel = new QLabel(this);

    // GameBoardWidget
    boardWidget->turnLabel = turnLabel;
    boardWidget->blackCountLabel = blackCountLabel;
    boardWidget->whiteCountLabel = whiteCountLabel;

    // Buttons
    backButton = new QPushButton("To main", this);
    connect(backButton, &QPushButton::clicked, this, &GameWindow::goToMainMenu);

    // Layout
    QVBoxLayout *sideLayout = new QVBoxLayout;
    sideLayout->addWidget(turnLabel);
    sideLayout->addWidget(blackCountLabel);
    sideLayout->addWidget(whiteCountLabel);
    sideLayout->addStretch();
    sideLayout->addWidget(backButton);

    // ovr layout
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(boardWidget, 1);       
    mainLayout->addLayout(sideLayout);

    setLayout(mainLayout);
    setWindowTitle("Othello");
    resize(800, 600);
}

void GameWindow::goToMainMenu() {
    QMessageBox::information(this, "Main", "Exit to main");
    close();
}
