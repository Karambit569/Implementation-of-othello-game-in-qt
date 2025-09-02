#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include "GameSettingDialog.h"
#include "GameBoardWidget.h"
#include "ReplayWindow.h"
#include "GameState.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void startNewGame();
    void continueGame();
    void openReplay();
    void exitGame();

private:
    QWidget *central;
    QLabel *gameLabel;
    QPushButton *newGameBtn;
    QPushButton *continueBtn;
    QPushButton *replayBtn;
    QPushButton *exitBtn;
    QLabel *infoLabel;

    GameBoardWidget *gameBoard = nullptr;
    GameState savedState; // ✅ 값 타입으로 선언
    QList<GameState> replayHistory;
};

#endif
