#include "GameWindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>

GameWindow::GameWindow(const GameSettingDialog::GameConfig &config, QWidget *parent)
    : QWidget(parent) {

    // 게임판 위젯 생성
    boardWidget = new GameBoardWidget(config, this);

    // 라벨 생성
    turnLabel = new QLabel(this);
    blackCountLabel = new QLabel(this);
    whiteCountLabel = new QLabel(this);

    // 라벨을 GameBoardWidget에도 전달
    boardWidget->turnLabel = turnLabel;
    boardWidget->blackCountLabel = blackCountLabel;
    boardWidget->whiteCountLabel = whiteCountLabel;

    // 버튼 생성
    backButton = new QPushButton("메인화면으로", this);
    connect(backButton, &QPushButton::clicked, this, &GameWindow::goToMainMenu);

    // 오른쪽 레이아웃 구성
    QVBoxLayout *sideLayout = new QVBoxLayout;
    sideLayout->addWidget(turnLabel);
    sideLayout->addWidget(blackCountLabel);
    sideLayout->addWidget(whiteCountLabel);
    sideLayout->addStretch();
    sideLayout->addWidget(backButton);

    // 전체 레이아웃
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(boardWidget, 1);       // 비율 1
    mainLayout->addLayout(sideLayout);

    setLayout(mainLayout);
    setWindowTitle("오델로");
    resize(800, 600);
}

void GameWindow::goToMainMenu() {
    QMessageBox::information(this, "메인화면", "메인화면으로 돌아갑니다.");
    // 여기서 메인 윈도우 호출 또는 현재 창 닫기 처리 가능
    close();
}
